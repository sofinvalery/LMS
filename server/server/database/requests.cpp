#include "databasemanager.h"
#include "../../common/authentication/authentication.h"


QList<Course*> DatabaseManager::Login(Authentication* auth) {
    QSqlQuery query;
    query.prepare("SELECT u.fio, u.avatar_url, u.role, u.id "
                  "FROM users AS u "
                  "WHERE u.login = :login AND u.password = :password");

    query.bindValue(":login", auth->GetLogin());
    query.bindValue(":password", auth->GetPassword());

    QVariant userId = getScalarValue(query.executedQuery());
    // QList<Course*> courses;
    if (userId.isValid()) {
        QString fullName = query.value("fio").toString();
        QString avatarUrl = query.value("avatar_url").toString();
        EnumRoles userRole = EnumRoles(query.value("role").toInt());
        int32_t userId = query.value("id").toInt();

        QSqlQuery groupsQuery;
        groupsQuery.prepare("SELECT g.classname "
                            "FROM zachisleniya z "
                            "JOIN groups g ON z.groups_id = g.id "
                            "WHERE z.users_id = :userId");
        groupsQuery.bindValue(":userId", userId);
        QSqlQuery groupsResult = executeQuery(groupsQuery.executedQuery());

        QList<QString> userGroups;
        while (groupsResult.next()) {
            userGroups.append(groupsResult.value("classname").toString());
        }

        auth->SetInformationAfterAuthentication(fullName, avatarUrl, userRole, userId, userGroups);
    }
    return GetMainPage(auth);
}

QList<Course*> DatabaseManager::GetMainPage(Authentication* auth) {
    QSqlQuery query;
    QList<Course*> courses;

    if (auth->GetCurrentRole() == STUDENT) {
        query.prepare("SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time "
                      "FROM courses c "
                      "INNER JOIN zachisleniya_in_potok zip ON c.students_groups_union_id1 = zip.students_groups_union_id "
                      "INNER JOIN zachisleniya z ON zip.groups_id = z.groups_id "
                      "WHERE z.users_id = :userId");
    } else if (auth->GetCurrentRole() == TEACHER) {
        query.prepare("SELECT c.id, c.title, c.ava_title_url, c.start_time, c.end_time "
                      "FROM courses c "
                      "INNER JOIN groups g ON c.groups_id = g.id "
                      "INNER JOIN zachisleniya z ON g.id = z.groups_id "
                      "WHERE z.users_id = :userId");
    } else {
        // ...
        return courses;
    }

    query.bindValue(":userId", auth->getId());

    QSqlQuery result = executeQuery(query.executedQuery());

    while (result.next()) {
        int courseId = result.value("id").toInt();
        QString title = result.value("title").toString();
        QString avaUrl = result.value("ava_title_url").toString();
        QDate start = result.value("start_time").toDate();
        QDate end = result.value("end_time").toDate();
        int sumpoints = 0;
        int maxSumpoints = 0;

        Course* course = new Course(courseId, title, avaUrl, start, end, sumpoints, maxSumpoints);
        courses.append(course);
    }

    return courses;
}

void DatabaseManager::GetCourseComponents(Course* course) {
    QSqlQuery pdfQuery;
    pdfQuery.prepare("SELECT id, `order`, title, url "
                     "FROM path_course_pdfs "
                     "WHERE courses_id1 = :courseId "
                     "ORDER BY `order`");
    pdfQuery.bindValue(":courseId", course->GetCourseId());
    QSqlQuery pdfResult = executeQuery(pdfQuery.executedQuery());

    while (pdfResult.next()) {
        int32_t id = pdfResult.value("id").toInt();
        int32_t order = pdfResult.value("order").toInt();
        QString title = pdfResult.value("title").toString();
        QString url = pdfResult.value("url").toString();
        CoursePdf* pdf = new CoursePdf(id, order, title, url);
        course->AddCourseComponent(pdf);
    }

    QSqlQuery taskQuery;
    taskQuery.prepare("SELECT pct.id, pct.`order`, pct.content, pct.max_mark, pct.memory_limit, "
                      "GROUP_CONCAT(tf.name SEPARATOR ',') AS allowed_types, "
                      "pcts.answer_url, pcts.time, pcts.verdict, pcts.notes "
                      "FROM path_course_tasks pct "
                      "LEFT JOIN type_file_has_lesson_problem tfhlp ON pct.id = tfhlp.path_course_tasks_id1 "
                      "LEFT JOIN type_files tf ON tfhlp.type_files_id1 = tf.id "
                      "LEFT JOIN path_course_tasks_submits pcts ON pct.id = pcts.path_course_tasks_id1 "
                      "WHERE pct.courses_id1 = :courseId "
                      "GROUP BY pct.id "
                      "ORDER BY pct.`order`");
    taskQuery.bindValue(":courseId", course->GetCourseId());
    QSqlQuery taskResult = executeQuery(taskQuery.executedQuery());

    while (taskResult.next()) {
        int32_t id = taskResult.value("id").toInt();
        int32_t order = taskResult.value("order").toInt();
        QString content = taskResult.value("content").toString();
        int32_t maxMark = taskResult.value("max_mark").toInt();
        int32_t memoryLimit = taskResult.value("memory_limit").toInt();
        QString allowedTypes = taskResult.value("allowed_types").toString();
        QString answerUrl = taskResult.value("answer_url").toString();
        QDate solutionTime = taskResult.value("time").toDate();
        int32_t verdict = taskResult.value("verdict").toInt();
        QString notes = taskResult.value("notes").toString();
        CourseTask* task = new CourseTask(id, order, content, maxMark, memoryLimit,
                                          allowedTypes, answerUrl, solutionTime,
                                          verdict, notes);
        course->AddCourseComponent(task);
    }

    QSqlQuery testQuery;
    testQuery.prepare("SELECT pct.id, pct.`order`, pct.title, pct.max_mark, pct.url_json, "
                      "pct.time_in_seconds, pcts.verdict, pcts.notes, pcts.time "
                      "FROM path_course_tests pct "
                      "LEFT JOIN path_course_test_submits pcts ON pct.id = pcts.path_course_tests_id "
                      "WHERE pct.courses_id1 = :courseId "
                      "ORDER BY pct.`order`");
    testQuery.bindValue(":courseId", course->GetCourseId());
    QSqlQuery testResult = executeQuery(testQuery.executedQuery());

    while (testResult.next()) {
        int32_t id = testResult.value("id").toInt();
        int32_t order = testResult.value("order").toInt();
        QString title = testResult.value("title").toString();
        int32_t maxMark = testResult.value("max_mark").toInt();
        QString urlJson = testResult.value("url_json").toString();
        int32_t timeInSeconds = testResult.value("time_in_seconds").toInt();
        int32_t verdict = testResult.value("verdict").toInt();
        QString notes = testResult.value("notes").toString();
        QDate time = testResult.value("time").toDate();
        CourseTest* test = new CourseTest(id, order, title, maxMark, urlJson,
                                          timeInSeconds, verdict, notes, time);
        course->AddCourseComponent(test);
    }

    QSqlQuery tutorialQuery;
    tutorialQuery.prepare("SELECT id, `order`, content "
                          "FROM path_course_tutorials "
                          "WHERE courses_id1 = :courseId "
                          "ORDER BY `order`");
    tutorialQuery.bindValue(":courseId", course->GetCourseId());
    QSqlQuery tutorialResult = executeQuery(tutorialQuery.executedQuery());

    while (tutorialResult.next()) {
        int32_t id = tutorialResult.value("id").toInt();
        int32_t order = tutorialResult.value("order").toInt();
        QString content = tutorialResult.value("content").toString();
        CourseTutorials* tutorial = new CourseTutorials(id, order, content);
        course->AddCourseComponent(tutorial);
    }

    QSqlQuery videoQuery;
    videoQuery.prepare("SELECT id, `order`, title, url "
                       "FROM path_course_videos "
                       "WHERE courses_id1 = :courseId "
                       "ORDER BY `order`");
    videoQuery.bindValue(":courseId", course->GetCourseId());
    QSqlQuery videoResult = executeQuery(videoQuery.executedQuery());

    while (videoResult.next()) {
        int32_t id = videoResult.value("id").toInt();
        int32_t order = videoResult.value("order").toInt();
        QString title = videoResult.value("title").toString();
        QString url = videoResult.value("url").toString();
        CourseVideos* video = new CourseVideos(id, order, title, url);
        course->AddCourseComponent(video);
    }
}

QString DatabaseManager::GetTestQuestion(int32_t testId) {
    QSqlQuery query;
    query.prepare("SELECT url_json "
                  "FROM path_course_tests "
                  "WHERE id = :testId");
    query.bindValue(":testId", testId);

    QSqlQuery result = executeQuery(query.executedQuery());

    if (result.next()) {
        return result.value("url_json").toString();
    } else {
        return QString();
    }
}
