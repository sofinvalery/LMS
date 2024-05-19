#include "../../common/authentication/authentication.h"
#include "../../common/course/course_components/coursetest.h"

#ifndef TRANSFERENUM_H
#define TRANSFERENUM_H

enum TransferEnum{
    LOGINING=0,
    GETMAINPAGE=1,
    GETCOURSECOMPONENTS=2,
    GETTESTQUESTION=3,
    SETNEWGROUP=4,
    SETNEWCOURSE=5,
    RECONECT=6,
    GETINFOFORADDINGPOTOK=7,
    SETNEWPOTOK=8,
    GETINFOFORADDINGGROUP=9,
    GETINFOFORAADDINGCOURSE=10,
    GETINFOFOREDITGROUP=11,
    GETGROUP=12,
    UPDATEGROUP=13,
    GETALLCOURSECOMPONENTS=14,
    ADDCOURSECOMPONENT=15,
    EDITCOURSECOMPONENT=16,
    DELETECOURSECOMPONENT=17,
    GETGROUPSBYCOURSEID=18,
    GETSUBMITS=19,
    GETINFOFORSETSUBMITS=20,
    SETSUBMITS=21,
    ADDSTUDENTSUBMIT=22,
    GETUNCHECKEDTASK=23,
};

enum TypeMessage{
    JSONMESSAGE=1,
    REQUESTFILEMESSAGE=2,
    SENDFILEMESSAGE=3
};

struct Submit {
    Authentication* student;
    CourseComponent* work;
};

#endif // TRANSFERENUM_H
