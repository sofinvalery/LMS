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



QList<Course*> DatabaseManager::GetMainPage(Authentication* auth) {
    QSqlQuery query(m_db);
    QList<Course*> courses;

    if (auth->GetCurrentRole() == STUDENT) {
        query.prepare("SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time, "
                      "SUM(COALESCE(pts.verdict, 0)) + SUM(COALESCE(pcts.verdict, 0)) AS current_points, "
                      "SUM(COALESCE(pct.max_mark, 0) + COALESCE(pct2.max_mark, 0)) AS max_points "
                      "FROM courses AS c "
                      "INNER JOIN zachisleniya_in_potok AS zip ON c.students_groups_union_id1 = zip.students_groups_union_id "
                      "INNER JOIN zachisleniya AS z ON zip.groups_id = z.groups_id "
                      "LEFT JOIN path_course_tasks AS pct ON pct.courses_id1 = c.id "
                      "LEFT JOIN path_course_tests AS pct2 ON pct2.courses_id1 = c.id "
                      "LEFT JOIN path_course_tasks_submits AS pts ON pct.id = pts.path_course_tasks_id1 AND pts.users_id1 = z.users_id "
                      "LEFT JOIN path_course_test_submits AS pcts ON pct2.id = pcts.path_course_tests_id AND pcts.users_id1 = z.users_id "
                      "WHERE z.users_id = :userId "
                      "GROUP BY c.id, c.title, c.ava_title_url, c.start_time, c.end_time");
    } else if (auth->GetCurrentRole() == TEACHER) {
        query.prepare("SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time "
                      "FROM courses AS c "
                      "INNER JOIN `groups` AS g ON c.groups_id = g.id "
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

    if (!query.first()) {
        qDebug() << "No user found with the given login and password.";
        return courses;
    }
    else {
        do {
            int courseId = query.value("id").toInt();
            QString title = query.value("title").toString();
            QString avaUrl = query.value("ava_title_url").toString();
            QDate start = query.value("start_time").toDate();
            QDate end = query.value("end_time").toDate();
            int currentPoints = 0;
            int maxPoints = 0;
            if (auth->GetCurrentRole() == STUDENT) {
                currentPoints = query.value("current_points").toInt();
                maxPoints = query.value("max_points").toInt();
            }

            Course* course = new Course(courseId, title, avaUrl, start, end, currentPoints, maxPoints);
            courses.append(course);
        }
        while (query.next());
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

    while (query.next()) {
        int32_t id = query.value("id").toInt();
        int32_t order = query.value("order").toInt();
        QString title = query.value("title").toString();
        QString url = query.value("url").toString();
        TypeFile typeFile = (TypeFile)(query.value("type").toInt());
        listComponents->append(new CourseMediaFiles(id, order, title, url, typeFile));
    }

    query.prepare("SELECT id, content, max_mark, memory_limit, \"order\", title "
                  "FROM path_course_tasks "
                  "WHERE courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    if (!query.exec()) {
        qDebug() << "Error executing course tasks query:" << query.lastError().text();
        return listComponents;
    }

    while (query.next()) {
        int32_t id = query.value("id").toInt();
        int32_t order = query.value("order").toInt();
        QString content = query.value("content").toString();
        int32_t maxMark = query.value("max_mark").toInt();
        int32_t memoryLimit = query.value("memory_limit").toInt();
        QString title = query.value("title").toString();

        QStringList allowedTypes;
        query.prepare("SELECT type_files.name "
                      "FROM type_file_has_lesson_problem "
                      "JOIN type_files ON type_file_has_lesson_problem.type_files_id1 = type_files.id "
                      "WHERE type_file_has_lesson_problem.path_course_tasks_id1 = :taskId");
        query.bindValue(":taskId", id);
        if (!query.exec()) {
            qDebug() << "Error executing allowed file types query:" << query.lastError().text();
            return listComponents;
        }

        while (query.next()) {
            allowedTypes.append(query.value("name").toString());
        }

        QString allowedTypeOfFiles = allowedTypes.join(",");
        query.prepare("SELECT answer_url, time, verdict, notes "
                      "FROM path_course_tasks_submits "
                      "WHERE path_course_tasks_id1 = :taskId AND users_id1 = :id");
        query.bindValue(":taskId", id);
        query.bindValue(":id", auth->getId());
        if (!query.exec()) {
            qDebug() << "Error executing task submissions query:" << query.lastError().text();
            return listComponents;
        }

        QString answerUrl;
        QDate solutionTime;
        int32_t verdict = 0;
        QString notes;
        if (query.first()) {
            answerUrl = query.value("answer_url").toString();
            solutionTime = query.value("time").toDate();
            verdict = query.value("verdict").toInt();
            notes = query.value("notes").toString();
        }

        listComponents->append(new CourseTask(id, order, content, maxMark, memoryLimit,
                                                  allowedTypeOfFiles, answerUrl, solutionTime,
                                                  verdict, notes, title));
    }

    query.prepare("SELECT id, title, max_mark, url_json, \"order\", test_size "
                  "FROM path_course_tests "
                  "WHERE courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    if (!query.exec()) {
        qDebug() << "Error executing course tests query:" << query.lastError().text();
        return listComponents;
    }

    while (query.next()) {
        int32_t id = query.value("id").toInt();
        int32_t order = query.value("order").toInt();
        QString title = query.value("title").toString();
        int32_t maxMark = query.value("max_mark").toInt();
        QString urlJson = query.value("url_json").toString();
        int32_t testSize = query.value("test_size").toInt();

        query.prepare("SELECT time, verdict, notes "
                      "FROM path_course_test_submits "
                      "WHERE path_course_tests_id = :testId AND users_id1 = :id");
        query.bindValue(":testId", id);
        query.bindValue(":id", auth->getId());
        if (!query.exec()) {
            qDebug() << "Error executing test submissions query:" << query.lastError().text();
            return listComponents;
        }

        QDate time;
        int32_t verdict = 0;
        QString notes;
        if (query.first()) {
            time = query.value("time").toDate();
            verdict = query.value("verdict").toInt();
            notes = query.value("notes").toString();
        }

        listComponents->append(new CourseTest(id, order, title, maxMark, urlJson, 0, verdict, notes, time, testSize));
    }

    query.prepare("SELECT id, content, \"order\" "
                  "FROM path_course_tutorials "
                  "WHERE courses_id1 = :courseId");
    query.bindValue(":courseId", courseId);
    if (!query.exec()) {
        qDebug() << "Error executing course tutorials query:" << query.lastError().text();
        return listComponents;
    }

    while (query.next()) {
        int32_t id = query.value("id").toInt();
        int32_t order = query.value("order").toInt();
        QString content = query.value("content").toString();
        listComponents->append(new CourseTutorials(id, order, content));
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

    query.prepare("INSERT INTO path_course_tests (title, max_mark, url_json, \"order\", courses_id1, test_size) "
                  "VALUES (:title, :maxMark, :urlJson, :order, :courseId1, :test_size)");
    query.bindValue(":title", tests->getTitle());
    query.bindValue(":maxMark", tests->getMaxMark());
    query.bindValue(":urlJson", tests->getUrlJson());
    query.bindValue(":order", tests->getOrder());
    query.bindValue(":courseId1", courseId);
    query.bindValue(":test_size", tests->getTestSize());

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
    int order = 0;
    if (query.next()) {
        order = query.value(0).toInt();
    }

    query.prepare("DELETE FROM path_course_media_files WHERE id = :courseMediaId");
    query.bindValue(":courseMediaId", courseMediaId);
    if (!query.exec()) {
        qDebug() << "Error deleting course media file:" << query.lastError().text();
        return false;
    }

    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course MF1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course MF2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course MF3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
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
    query.bindValue(":courseTutorials", courseTutorialId);
    if (!query.exec()) {
        qDebug() << "Error getting order of course tutorial:" << query.lastError().text();
        return false;
    }

    int order = 0;
    if (query.next()) {
        order = query.value(0).toInt();
    }

    query.prepare("DELETE FROM path_course_tutorials WHERE id = :courseTutorialId");
    query.bindValue(":courseTutorialId", courseTutorialId);
    if (!query.exec()) {
        qDebug() << "Error deleting course tutorial:" << query.lastError().text();
        return false;
    }

    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course T1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course T2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course T3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
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

    int order = 0;
    if (query.next()) {
        order = query.value(0).toInt();
    }

    query.prepare("DELETE FROM path_course_tasks WHERE id = :courseTaskId");
    query.bindValue(":courseTaskId", courseTaskId);
    if (!query.exec()) {
        qDebug() << "Error deleting course task:" << query.lastError().text();
        return false;
    }

    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course task1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course task2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course task3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
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

    int order = 0;
    if (query.next()) {
        order = query.value(0).toInt();
    }

    query.prepare("DELETE FROM path_course_tests WHERE id = :courseTestId");
    query.bindValue(":courseTestId", courseTestId);
    if (!query.exec()) {
        qDebug() << "Error deleting course test:" << query.lastError().text();
        return false;
    }

    query.prepare("UPDATE path_course_media_files SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course test1:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tutorials SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course test2:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tasks SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
    query.bindValue(":courseId", courseId);
    query.bindValue(":order", order);
    if (!query.exec()) {
        qDebug() << "Error reordering course test3:" << query.lastError().text();
        return false;
    }
    query.prepare("UPDATE path_course_tests SET \"order\" = \"order\" - 1 WHERE \"order\" > :order AND courseId = :courseId");
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
                  "    \"order\" = :order"
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
                  "    \"order\" = :order"
                  "    test_size = :testSize "
                  "WHERE id = :id");
    query.bindValue(":title", test->getTitle());
    query.bindValue(":maxMark", test->getMaxMark());
    query.bindValue(":urlJson", test->getUrlJson());
    query.bindValue(":order", test->getOrder());
    query.bindValue(":id", test->getId());
    query.bindValue(":test_size", test->getTestSize());

    if (!query.exec()) {
        qDebug() << "Error updating course test:" << query.lastError().text();
        return false;
    }

    return true;
}














