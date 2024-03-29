#ifndef JSONMANEGER_H
#define JSONMANEGER_H

#include<QJsonObject>
#include "../../common/transferEnum/transferEnum.h"
#include "../../common/authentication/authentication.h"
#include "../../common/course/course.h"
#include "../../common/course/course_components/coursetutorials.h"
#include "../database/databaseManager.h"

QJsonObject jsonManager(QJsonObject json,Authentication *auth);

static QJsonObject logining(QJsonObject json,Authentication *auth);

static QJsonObject getMainPage(QJsonObject json,Authentication *auth);

static QJsonObject getCourseComponents(QJsonObject json,Authentication *auth);

static QJsonObject getTestQuestions(QJsonObject json,Authentication *auth);

static QJsonObject setNewGroupStudents(QJsonObject json,Authentication *auth);

static QJsonObject setNewTest(QJsonObject json,Authentication *auth);

static QJsonObject setNewCourse(QJsonObject json,Authentication *auth);





#endif // JSONMANEGER_H
