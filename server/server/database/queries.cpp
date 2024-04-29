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
        query.prepare("SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time "
                      "FROM courses AS c "
                      "INNER JOIN zachisleniya_in_potok AS zip ON c.students_groups_union_id1 = zip.students_groups_union_id "
                      "INNER JOIN zachisleniya AS z ON zip.groups_id = z.groups_id "
                      "WHERE z.users_id = :userId");
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
            int sumpoints = 0;
            int maxSumpoints = 0;

            Course* course = new Course(courseId, title, avaUrl, start, end, sumpoints, maxSumpoints);
            courses.append(course);
        }
        while (query.next());
    }
    return courses;
}

void DatabaseManager::GetCourseComponents(Course* course) {
    QSqlQuery pdfQuery(m_db);
    pdfQuery.prepare("SELECT id, `order`, title, url "
                     "FROM path_course_pdfs "
                     "WHERE courses_id1 = :courseId "
                     "ORDER BY `order`");
    pdfQuery.bindValue(":courseId", course->GetCourseId());
    if (!pdfQuery.exec()) {
        qDebug() << "Error executing PDF query:" << pdfQuery.lastError().text();
        return;
    }

    while (pdfQuery.next()) {
        int32_t id = pdfQuery.value("id").toInt();
        int32_t order = pdfQuery.value("order").toInt();
        QString title = pdfQuery.value("title").toString();
        QString url = pdfQuery.value("url").toString();
        //CoursePdf* pdf = new CoursePdf(id, order, title, url);
        //course->AddCourseComponent(pdf);
    }

    QSqlQuery taskQuery(m_db);
    taskQuery.prepare("SELECT pct.id, pct.`order`, pct.content, pct.max_mark, pct.memory_limit, "
                      "GROUP_CONCAT(tf.name SEPARATOR ',') AS allowed_types, "
                      "pcts.answer_url, pcts.time, pcts.verdict, pcts.notes "
                      "FROM path_course_tasks AS pct "
                      "LEFT JOIN type_file_has_lesson_problem AS tfhlp ON pct.id = tfhlp.path_course_tasks_id1 "
                      "LEFT JOIN type_files AS tf ON tfhlp.type_files_id1 = tf.id "
                      "LEFT JOIN path_course_tasks_submits AS pcts ON pct.id = pcts.path_course_tasks_id1 "
                      "WHERE pct.courses_id1 = :courseId "
                      "GROUP BY pct.id "
                      "ORDER BY pct.`order`");
    taskQuery.bindValue(":courseId", course->GetCourseId());
    if (!taskQuery.exec()) {
        qDebug() << "Error executing task query:" << taskQuery.lastError().text();
        return;
    }

    while (taskQuery.next()) {
        int32_t id = taskQuery.value("id").toInt();
        int32_t order = taskQuery.value("order").toInt();
        QString content = taskQuery.value("content").toString();
        int32_t maxMark = taskQuery.value("max_mark").toInt();
        int32_t memoryLimit = taskQuery.value("memory_limit").toInt();
        QString allowedTypes = taskQuery.value("allowed_types").toString();
        QString answerUrl = taskQuery.value("answer_url").toString();
        QDate solutionTime = taskQuery.value("time").toDate();
        int32_t verdict = taskQuery.value("verdict").toInt();
        QString notes = taskQuery.value("notes").toString();
        CourseTask* task = new CourseTask(id, order, content, maxMark, memoryLimit,
                                          allowedTypes, answerUrl, solutionTime,
                                          verdict, notes);
        course->AddCourseComponent(task);
    }

    QSqlQuery testQuery(m_db);
    testQuery.prepare("SELECT pct.id, pct.`order`, pct.title, pct.max_mark, pct.url_json, "
                      "pct.time_in_seconds, pcts.verdict, pcts.notes, pcts.time "
                      "FROM path_course_tests AS pct "
                      "LEFT JOIN path_course_test_submits pcts ON pct.id = pcts.path_course_tests_id "
                      "WHERE pct.courses_id1 = :courseId "
                      "ORDER BY pct.`order`");
    testQuery.bindValue(":courseId", course->GetCourseId());
    if (!testQuery.exec()) {
        qDebug() << "Error executing test query:" << testQuery.lastError().text();
        return;
    }

    while (testQuery.next()) {
        int32_t id = testQuery.value("id").toInt();
        int32_t order = testQuery.value("order").toInt();
        QString title = testQuery.value("title").toString();
        int32_t maxMark = testQuery.value("max_mark").toInt();
        QString urlJson = testQuery.value("url_json").toString();
        int32_t timeInSeconds = testQuery.value("time_in_seconds").toInt();
        int32_t verdict = testQuery.value("verdict").toInt();
        QString notes = testQuery.value("notes").toString();
        QDate time = testQuery.value("time").toDate();
        CourseTest* test = new CourseTest(id, order, title, maxMark, urlJson,
                                          timeInSeconds, verdict, notes, time);
        course->AddCourseComponent(test);
    }

    QSqlQuery tutorialQuery(m_db);
    tutorialQuery.prepare("SELECT id, `order`, content "
                          "FROM path_course_tutorials "
                          "WHERE courses_id1 = :courseId "
                          "ORDER BY `order`");
    tutorialQuery.bindValue(":courseId", course->GetCourseId());
    if (!tutorialQuery.exec()) {
        qDebug() << "Error executing tutorial query:" << tutorialQuery.lastError().text();
        return;
    }

    while (tutorialQuery.next()) {
        int32_t id = tutorialQuery.value("id").toInt();
        int32_t order = tutorialQuery.value("order").toInt();
        QString content = tutorialQuery.value("content").toString();
        CourseTutorials* tutorial = new CourseTutorials(id, order, content);
        course->AddCourseComponent(tutorial);
    }

    QSqlQuery videoQuery(m_db);
    videoQuery.prepare("SELECT id, `order`, title, url "
                       "FROM path_course_videos "
                       "WHERE courses_id1 = :courseId "
                       "ORDER BY `order`");
    videoQuery.bindValue(":courseId", course->GetCourseId());
    if (!videoQuery.exec()) {
        qDebug() << "Error executing video query:" << videoQuery.lastError().text();
        return;
    }

    while (videoQuery.next()) {
        int32_t id = videoQuery.value("id").toInt();
        int32_t order = videoQuery.value("order").toInt();
        QString title = videoQuery.value("title").toString();
        QString url = videoQuery.value("url").toString();
        //CourseVideos* video = new CourseVideos(id, order, title, url);
        //course->AddCourseComponent(video);
    }
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





























