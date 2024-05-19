#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include<QJsonObject>
#include "../../common/transferEnum/transferEnum.h"
#include "../../common/authentication/authentication.h"
#include "../../common/course/course.h"
#include "../../common/course/course_components/coursetutorials.h"
#include "../database/databaseManager.h"

QJsonObject jsonManager(QJsonObject json,Authentication **auth);



static QJsonObject logining(QJsonObject json,Authentication **auth);

static QJsonObject reconect(QJsonObject json,Authentication **auth);

static QJsonObject getMainPage(QJsonObject json,Authentication **auth);

static QJsonObject getCourseComponents(QJsonObject json,Authentication **auth);

static QJsonObject getTestQuestions(QJsonObject json,Authentication **auth);

static QJsonObject setNewGroup(QJsonObject json,Authentication **auth);

static QJsonObject setNewCourse(QJsonObject json,Authentication **auth);

static QJsonObject getInfoForAddPotok(QJsonObject json,Authentication **auth);

static QJsonObject setNewPotok(QJsonObject json,Authentication **auth);

static QJsonObject getInfoAboutAllGroup(QJsonObject json,Authentication **auth);

static QJsonObject getInfoForAddGroup(QJsonObject json,Authentication **auth);

static QJsonObject getInfoForEditGroup(QJsonObject json,Authentication **auth);

static QJsonObject getInfoForAddCourse(QJsonObject json,Authentication **auth);

static QJsonObject getGroup(QJsonObject json,Authentication **auth);

static QJsonObject updateGroup(QJsonObject json,Authentication **auth);

static QJsonObject getAllCourseComponents(QJsonObject json,Authentication **auth);

static QJsonObject addCourseComponent(QJsonObject json,Authentication **auth);

static QJsonObject editCourseComponent(QJsonObject json,Authentication **auth);

static QJsonObject deleteCourseComponent(QJsonObject json,Authentication **auth);

static QJsonObject getGroupsByCourseId(QJsonObject json,Authentication **auth);

static QJsonObject getSubmits(QJsonObject json,Authentication **auth);

static QJsonObject getInfoForSetSubmits(QJsonObject json,Authentication **auth);

static QJsonObject setSubmits(QJsonObject json,Authentication **auth);

static QJsonObject addStudentSubmit(QJsonObject json,Authentication **auth);

static QJsonObject getUnCheckedTask(QJsonObject json,Authentication **auth);

#endif // JSONMANAGER_H

