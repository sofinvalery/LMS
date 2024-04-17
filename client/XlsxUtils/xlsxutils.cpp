#include "xlsxutils.h"
#include <QStandardPaths>
#include <QDir>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


XlsxUtils* XlsxUtils::s_Instance = nullptr;

XlsxUtils::XlsxUtils(QObject *parent)
    : QObject{parent}
{
    downloadPath=QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
}

void XlsxUtils::getExampleForAddingGroup()
{
    QXlsx::Document xlsxW;
    Format format;
    format.setFontBold(true);
    xlsxW.write(1, 1, "Запишите свои данные вместо зеленого шрифта:",format);
    format.setFontColor(QColor(0,128,0));
    xlsxW.write(2, 1, "Имя группы",format);
    format.setFontBold(0);
    int i=0;
    for(;i<10;i++)
        xlsxW.write(3+i, 1, "фио студента",format);
    xlsxW.write(3+i, 1, "...",format);
    xlsxW.autosizeColumnWidth();
    if(downloadPath.size()>0&&downloadPath[0]!="")
    xlsxW.saveAs(downloadPath[0]+"/ExampleForAddingGroup.xlsx");
    else{
        xlsxW.saveAs(QDir::homePath()+"/ExampleForAddingGroup.xlsx");
    }
}

void XlsxUtils::getAddedGroup(Group* group)
{
    QXlsx::Document xlsxW;
    Format format;
    format.setFontBold(true);
    xlsxW.write(1, 1, "Добавленная группа",format);
    xlsxW.write(2, 1, "Имя группы");
    xlsxW.write(2, 2, group->getClassname(),format);
    if(group->getIsTeacherGroup())
    {
        xlsxW.write(3, 1, "Это группа учителей",format);
    }
    else
    {
        xlsxW.write(3, 1, "Это группа студентов",format);
    }
    xlsxW.write(4, 1, "Логин",format);
    xlsxW.write(4, 2, "Пароль",format);
    xlsxW.write(4, 3, "ФИО",format);
    int i=5;
    for(auto user : group->getParticipants())
    {
        xlsxW.write(i, 1, user->GetLogin());
        if(user->GetPassword().size()<25)
        xlsxW.write(i, 2, user->GetPassword());
        else xlsxW.write(i, 2, "???");
        xlsxW.write(i, 3, user->GetFIO());
        i++;
    }
    xlsxW.autosizeColumnWidth();
    if(downloadPath.size()>0&&downloadPath[0]!="")
        xlsxW.saveAs(downloadPath[0]+"/"+group->getClassname()+".xlsx");
    else{
        xlsxW.saveAs(QDir::homePath()+"/"+group->getClassname()+".xlsx");
    }
}
