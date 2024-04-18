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

void XlsxUtils::getExample(QString titleName, QString pathName,QString fileName)
{
    QXlsx::Document xlsxW;
    Format format;
    format.setFontBold(true);
    xlsxW.write(1, 1, "Запишите свои данные вместо зеленого шрифта:",format);
    format.setFontColor(QColor(0,128,0));
    xlsxW.write(2, 1, titleName,format);
    format.setFontBold(0);
    int i=0;
    for(;i<10;i++)
        xlsxW.write(3+i, 1, pathName,format);
    xlsxW.write(3+i, 1, "...",format);
    xlsxW.autosizeColumnWidth();
    if(downloadPath.size()>0&&downloadPath[0]!="")
        xlsxW.saveAs(downloadPath[0]+"/"+fileName);
    else{
        xlsxW.saveAs(QDir::homePath()+"/"+fileName);
    }
}

void XlsxUtils::getExampleForAddingGroup()
{
    getExample("Имя группы","фио студента","ExampleForAddingGroup.xlsx");
}

void XlsxUtils::getExampleForAddingPotok()
{
    getExample("Имя потока","название группы","ExampleForAddingPotok.xlsx");
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

void XlsxUtils::getAddedPotok(AddingData* data)
{
    QXlsx::Document xlsxW;
    Format format;
    format.setFontBold(true);
    xlsxW.write(1, 1, "Добавлен поток",format);
    xlsxW.write(2, 1, "Название потока");
    xlsxW.write(2, 2, data->titleName,format);
    int i=3;
    for(const auto &user : data->pathName)
    {
        xlsxW.write(i, 1, user);
        i++;
    }
    xlsxW.autosizeColumnWidth();
    if(downloadPath.size()>0&&downloadPath[0]!="")
        xlsxW.saveAs(downloadPath[0]+"/"+data->titleName+".xlsx");
    else{
        xlsxW.saveAs(QDir::homePath()+"/"+data->titleName+".xlsx");
    }
}

AddingData *XlsxUtils::parsAddingXlsx(QString path)
{
    AddingData* data = new AddingData();
    QXlsx::Document xlsxR(path);
    data->titleName=xlsxR.read(2,1).toString();
    int i=3;
    QString temp;
    while((temp=xlsxR.read(i++,1).toString())!="")
        data->pathName.append(temp);
    return data;
}
