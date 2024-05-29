#include "databaseManager.h"
#include "../../common/authentication/authentication.h"

bool DatabaseManager::Login(Authentication* auth) {
    QSqlQuery query(m_db);
    query.prepare("SELECT u.fio, u.avatar_url, u.role, u.id "
                  "FROM users AS u "
                  "WHERE u.login = :login AND u.password = :password");
    query.bindValue(":login", auth->GetLogin());
    query.bindValue(":password", auth->GetPassword());
    // для вставки логина пароля в бд закоментировать выше разкомментировать ниже
    // query.prepare("INSERT INTO users ( fio, login, password, avatar_url, role) "
    //               "VALUES ( :fio, :login, :password, :avatar_url, :role)");
    // query.bindValue(":login", auth->GetLogin());
    // query.bindValue(":password", auth->GetPassword());
    // query.bindValue(":fio", "Pasha");
    // query.bindValue(":avatar_url", "avatarUrl");
    // query.bindValue(":role", 0);
    if (!query.exec()) {
        qDebug() << "Error executing login query:" << query.lastError().text();
        return false;
    }

    if (!query.first()) {
        qDebug() << "No user found with the given login and password.";
        return false;
    }

    QString fullName = query.value("fio").toString();
    QString avatarUrl = query.value("avatar_url").toString();
    EnumRoles userRole = EnumRoles(query.value("role").toInt());
    int32_t userId = query.value("id").toInt();

    QSqlQuery groupsQuery(m_db);
    groupsQuery.prepare("SELECT g.classname "
                        "FROM groups AS g "
                        "JOIN zachisleniya AS z ON z.groups_id = g.id "
                        "WHERE z.users_id = :userId");
    groupsQuery.bindValue(":userId", userId);

    if (!groupsQuery.exec()) {
        qDebug() << "Error executing groups query:" << groupsQuery.lastError().text();
        return false;
    }

    QList<QString> userGroups;
    while (groupsQuery.next()) {
        userGroups.append(groupsQuery.value("classname").toString());
    }

    auth->SetInformationAfterAuthentication(fullName, avatarUrl, userRole, userId, userGroups);
    return true;
}

// SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time, 
// COALESCE(SUM(pts.verdict), 0) AS current_points, 
// COALESCE(SUM(pct.max_mark), 0) + COALESCE(SUM(pct2.max_mark), 0) AS max_points 
// FROM courses AS c 
// INNER JOIN zachisleniya_in_potok AS zip ON c.students_groups_union_id1 = zip.students_groups_union_id 
// INNER JOIN zachisleniya AS z ON zip.groups_id = z.groups_id
// LEFT JOIN path_course_tasks AS pct ON pct.courses_id1 = c.id 
// LEFT JOIN path_course_tests AS pct2 ON pct2.courses_id1 = c.id 
// LEFT JOIN path_course_tasks_submits AS pts ON pct.id = pts.path_course_tasks_id1 AND pts.users_id1 = z.users_id 
// LEFT JOIN path_course_test_submits AS pcts ON pct2.id = pcts.path_course_tests_id AND pcts.users_id1 = z.users_id 
// WHERE z.users_id = 32 
// GROUP BY c.id, c.title, c.ava_title_url, c.start_time, c.end_time;

QList<Course*> DatabaseManager::GetMainPage(Authentication* auth) {
    QSqlQuery query(m_db);
    QList<Course*> courses;

    if (auth->GetCurrentRole() == STUDENT) {
        query.prepare(
                    "SELECT "
                        "c.id, c.title, c.ava_title_url, c.start_time, c.end_time, "
                        "COALESCE(SUM(pts.verdict), 0) + COALESCE(SUM(pcts.verdict), 0) AS current_points, "
                        "COALESCE(SUM(pct.max_mark), 0) + COALESCE(SUM(pct2.max_mark), 0) AS max_points "
                    "FROM "
                        "courses AS c "
                    "INNER JOIN "
                        "zachisleniya_in_potok AS zip ON c.students_groups_union_id1 = zip.students_groups_union_id "
                    "INNER JOIN "
                        "zachisleniya AS z ON zip.groups_id = z.groups_id "
                    "LEFT JOIN "
                        "path_course_tasks AS pct ON pct.courses_id1 = c.id "
                    "LEFT JOIN "
                        "path_course_tests AS pct2 ON pct2.courses_id1 = c.id "
                    "LEFT JOIN "
                        "path_course_tasks_submits AS pts ON pct.id = pts.path_course_tasks_id1 AND pts.users_id1 = :userId "
                    "LEFT JOIN "
                        "path_course_test_submits AS pcts ON pct2.id = pcts.path_course_tests_id AND pcts.users_id1 = :userId "
                    "WHERE "
                        "z.users_id = :userId "
                    "GROUP BY "
                        "c.id, c.title, c.ava_title_url, c.start_time, c.end_time");
    } else if (auth->GetCurrentRole() == TEACHER) {
        query.prepare("SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time "
                      "FROM courses AS c "
                      "INNER JOIN groups AS g ON c.groups_id = g.id "
                      "INNER JOIN zachisleniya AS z ON g.id = z.groups_id "
                      "WHERE z.users_id = :userId");
    } else {
        query.prepare("SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time "
                      "FROM courses AS c");
    }

    query.bindValue(":userId", auth->getId());
    if (!query.exec()) {
        qDebug() << "Error executing getMainPage query:" << query.lastError().text();
        return courses;
    }

    while (query.next()) {
        int courseId = query.value("id").toInt();
        QString title = query.value("title").toString();
        QString avaUrl = query.value("ava_title_url").toString();
        QDate start = query.value("start_time").toDate();
        QDate end = query.value("end_time").toDate();
        int currentPoints = 0;
        int maxPoints = 0;
        if (auth->GetCurrentRole() == STUDENT) {
            QSqlQuery query_1(m_db);
            query_1.prepare("select sum(verdict) from path_course_tasks_submits "
                "where users_id1 = :userId and "
                            "path_course_tasks_id1 in (select id from path_course_tasks where courses_id1 = :id)");
            query_1.bindValue(":userId",auth->getId());
            query_1.bindValue(":id",courseId);
            if (!query_1.exec()) {
                qDebug() << "Error executing getMainPage query1:" << query_1.lastError().text();
                return courses;
            }
            query_1.next();
            currentPoints += query_1.value(0).toInt();
            QSqlQuery query_2(m_db);
            query_2.prepare("select sum(verdict) from path_course_test_submits "
                            "where users_id1 = :userId and "
                            "path_course_tests_id in (select id from path_course_tests where courses_id1 = :id)");
            query_2.bindValue(":userId",auth->getId());
            query_2.bindValue(":id",courseId);
            if (!query_2.exec()) {
                qDebug() << "Error executing getMainPage query2:" << query_2.lastError().text();
                return courses;
            }
            query_2.next();
            currentPoints += query_2.value(0).toInt();
            QSqlQuery query_3(m_db);
            query_3.prepare("select sum(test_size) from path_course_tests where courses_id1 = :id");
            query_3.bindValue(":id",courseId);
            if (!query_3.exec()) {
                qDebug() << "Error executing getMainPage query3:" << query_3.lastError().text();
                return courses;
            }
            query_3.next();
            maxPoints += query_3.value(0).toInt();
            QSqlQuery query_4(m_db);
            query_4.prepare("select sum(max_mark) from path_course_tasks where courses_id1 = :id");
            query_4.bindValue(":id",courseId);
            if (!query_4.exec()) {
                qDebug() << "Error executing getMainPage query4:" << query_4.lastError().text();
                return courses;
            }
            query_4.next();
            maxPoints += query_4.value(0).toInt();
        }

        Course* course = new Course(courseId, title, avaUrl, start, end, currentPoints, maxPoints);
        courses.append(course);
    }

    return courses;
}

QList<CourseComponent*>* DatabaseManager::GetCourseComponents(int32_t courseId,Authentication* auth) {
    QSqlQuery query(m_db);
    QList<CourseComponent*>* listComponents = new QList<CourseComponent*>();
    query.prepare("SELECT id, title, url, \"order\", \"type\" "
                  "FROM path_course_media_files "
                  "WHERE courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    if (!query.exec()) {
        qDebug() << "Error executing course media files query:" << query.lastError().text();
        return listComponents;
    }
    if (!query.first()) {
        qDebug() << "ahahah";
    } else {
        do {
            int32_t id = query.value("id").toInt();
            int32_t order = query.value("order").toInt();
            QString title = query.value("title").toString();
            QString url = query.value("url").toString();
            TypeFile typeFile = (TypeFile)(query.value("type").toInt());
            listComponents->append(new CourseMediaFiles(id, order, title, url, typeFile));
        } while (query.next());
    }

    query.prepare("SELECT * FROM path_course_tasks WHERE courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    if (!query.exec()) {
        qDebug() << "Error executing course tasks query:" << query.lastError().text();
        return listComponents;
    }
    // qInfo() << "huy:" << query.text();
    if (!query.first()) {
        qDebug() << "ahahah";
    } else {
        do {
            int32_t id = query.value("id").toInt();
            int32_t order = query.value("order").toInt();
            QString content = query.value("content").toString();
            int32_t maxMark = query.value("max_mark").toInt();
            int32_t memoryLimit = query.value("memory_limit").toInt();
            QString title = query.value("title").toString();

            QStringList allowedTypes;
            QSqlQuery query2(m_db);
            query2.prepare("SELECT type_files.name "
                          "FROM type_file_has_lesson_problem "
                          "JOIN type_files ON type_file_has_lesson_problem.type_files_id1 = type_files.id "
                          "WHERE type_file_has_lesson_problem.path_course_tasks_id1 = :taskId");
            query2.bindValue(":taskId", id);
            if (!query2.exec()) {
                qDebug() << "Error executing allowed file types query:" << query2.lastError().text();
                return listComponents;
            }
            if (!query2.first()) {
                qDebug() << "ahahah";
            } else {
                do {
                    allowedTypes.append(query2.value("name").toString());
                } while (query2.next());
            }
            QSqlQuery query3(m_db);
            QString allowedTypeOfFiles = allowedTypes.join(",");
            query3.prepare("SELECT answer_url, time, verdict, notes "
                          "FROM path_course_tasks_submits "
                          "WHERE path_course_tasks_id1 = :taskId AND users_id1 = :id");
            query3.bindValue(":taskId", id);
            query3.bindValue(":id", auth->getId());
            if (!query3.exec()) {
                qDebug() << "Error executing task submissions query:" << query3.lastError().text();
                return listComponents;
            }
            if (!query3.first()) {
                qDebug() << "ahahah";
            }

            QString answerUrl;
            QDate solutionTime;
            int32_t verdict = 0;
            QString notes;
            if (query3.first()) {
                answerUrl = query3.value("answer_url").toString();
                solutionTime = query3.value("time").toDate();
                verdict = query3.value("verdict").toInt();
                notes = query3.value("notes").toString();
            }

            listComponents->append(new CourseTask(id, order, content, maxMark, memoryLimit,
                                                      allowedTypeOfFiles, answerUrl, solutionTime,
                                                      verdict, notes, title));
        } while (query.next());
    }

    query.prepare("SELECT id, title, max_mark, url_json, \"order\", test_size, time_in_seconds "
                  "FROM path_course_tests "
                  "WHERE courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    if (!query.exec()) {
        qDebug() << "Error executing course tests query:" << query.lastError().text();
        return listComponents;
    }
    if (!query.first()) {
        qDebug() << "ahahah";
    } else {

        do {
            int32_t id = query.value("id").toInt();
            int32_t order = query.value("order").toInt();
            QString title = query.value("title").toString();
            int32_t maxMark = query.value("max_mark").toInt();
            QString urlJson = query.value("url_json").toString();
            int32_t testSize = query.value("test_size").toInt();
            int32_t timeInSeconds = query.value("time_in_seconds").toInt();

            QSqlQuery query2(m_db);
            query2.prepare("SELECT time, verdict, notes "
                          "FROM path_course_test_submits "
                          "WHERE path_course_tests_id = :testId AND users_id1 = :id");
            query2.bindValue(":testId", id);
            query2.bindValue(":id", auth->getId());
            if (!query2.exec()) {
                qDebug() << "Error executing test submissions query:" << query2.lastError().text();
                return listComponents;
            }
            if (!query2.first()) {
                qDebug() << "ahahah";
            }

            QDate time;
            int32_t verdict = 0;
            QString notes;
            if (query2.first()) {
                time = query2.value("time").toDate();
                verdict = query2.value("verdict").toInt();
                notes = query2.value("notes").toString();
            }

            listComponents->append(new CourseTest(id, order, title, maxMark, urlJson,timeInSeconds, verdict, notes, time, testSize));
        } while (query.next());
    }

    query.prepare("SELECT id, content, \"order\" "
                  "FROM path_course_tutorials "
                  "WHERE courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    if (!query.exec()) {
        qDebug() << "Error executing course tutorials query:" << query.lastError().text();
        return listComponents;
    }
    if (!query.first()) {
        qDebug() << "ahahah";
    } else {

        do {
            int32_t id = query.value("id").toInt();
            int32_t order = query.value("order").toInt();
            QString content = query.value("content").toString();
            listComponents->append(new CourseTutorials(id, order, content));
        } while (query.next());
    }
    return listComponents;
}

QString DatabaseManager::GetTestQuestion(int32_t testId) {
    QSqlQuery query(m_db);
    query.prepare("SELECT url_json "
                  "FROM path_course_tests "
                  "WHERE id = :testId");
    query.bindValue(":testId", testId);

    if (!query.exec()) {
        qDebug() << "Error executing test question query:" << query.lastError().text();
        return QString();
    }

    if (!query.first()) {
        qDebug() << "No test question found for the given test ID.";
        return QString();
    }
    else {
        return query.value("url_json").toString();
    }
}

QList<QString> DatabaseManager::GetEveryGroupName() {
    QSqlQuery query(m_db);
    QList<QString> groupNames;

    query.prepare("SELECT classname FROM groups");

    if (!query.exec()) {
        qDebug() << "Error executing GeteveryGroupName query:" << query.lastError().text();
        return groupNames;
    }

    while (query.next()) {
        QString groupName = query.value("classname").toString();
        groupNames.append(groupName);
    }

    return groupNames;
}

QList<QString> DatabaseManager::GetEveryUnionName() {
    QSqlQuery query(m_db);
    QList<QString> unionNames;

    query.prepare("SELECT classname FROM students_groups_union");

    if (!query.exec()) {
        qDebug() << "Error executing getEveryUnionName query:" << query.lastError().text();
        return unionNames;
    }

    while (query.next()) {
        QString unionName = query.value("classname").toString();
        unionNames.append(unionName);
    }

    return unionNames;
}

bool DatabaseManager::AddNewGroup(Group* group) {
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO groups (classname, isteachergroup) VALUES (:classname, :isTeacherGroup)");
    query.bindValue(":classname", group->getClassname());
    query.bindValue(":isTeacherGroup", group->getIsTeacherGroup());
    if (!query.exec()) {
        qDebug() << "Error inserting group into 'groups' table:" << query.lastError().text();
        return false;
    }

    int groupId = query.lastInsertId().toInt();

    foreach (Authentication* participant, group->getParticipants()) {
        query.prepare("INSERT INTO users ( fio, login, password, avatar_url, role) "
                   "VALUES ( :fio, :login, :password, :avatar_url, :role)");
        query.bindValue(":login", participant->GetLogin());
        participant->HashPassword();
        query.bindValue(":password", participant->GetPassword());
        query.bindValue(":fio", participant->GetFIO());
        query.bindValue(":avatar_url", participant->GetUrlAvatar());
        query.bindValue(":role", (int)participant->GetCurrentRole());
        if (!query.exec()) {
            qDebug() << "Error inserting participant into 'users' table:" << query.lastError().text();
            return false;
        }
        int userId = query.lastInsertId().toInt();
        query.prepare("INSERT INTO zachisleniya (users_id, groups_id) VALUES (:userId, :groupId)");
        query.bindValue(":userId", userId);
        query.bindValue(":groupId", groupId);
        if (!query.exec()) {
            qDebug() << "Error inserting participant into 'zachisleniya' table:" << query.lastError().text();
            return false;
        }
    }
    return true;
}

QList<QString> DatabaseManager::GetAllStudentGroupName() {
    QSqlQuery query(m_db);
    QList<QString> studentGroupNames;

    query.prepare("SELECT * FROM groups WHERE isteachergroup = false");
    if (!query.exec()) {
        qDebug() << "Error executing getAllStudentGroupname query" << query.lastError().text();
        return studentGroupNames;
    }

    while (query.next()) {
        QString groupName = query.value("classname").toString();
        studentGroupNames.append(groupName);
    }

    return studentGroupNames;
}

QList<QString> DatabaseManager::GetEveryTeacherGroupName() {
    QSqlQuery query(m_db);
    QList<QString> teacherGroupNames;

    query.prepare("SELECT * FROM groups WHERE isteachergroup = true");
    if (!query.exec()) {
        qDebug() << "Error executing getEveryTeacherGroupName query" << query.lastError().text();
        return teacherGroupNames;
    }

    while (query.next()) {
        QString groupName = query.value("classname").toString();
        teacherGroupNames.append(groupName);
    }

    return teacherGroupNames;
}

bool DatabaseManager::AddGroupsToUnion(QList<QString> groupsList, QString unionName) {
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO students_groups_union (classname) VALUES (:unionName)");
    query.bindValue(":unionName", unionName);
    if (!query.exec()) {
        qDebug() << "Error inserting new union" << query.lastError().text();
        return false;
    }

    int unionId = query.lastInsertId().toInt();

    foreach (QString groupName, groupsList) {
        query.prepare("SELECT id FROM groups WHERE classname = :value");
        query.bindValue(":value", groupName);
        if (!query.exec()) {
            qDebug() << "Error select group" << query.lastError().text();
            return false;
        }

        if (query.next()) {
            int groupId = query.value("id").toInt();
            query.prepare("INSERT INTO zachisleniya_in_potok (groups_id, students_groups_union_id) VALUES (:groupId, :unionId)");
            query.bindValue(":groupId", groupId);
            query.bindValue(":unionId", unionId);
            if (!query.exec()) {
                qDebug() << "Error inserting relationship" << query.lastError().text();
                return false;
            }
        }
    }

    return true;
}

bool DatabaseManager::AddNewCourse(QString teachersGroupName, QString unionName, Course* course) {

    QSqlQuery groupQuery(m_db);
    groupQuery.prepare("SELECT id FROM groups WHERE classname = :classname AND isteachergroup = true");
    groupQuery.bindValue(":classname", teachersGroupName);
    if (!groupQuery.exec()) {
        qDebug() << "Error getting teachers group ID" << groupQuery.lastError().text();
        return false;
    }
    if (!groupQuery.next()) {
        qDebug() << "Error: Could not find teachers group with name" << teachersGroupName;
        return false;
    }
    int teachersGroupId = groupQuery.value(0).toInt();

    QSqlQuery unionQuery(m_db);
    unionQuery.prepare("SELECT id FROM students_groups_union WHERE classname = :classname");
    unionQuery.bindValue(":classname", unionName);
    if (!unionQuery.exec()) {
        qDebug() << "Error getting union ID" << unionQuery.lastError().text();
        return false;
    }
    if (!unionQuery.next()) {
        qDebug() << "Error: Could not find union with name" << unionName;
        return false;
    }
    int unionId = unionQuery.value(0).toInt();

    QSqlQuery query(m_db);

    query.prepare("INSERT INTO courses (title, ava_title_url, start_time, end_time, groups_id, students_groups_union_id1) "
                  "VALUES (:title, :ava_title_url, :start_time, :end_time, :groups_id, :students_groups_union_id1)");
    query.bindValue(":title", course->GetTitle());
    query.bindValue(":ava_title_url", course->GetAvaTitleUrl());
    query.bindValue(":start_time", course->GetStartTime());
    query.bindValue(":end_time", course->GetEndTime());
    query.bindValue(":groups_id", teachersGroupId);
    query.bindValue(":students_groups_union_id1", unionId);

    if (!query.exec()) {
        qDebug() << "Error inserting new course" << query.lastError().text();
        return false;
    }
    int courseId = query.lastInsertId().toInt();
    QString newAvaTitleUrl= course->moveImageNewCourseToStandartName(courseId);
    course->CreateDir(courseId);
    if(newAvaTitleUrl!=""){
        query.prepare("UPDATE courses SET ava_title_url = :new_ava_title_url WHERE id = :id");
        query.bindValue(":new_ava_title_url", newAvaTitleUrl);
        query.bindValue(":id", courseId);

        if (!query.exec()) {
            qDebug() << "Error updating Course with standart ava_title_url:" << query.lastError().text();
        }
    }
    return true;
}



bool DatabaseManager::UpdateGroup(Group* group) {
    QSqlQuery query(m_db);

    query.prepare("SELECT users_id FROM zachisleniya WHERE groups_id = :groups_id");
    query.bindValue(":groups_id", group->getId());

    QList<int> participantsIDs;

    if (!query.exec()) {
        qDebug() << "Error getting participantsIDs from UpdateGroup func:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int participantID = query.value("users_id").toInt();
        participantsIDs.append(participantID);
    }

    QList<Authentication*> participants = group->getParticipants();

    for (int participantID : participantsIDs) {
        bool found = false;
        for (Authentication* participant : participants) {
            if (participant->getId() == participantID) {
                found = true;
                query.prepare("SELECT fio, password FROM users WHERE id = :id");
                query.bindValue(":id", participantID);
                if (!query.exec()) {
                    qDebug() << "Error getting fio from users table:" << query.lastError().text();
                    return false;
                }
                if (query.next()) {
                    QString dbFio = query.value("fio").toString();
                    QString dbPassword = query.value("password").toString();
                    if (dbFio != participant->GetFIO()) {
                        query.prepare("UPDATE users SET fio = :fio WHERE id = :id");
                        query.bindValue(":fio", participant->GetFIO());
                        query.bindValue(":id", participantID);
                        if (!query.exec()) {
                            qDebug() << "Error updating fio in users table:" << query.lastError().text();
                            return false;
                        }
                    }
                    if (dbPassword != participant->GetPassword()) {
                        query.prepare("UPDATE users SET password = :password WHERE id = :id");
                        participant->HashPassword();
                        query.bindValue(":password", participant->GetPassword());
                        query.bindValue(":id", participantID);
                        if (!query.exec()) {
                            qDebug() << "Error updating password in users table:" << query.lastError().text();
                            return false;
                        }
                    }
                }
                break;
            }
        }
        if (!found) {
            query.prepare("DELETE FROM zachisleniya WHERE users_id = :users_id AND groups_id = :groups_id");
            query.bindValue(":users_id", participantID);
            query.bindValue(":groups_id", group->getId());
            if (!query.exec()) {
                qDebug() << "Error deleting user from zachisleniya table:" << query.lastError().text();
                return false;
            }

            query.prepare("DELETE FROM users WHERE id = :id");
            query.bindValue(":id", participantID);
            if (!query.exec()) {
                qDebug() << "Error deleting user from users table:" << query.lastError().text();
                return false;
            }
        }
    }

    for (Authentication* participant : participants) {
        if (participant->getId() < 0) {
            query.prepare("INSERT INTO users (login, password, fio, avatar_url, role) VALUES (:login, :password, :fio, :avatar_url, :role) RETURNING id");
            query.bindValue(":login", participant->GetLogin());
            participant->HashPassword();
            query.bindValue(":password", participant->GetPassword());
            query.bindValue(":fio", participant->GetFIO());
            query.bindValue(":avatar_url", participant->GetUrlAvatar());
            query.bindValue(":role", (int)(participant->GetCurrentRole()));
            if (!query.exec()) {
                qDebug() << "Error inserting user into users table:" << query.lastError().text();
                return false;
            }

            if (query.next()) {
                int newUserId = query.value(0).toInt();

                query.prepare("INSERT INTO zachisleniya (users_id, groups_id) VALUES (:users_id, :groups_id)");
                query.bindValue(":users_id", newUserId);
                query.bindValue(":groups_id", group->getId());
                if (!query.exec()) {
                    qDebug() << "Error inserting user into zachisleniya table:" << query.lastError().text();
                    return false;
                }
            } else {
                qDebug() << "Error getting new user ID";
                return false;
            }
        }
    }

    return true;
}



Group* DatabaseManager::GetGroupByName(QString groupName) {
    QSqlQuery query(m_db);
    query.prepare("SELECT id, isteachergroup FROM groups WHERE classname = :classname");
    query.bindValue(":classname", groupName);
    query.exec();
    if (!query.next()) {
        qDebug() << "Error executing GetGroupByName query1:" << query.lastError().text();
        return nullptr;
    }
    int groupId = query.value(0).toInt();
    bool isTeacherGroup = query.value(1).toBool();

    QList<Authentication*> participants;
    query.prepare("SELECT u.id, u.fio, u.login, u.password, u.avatar_url, u.role "
                  "FROM users u "
                  "JOIN zachisleniya z ON u.id = z.users_id "
                  "WHERE z.groups_id = :groupId");
    query.bindValue(":groupId", groupId);
    if (!query.exec()) {
        qDebug() << "Error executing GetGroupByName query2:" << query.lastError().text();
    }
    while (query.next()) {
        int userId = query.value(0).toInt();
        QString fio = query.value(1).toString();
        QString login = query.value(2).toString();
        QString password = query.value(3).toString();
        QString avatarUrl = query.value(4).toString();
        int role = query.value(5).toInt();
        Authentication* participant = new Authentication(login, password, userId, fio, avatarUrl, EnumRoles(role), QList<QString>(), false, nullptr);
        participants.append(participant);
    }

    Group* group = new Group(groupId, groupName, isTeacherGroup, participants);
    return group;
}

bool DatabaseManager::SetCourseTutorial(CourseTutorials* tutorial, int32_t courseId) {
    QSqlQuery query(m_db);

    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tutorial->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tutorials1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tutorial->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tutorials2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tutorial->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tutorials3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tutorial->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tutorials4:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO path_course_tutorials (content, \"order\", courses_id1) "
                  "VALUES (:content, :order, :courseId1)");
    query.bindValue(":content", tutorial->getContent());
    query.bindValue(":order", tutorial->getOrder());
    query.bindValue(":courseId1", courseId);

    if (!query.exec()) {
        qDebug() << "Error inserting course tutorial into 'path_course_tutorials' table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::SetCourseMediaFiles(CourseMediaFiles* mediaFiles, int32_t courseId) {
    QSqlQuery query(m_db);

    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", mediaFiles->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course media files1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", mediaFiles->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course media files2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", mediaFiles->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course media files3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", mediaFiles->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course media files4:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO path_course_media_files (title, url, \"order\", type, courses_id1) "
                  "VALUES (:title, :url, :order, :type, :courseId1)");
    query.bindValue(":title", mediaFiles->getTitle());
    query.bindValue(":url", mediaFiles->getUrl());
    query.bindValue(":order", mediaFiles->getOrder());
    query.bindValue(":type", (int)mediaFiles->getTypeFile());
    query.bindValue(":courseId1", courseId);

    if (!query.exec()) {
        qDebug() << "Error inserting course media file into 'path_course_media_files' table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::SetCourseTasks(CourseTask* tasks, int32_t courseId) {
    QSqlQuery query(m_db);

    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tasks->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tasks1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tasks->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tasks2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tasks->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tasks3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tasks->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tasks4:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO path_course_tasks (content, max_mark, memory_limit, \"order\", courses_id1, title) "
                  "VALUES (:content, :maxMark, :memoryLimit, :order, :courseId1, :title)");
    query.bindValue(":content", tasks->getContent());
    query.bindValue(":maxMark", tasks->getMaxMark());
    query.bindValue(":memoryLimit", tasks->getMemoryLimit());
    query.bindValue(":order", tasks->getOrder());
    query.bindValue(":courseId1", courseId);
    query.bindValue(":title", tasks->getTitle());

    if (!query.exec()) {
        qDebug() << "Error inserting course task into 'path_course_tasks' table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::SetCourseTests(CourseTest* tests, int32_t courseId) {
    QSqlQuery query(m_db);

    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tests->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tests1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tests->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tests2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tests->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tests3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" + 1 WHERE courses_id1 = :courseId AND \"order\" >= :order");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", tests->getOrder());
    if (!query.exec()) {
        qDebug() << "Error reordering course tests4:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO path_course_tests (title, max_mark, url_json, \"order\", courses_id1, test_size, time_in_seconds) "
                  "VALUES (:title, :maxMark, :urlJson, :order, :courseId1, :test_size, :time_in_seconds)");
    query.bindValue(":title", tests->getTitle());
    query.bindValue(":maxMark", tests->getMaxMark());
    query.bindValue(":urlJson", tests->getUrlJson());
    query.bindValue(":order", tests->getOrder());
    query.bindValue(":courseId1", courseId);
    query.bindValue(":test_size", tests->getTestSize());
    query.bindValue(":time_in_seconds", tests->getTimeInSeconds());

    if (!query.exec()) {
        qDebug() << "Error inserting course test into 'path_course_tests' table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::DeleteCourseMedia(int32_t courseMediaId, int32_t courseId) {
    QSqlQuery query(m_db);

    query.prepare("SELECT \"order\" FROM path_course_media_files WHERE id = :courseMediaId");
    query.bindValue(":courseMediaId", courseMediaId);
    if (!query.exec()) {
        qDebug() << "Error getting order of course media file:" << query.lastError().text();
        return false;
    }
    if (!query.first()) {
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    int order = query.value(0).toInt();

    query.prepare("DELETE FROM path_course_media_files WHERE id = :courseMediaId");
    query.bindValue(":courseMediaId", courseMediaId);
    if (!query.exec()) {
        qDebug() << "Error deleting course media file:" << query.lastError().text();
        return false;
    }

    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course MF1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course MF2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course MF3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course MF4:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::DeleteCourseTutorial(int32_t courseTutorialId, int32_t courseId) {
    QSqlQuery query(m_db);

    query.prepare("SELECT \"order\" FROM path_course_tutorials WHERE id = :courseTutorialId");
    query.bindValue(":courseTutorialId", courseTutorialId);
    if (!query.exec()) {
        qDebug() << "Error getting order of course tutorial:" << query.lastError().text();
        return false;
    }
    if (!query.first()) {
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    int order = query.value(0).toInt();

    query.prepare("DELETE FROM path_course_tutorials WHERE id = :courseTutorialId");
    query.bindValue(":courseTutorialId", courseTutorialId);
    if (!query.exec()) {
        qDebug() << "Error deleting course tutorial:" << query.lastError().text();
        return false;
    }
    qDebug() << "order:" << order;
    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course T1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course T2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course T3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course T4:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::DeleteCourseTask(int32_t courseTaskId, int32_t courseId) {
    QSqlQuery query(m_db);

    query.prepare("SELECT \"order\" FROM path_course_tasks WHERE id = :courseTaskId");
    query.bindValue(":courseTaskId", courseTaskId);
    if (!query.exec()) {
        qDebug() << "Error getting order of course task:" << query.lastError().text();
        return false;
    }
    if (!query.first()) {
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    int order = query.value(0).toInt();

    query.prepare("DELETE FROM path_course_tasks WHERE id = :courseTaskId");
    query.bindValue(":courseTaskId", courseTaskId);
    if (!query.exec()) {
        qDebug() << "Error deleting course task:" << query.lastError().text();
        return false;
    }

    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course task1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course task2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course task3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course task4:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::DeleteCourseTest(int32_t courseTestId, int32_t courseId) {
    QSqlQuery query(m_db);

    query.prepare("SELECT \"order\" FROM path_course_tests WHERE id = :courseTaskId");
    query.bindValue(":courseTestId", courseTestId);
    if (!query.exec()) {
        qDebug() << "Error getting order of course task:" << query.lastError().text();
        return false;
    }
    if (!query.first()) {
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    int order = query.value(0).toInt();

    query.prepare("DELETE FROM path_course_tests WHERE id = :courseTestId");
    query.bindValue(":courseTestId", courseTestId);
    if (!query.exec()) {
        qDebug() << "Error deleting course test:" << query.lastError().text();
        return false;
    }

    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course test1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course test2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course test3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course test4:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::EditCourseMediaFiles(CourseMediaFiles* mediaFiles) {
    QSqlQuery query(m_db);

    query.prepare("UPDATE path_course_media_files "
                  "SET title = :title, "
                  "    url = :url, "
                  "    \"order\" = :order, "
                  "    type = :type "
                  "WHERE id = :id");
    query.bindValue(":title", mediaFiles->getTitle());
    query.bindValue(":url", mediaFiles->getUrl());
    query.bindValue(":order", mediaFiles->getOrder());
    query.bindValue(":type", (int)(mediaFiles->getTypeFile()));
    query.bindValue(":id", mediaFiles->getId());

    if (!query.exec()) {
        qDebug() << "Error updating course media file:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::EditCourseTutorial(CourseTutorials* tutorials) {
    QSqlQuery query(m_db);

    query.prepare("UPDATE path_course_tutorials "
                  "SET content = :content, "
                  "    \"order\" = :order "
                  "WHERE id = :id");
    query.bindValue(":content", tutorials->getContent());
    query.bindValue(":order", tutorials->getOrder());
    query.bindValue(":id", tutorials->getId());

    if (!query.exec()) {
        qDebug() << "Error updating course tutorial:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::EditCourseTask(CourseTask* task) {
    QSqlQuery query(m_db);

    query.prepare("UPDATE path_course_tasks "
                  "SET content = :content, "
                  "    max_mark = :maxMark, "
                  "    memory_limit = :memoryLimit, "
                  "    \"order\" = :order, "
                  "    title = :title "
                  "WHERE id = :id");
    query.bindValue(":content", task->getContent());
    query.bindValue(":maxMark", task->getMaxMark());
    query.bindValue(":memoryLimit", task->getMemoryLimit());
    query.bindValue(":order", task->getOrder());
    query.bindValue(":id", task->getId());
    query.bindValue(":title", task->getTitle());

    if (!query.exec()) {
        qDebug() << "Error updating course task:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::EditCourseTest(CourseTest* test) {
    QSqlQuery query(m_db);

    query.prepare("UPDATE path_course_tests "
                  "SET title = :title, "
                  "    max_mark = :maxMark, "
                  "    url_json = :urlJson, "
                  "    \"order\" = :order, "
                  "    test_size = :testSize, "
                  "    time_in_seconds = :time_in_seconds "
                  "WHERE id = :id");
    query.bindValue(":title", test->getTitle());
    query.bindValue(":maxMark", test->getMaxMark());
    query.bindValue(":urlJson", test->getUrlJson());
    query.bindValue(":order", test->getOrder());
    query.bindValue(":id", test->getId());
    query.bindValue(":testSize", test->getTestSize());
    query.bindValue(":time_in_seconds",test->getTimeInSeconds());

    if (!query.exec()) {
        qDebug() << "Error updating course test:" << query.lastError().text();
        return false;
    }

    return true;
}

QList<QString> DatabaseManager::GetGroupsOfStudentByCourseId(int32_t courseId) {
    QList<QString> groupNames;
    QSqlQuery query(m_db);
    query.prepare("select classname from groups where id IN (select groups_id from zachisleniya_in_potok where students_groups_union_id = (SELECT students_groups_union_id1 from courses where id =:courseId))");
    query.bindValue(":courseId", courseId);

    if (query.exec()) {
        while (query.next()) {
            groupNames.append(query.value(0).toString());
        }
    }
    else {
        qDebug() << "Error executing the query:" << query.lastError().text();
    }

    return groupNames;
}

QList<Submit*> DatabaseManager::GetTestSubmits(int32_t courseId) {
    QList<Submit*> submits;

    QSqlQuery testQuery(m_db);
    testQuery.prepare("SELECT id, title, max_mark, url_json, \"order\", test_size, time_in_seconds "
                      "FROM path_course_tests "
                      "WHERE courses_id1 = :courseId");
    testQuery.bindValue(":courseId", courseId);

    if (testQuery.exec()) {
        while (testQuery.next()) {
            int32_t testId = testQuery.value(0).toInt();
            QString testTitle = testQuery.value(1).toString();
            int32_t maxMark = testQuery.value(2).toInt();
            QString urlJson = testQuery.value(3).toString();
            int32_t order = testQuery.value(4).toInt();
            int32_t testSize = testQuery.value(5).toInt();
            int32_t timeInSeconds = testQuery.value(6).toInt();

            QSqlQuery submitQuery(m_db);
            submitQuery.prepare("SELECT p.id, p.\"time\", p.verdict, p.notes, p.users_id1 "
                                "FROM path_course_test_submits p "
                                "WHERE p.path_course_tests_id = :testId");
            submitQuery.bindValue(":testId", testId);

            if (submitQuery.exec()) {
                while (submitQuery.next()) {
                    int32_t submitId = submitQuery.value(0).toInt();
                    QDate submitTime = submitQuery.value(1).toDate();
                    int32_t verdict = submitQuery.value(2).toInt();
                    QString notes = submitQuery.value(3).toString();
                    int32_t userId = submitQuery.value(4).toInt();

                    QSqlQuery userQuery(m_db);
                    userQuery.prepare("SELECT fio, login, avatar_url, role "
                                      "FROM users "
                                      "WHERE id = :userId");
                    userQuery.bindValue(":userId", userId);

                    if (userQuery.exec()) {
                        if (userQuery.next()) {
                            QString fio = userQuery.value(0).toString();
                            QString login = userQuery.value(1).toString();
                            QString avatarUrl = userQuery.value(2).toString();
                            int32_t role = userQuery.value(3).toInt();

                            Authentication* student = new Authentication(login, "", userId, fio, avatarUrl, (EnumRoles)(role));
                            CourseTest* test = new CourseTest(testId, order, testTitle, maxMark, urlJson, timeInSeconds, verdict, notes, submitTime, testSize);

                            Submit* submit = new Submit;
                            submit->student = student;
                            submit->work = test;
                            submits.append(submit);
                        }
                    }
                    else { qDebug() << "Error executing the user query:" << userQuery.lastError().text(); }
                }
            }
            else { qDebug() << "Error executing the submit query:" << submitQuery.lastError().text(); }
        }
    }
    else { qDebug() << "Error executing the test query:" << testQuery.lastError().text(); }

    return submits;
}

QList<Submit*> DatabaseManager::GetTaskSubmits(int32_t courseId) {
    QList<Submit*> submits;

    QSqlQuery taskQuery(m_db);
    taskQuery.prepare("SELECT t.id, t.content, t.max_mark, t.memory_limit, t.\"order\", t.title "
                      "FROM path_course_tasks t "
                      "WHERE t.courses_id1 = :courseId");
    taskQuery.bindValue(":courseId", courseId);

    if (taskQuery.exec()) {
        while (taskQuery.next()) {
            int32_t taskId = taskQuery.value(0).toInt();
            QString taskContent = taskQuery.value(1).toString();
            int32_t maxMark = taskQuery.value(2).toInt();
            int32_t memoryLimit = taskQuery.value(3).toInt();
            int32_t order = taskQuery.value(4).toInt();
            QString taskTitle = taskQuery.value(5).toString();

            QSqlQuery submitQuery(m_db);
            submitQuery.prepare("SELECT s.id, s.\"time\", s.verdict, s.notes, s.answer_url, s.users_id1 "
                                "FROM path_course_tasks_submits s "
                                "WHERE s.path_course_tasks_id1 = :taskId");
            submitQuery.bindValue(":taskId", taskId);

            if (submitQuery.exec()) {
                while (submitQuery.next()) {
                    int32_t submitId = submitQuery.value(0).toInt();
                    QDate submitTime = submitQuery.value(1).toDate();
                    int32_t verdict = submitQuery.value(2).toInt();
                    QString notes = submitQuery.value(3).toString();
                    QString answerUrl = submitQuery.value(4).toString();
                    int32_t userId = submitQuery.value(5).toInt();

                    QSqlQuery userQuery(m_db);
                    userQuery.prepare("SELECT fio, login, avatar_url, role "
                                      "FROM users "
                                      "WHERE id = :userId");
                    userQuery.bindValue(":userId", userId);

                    if (userQuery.exec()) {
                        if (userQuery.next()) {
                            QString fio = userQuery.value(0).toString();
                            QString login = userQuery.value(1).toString();
                            QString avatarUrl = userQuery.value(2).toString();
                            int32_t role = userQuery.value(3).toInt();

                            Authentication* student = new Authentication(login, "", userId, fio, avatarUrl, (EnumRoles)(role));
                            CourseTask* task = new CourseTask(taskId, order, taskContent, maxMark, memoryLimit, "", answerUrl, submitTime, verdict, notes, taskTitle);

                            Submit* submit = new Submit;
                            submit->student = student;
                            submit->work = task;
                            submits.append(submit);
                        }
                    }
                    else {
                        qDebug() << "Error executing the user query:" << userQuery.lastError().text();
                    }
                }
            }
            else { qDebug() << "Error executing the submit query:" << submitQuery.lastError().text(); }
        }
    }
    else { qDebug() << "Error executing the task query:" << taskQuery.lastError().text(); }

    return submits;
}

bool DatabaseManager::SetTestSubmits(QList<Submit*> submits) {

    QSqlQuery checkQuery(m_db);
    QSqlQuery submitQuery(m_db);

    for (Submit* submit : submits) {

        if (CourseTest* test = dynamic_cast<CourseTest*>(submit->work)) {

            checkQuery.prepare("SELECT id FROM path_course_test_submits where users_id1 = :user_id AND path_course_tests_id = :test_id");

            checkQuery.bindValue(":user_id", submit->student->getId());
            checkQuery.bindValue(":test_id", test->getId());

            if (!checkQuery.exec()) {
                qDebug() << "Error executing the checkQuery path_course_test_submits:" << checkQuery.lastError().text();
                return false;
            }

            if(checkQuery.first()) {

                int32_t testSubmitId = checkQuery.value("id").toInt();

                submitQuery.prepare("UPDATE path_course_test_submits SET verdict = :verdict, time = now() WHERE id = :id AND verdict != :verdict");

                submitQuery.bindValue(":id", testSubmitId);
                submitQuery.bindValue(":verdict", test->getVerdict());

                if (!submitQuery.exec()) {
                    qDebug() << "Error executing the submit update query path_course_test_submits:" << submitQuery.lastError().text();
                    return false;
                }
            }
            else {

                submitQuery.prepare("INSERT INTO path_course_test_submits (path_course_tests_id, time, verdict, users_id1) "
                                    "VALUES (:path_course_tests_id, now(), :verdict, :users_id1)");

                submitQuery.bindValue(":path_course_tests_id", test->getId());
                submitQuery.bindValue(":verdict", test->getVerdict());
                submitQuery.bindValue(":users_id1", submit->student->getId());

                if (!submitQuery.exec()) {
                    qDebug() << "Error executing the submit insert query path_course_test_submits:" << submitQuery.lastError().text();
                    return false;
                }
            }
        }
    }

    return true;
}

bool DatabaseManager::SetTaskSubmits(QList<Submit*> submits) {

    QSqlQuery checkQuery(m_db);
    QSqlQuery submitQuery(m_db);

    for (Submit* submit : submits) {
        if (CourseTask* task = dynamic_cast<CourseTask*>(submit->work)) {

            checkQuery.prepare("SELECT id FROM path_course_tasks_submits WHERE users_id1 = :user_id AND path_course_tasks_id1 = :task_id");

            checkQuery.bindValue(":user_id", submit->student->getId());
            checkQuery.bindValue(":task_id", task->getId());

            if (!checkQuery.exec()) {
                qDebug() << "Error executing the checkQuery path_course_tasks_submits:" << checkQuery.lastError().text();
                return false;
            }

            if(checkQuery.first()) {
                int32_t taskSubmitId = checkQuery.value("id").toInt();

                submitQuery.prepare("UPDATE path_course_tasks_submits SET verdict = :verdict, time = NOW(), is_checked = TRUE WHERE id = :id AND verdict != :verdict");

                submitQuery.bindValue(":id", taskSubmitId);
                submitQuery.bindValue(":verdict", task->getVerdict());

                if (!submitQuery.exec()) {
                    qDebug() << "Error executing the submit update query path_course_tasks_submits:" << submitQuery.lastError().text();
                    return false;
                }
            }
            else {
                submitQuery.prepare("INSERT INTO path_course_tasks_submits (path_course_tasks_id1, time, verdict,is_checked, users_id1) "
                                    "VALUES (:path_course_tasks_id1, now(), :verdict,true, :users_id1)");

                submitQuery.bindValue(":path_course_tasks_id1", task->getId());
                submitQuery.bindValue(":verdict", task->getVerdict());
                submitQuery.bindValue(":users_id1", submit->student->getId());

                if (!submitQuery.exec()) {
                    qDebug() << "Error executing the submit insert query path_course_tasks_submits:" << submitQuery.lastError().text();
                    return false;
                }
            }
        }
    }

    return true;
}

bool DatabaseManager::SetQuestionList(QString path,int testId)
{
     QSqlQuery query(m_db);
    query.prepare("UPDATE path_course_tests SET url_json = :path WHERE id = :id");
    query.bindValue(":path", path);
    query.bindValue(":id", testId);
    if (!query.exec()) {
        qDebug() << "Error SetQuestionList:" << query.lastError().text();
        return false;
    }
    else return true;
}

bool DatabaseManager::AddStudentTaskSubmit(Submit *submit) {
    QSqlQuery checkQuery(m_db);
    QSqlQuery submitQuery(m_db);

    if (CourseTask* task = dynamic_cast<CourseTask*>(submit->work)) {

        checkQuery.prepare("SELECT id FROM path_course_tasks_submits WHERE users_id1 = :user_id AND path_course_tasks_id1 = :task_id");

        checkQuery.bindValue(":user_id", submit->student->getId());
        checkQuery.bindValue(":task_id", task->getId());

        if (!checkQuery.exec()) {
            qDebug() << "Error executing the checkQuery path_course_tasks_submits:" << checkQuery.lastError().text();
            return false;
        }

        if(checkQuery.first()) {
            int32_t taskSubmitId = checkQuery.value("id").toInt();

            submitQuery.prepare("UPDATE path_course_tasks_submits SET answer_url = :answer_url, time = NOW(), is_checked = FALSE WHERE id = :id");

            submitQuery.bindValue(":id", taskSubmitId);
            submitQuery.bindValue(":answer_url", task->getAnswerUrl());

            if (!submitQuery.exec()) {
                qDebug() << "Error executing the submit update query path_course_tasks_submits:" << submitQuery.lastError().text();
                return false;
            }
        }
        else {
        QSqlQuery submitQuery(m_db);
        submitQuery.prepare("INSERT INTO path_course_tasks_submits (path_course_tasks_id1, \"time\", answer_url, users_id1, is_checked) "
                            "VALUES (:taskId,  NOW(), :answer_url, :userId, :isChecked)");
        submitQuery.bindValue(":taskId", task->getId());
        submitQuery.bindValue(":answer_url", task->getAnswerUrl());
        submitQuery.bindValue(":userId", submit->student->getId());
        submitQuery.bindValue(":isChecked", false);

        if (!submitQuery.exec()) {
            qDebug() << "Error executing the AddStudentTaskSubmit query:" << submitQuery.lastError().text();
            return false;
        }

        return true;
        }
    }

    return true;
}

QList<Submit*> DatabaseManager::GetUncheckedTaskSubmitsFromCourse(int32_t path_course_tasks_id) {

    QList<Submit*> uncheckedSubmits;
    QSqlQuery taskQuery(m_db);
    taskQuery.prepare("SELECT * FROM path_course_tasks where courses_id1 = :id");
    taskQuery.bindValue(":id",path_course_tasks_id);
    if (!taskQuery.exec()) {
        qDebug() << "Error executing the GetUncheckedTaskSubmitsFromCourse query:" << taskQuery.lastError().text();
        return uncheckedSubmits;
    }
    while (taskQuery.next()) {
    int id = taskQuery.value("id").toInt();
    QString content = taskQuery.value("content").toString();
    QString title = taskQuery.value("title").toString();
    int max_mark = taskQuery.value("max_mark").toInt();

    QSqlQuery query(m_db);
    query.prepare("SELECT pcts.id, pcts.\"time\", pcts.verdict, pcts.notes, pcts.answer_url, pcts.is_checked, u.id, u.fio, u.login, u.password, u.avatar_url, u.role "
                  "FROM path_course_tasks_submits AS pcts "
                  "JOIN users u ON pcts.users_id1 = u.id "
                  "WHERE pcts.path_course_tasks_id1 = :path_course_tasks_id AND pcts.is_checked = false");
    query.bindValue(":path_course_tasks_id", id);

    if (!query.exec()) {
        qDebug() << "Error executing the GetUncheckedTaskSubmitsFromCourse query:" << query.lastError().text();
        return uncheckedSubmits;
    }

    while (query.next()) {
        int32_t submitId = query.value(0).toInt();
        QDateTime submitTime = query.value(1).toDateTime();
        int32_t verdict = query.value(2).toInt();
        QString notes = query.value(3).toString();
        QString answerUrl = query.value(4).toString();
        bool isChecked = query.value(5).toBool();
        int32_t userId = query.value(6).toInt();
        QString fio = query.value(7).toString();
        QString login = query.value(8).toString();
        QString password = query.value(9).toString();
        QString avatarUrl = query.value(10).toString();
        int32_t role = query.value(11).toInt();

        Authentication* student = new Authentication(login, password, userId, fio, avatarUrl, static_cast<EnumRoles>(role));
        CourseTask* task = new CourseTask(id,0,content,max_mark,0,"", answerUrl, submitTime.date(), verdict, notes,title);
        Submit* submit = new Submit{student, task};
        uncheckedSubmits.append(submit);
    }
    }
    return uncheckedSubmits;
}

bool DatabaseManager::UpdateCheckedTaskSubmit(Submit* submit) {
    if (CourseTask* task = dynamic_cast<CourseTask*>(submit->work)) {
        QSqlQuery query(m_db);
        query.prepare("SELECT id, verdict, notes FROM path_course_tasks_submits WHERE users_id1 = :userId AND path_course_tasks_id1 = :taskId");
        query.bindValue(":userId", submit->student->getId());
        query.bindValue(":taskId", task->getId());

        if (!query.exec()) {
            qDebug() << "Error executing the SELECT query:" << query.lastError().text();
            return false;
        }

        if (query.next()) {
            int submitId = query.value(0).toInt();
            int verdict = query.value(1).toInt();
            QString notes = query.value(2).toString();
            QSqlQuery updateQuery(m_db);
            updateQuery.prepare("UPDATE path_course_tasks_submits SET is_checked = TRUE, verdict = :verdict, notes = :notes WHERE id = :submitId");
            updateQuery.bindValue(":submitId", submitId);
            updateQuery.bindValue(":verdict", task->getVerdict());
            updateQuery.bindValue(":notes", task->getNotes());

            if (!updateQuery.exec()) {
                qDebug() << "Error executing the UPDATE query:" << updateQuery.lastError().text();
                return false;
            }
        } else {
            QSqlQuery insertQuery(m_db);
            insertQuery.prepare("INSERT INTO path_course_tasks_submits (path_course_tasks_id1, \"time\", verdict, notes, answer_url, users_id1, is_checked) "
                               "VALUES (:taskId, :submitTime, :verdict, :notes, :answerUrl, :userId, true)");
            insertQuery.bindValue(":taskId", task->getId());
            insertQuery.bindValue(":submitTime", task->getSolutionTime());
            insertQuery.bindValue(":verdict", task->getVerdict());
            insertQuery.bindValue(":notes", task->getNotes());
            insertQuery.bindValue(":answerUrl", task->getAnswerUrl());
            insertQuery.bindValue(":userId", submit->student->getId());

            if (!insertQuery.exec()) {
                qDebug() << "Error executing the INSERT query:" << insertQuery.lastError().text();
                return false;
            }
        }

        return true;
    } else {
        qDebug() << "Error: submit->work is not an instance of CourseTask";
        return false;
    }
}


























