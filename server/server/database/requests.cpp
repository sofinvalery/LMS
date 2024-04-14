#include "databaseManager.h"
#include "../../common/authentication/authentication.h"

#include <QThread>
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
    // query.bindValue(":role", 1);
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
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
        qDebug() << "Error executing query:" << query.lastError().text();
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
        CoursePdf* pdf = new CoursePdf(id, order, title, url);
        course->AddCourseComponent(pdf);
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
        CourseVideos* video = new CourseVideos(id, order, title, url);
        course->AddCourseComponent(video);
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
