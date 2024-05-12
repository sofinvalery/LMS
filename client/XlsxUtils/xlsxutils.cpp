#include "xlsxutils.h"
#include <QStandardPaths>
#include <QDir>
#include "../QXlsx/header/xlsxdocument.h"
#include "../QXlsx/header/xlsxchartsheet.h"
#include "../QXlsx/header/xlsxcellrange.h"
#include "../QXlsx/header/xlsxchart.h"
#include "../QXlsx/header/xlsxrichstring.h"
#include "../QXlsx/header/xlsxworkbook.h"
#include "ClientState/clientstate.h"
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


    QString path;
    if(downloadPath.size()>0&&downloadPath[0]!="")
        path=downloadPath[0]+"/"+group->getClassname()+".xlsx";
    else{
        path=QDir::homePath()+"/"+group->getClassname()+".xlsx";
    }
    int p=1;
    do
    {
        QFileInfo check_file(path);
        if (!check_file.exists()) {
            break;
        } else {
            if(downloadPath.size()>0&&downloadPath[0]!="")
                path=downloadPath[0]+"/"+group->getClassname()+".xlsx";
            else{
                path=QDir::homePath()+"/"+group->getClassname()+".xlsx";
            }
            for(int j=path.size()-1; j>=0; j--)
                if(path[j]=='.')
                {
                    path.insert(j,"("+QString::number(p++)+")");
                    break;
                }
        }
    }
    while(true);
    xlsxW.saveAs(path);
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
    data->pathName.clear();
    delete data;
    data=nullptr;
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

void XlsxUtils::getCourseScoreTable(QList<Submit *> &submits,Course* course, Group* group)
{
    std::sort(group->getParticipants().begin(),group->getParticipants().end(),[](Authentication * a, Authentication* b){return a->GetFIO()<b->GetFIO();});
    std::sort(submits.begin(),submits.end(),[](Submit * a, Submit * b){return a->work->getOrder()<b->work->getOrder();});
    std::sort(submits.begin(),submits.end(),[](Submit * a, Submit * b){return a->student->GetFIO()<b->student->GetFIO();});
    QXlsx::Document xlsxW;
    Format Boldformat;
    Boldformat.setFontBold(true);
    Boldformat.setHorizontalAlignment(Format::AlignHCenter);
    Format doubleFormat;
    doubleFormat.setNumberFormat("0.00%");
    doubleFormat.setHorizontalAlignment(Format::AlignHCenter);
    Format simpleFormat;
    simpleFormat.setHorizontalAlignment(Format::AlignHCenter);
    xlsxW.write(1, 1, "Группа",Boldformat);
    xlsxW.write(1, 2, group->getClassname(),simpleFormat);
    xlsxW.write(3, 1, "логин",simpleFormat);
    xlsxW.write(3, 2, "ФИО",simpleFormat);
    int colums=3;
    QList<int32_t> allSubmits;
    for(auto temp:course->getListComponents())
    {
        CourseTest* courseTest;
        CourseTask* courseTask;
        if ((courseTask = qobject_cast<CourseTask*>(temp)) != nullptr)
        {
            xlsxW.write(3, colums, courseTask->getTitle(),simpleFormat);
            xlsxW.write(4+group->getParticipants().size(), colums++, courseTask->getMaxMark(),simpleFormat);
            allSubmits.append(courseTask->getId());
        }
        else if ((courseTest = qobject_cast<CourseTest*>(temp)) != nullptr)
        {
            xlsxW.write(3, colums, courseTest->getTitle(),simpleFormat);
            xlsxW.write(4+group->getParticipants().size(), colums++, courseTest->getMaxMark(),simpleFormat);
            allSubmits.append(courseTest->getId());
        }
    }
    colums=3+allSubmits.size();
    xlsxW.write(3, colums, "Итого",Boldformat);
    xlsxW.write(3, colums+1, "Процент выполнения",Boldformat);
    xlsxW.write(4+group->getParticipants().size(), 2, "Максимальный бал",Boldformat);
    if(allSubmits.size()>0)
    {
        CellRange range(4+group->getParticipants().size(),3,4+group->getParticipants().size(),3+allSubmits.size()-1);
        xlsxW.write(4+group->getParticipants().size(), allSubmits.size()+3, "=SUM("+range.toString()+")",simpleFormat);
    }
    int rows=4;
    for(Authentication* auth:group->getParticipants())
    {
        xlsxW.write(rows, 1, auth->GetLogin(),simpleFormat);
        xlsxW.write(rows++, 2, auth->GetFIO(),simpleFormat);
    }
    //четвертая строка - первый участник
    // 3 столбец - столбец первого задания
        int i=0;
        for(rows=4;(rows-4)<group->getParticipants().size();rows++)
        {
            for(colums=3;(colums-3)<allSubmits.size();colums++)
            {
                if(i>=submits.size())
                {
                    xlsxW.write(rows, colums, 0,simpleFormat);
                }
                else if(submits[i]->student->getId()!=group->getParticipants()[rows-4]->getId())
                {
                     xlsxW.write(rows, colums, 0,simpleFormat);
                }
                else if(allSubmits[colums-3]!=submits[i]->work->getId())
                {
                    xlsxW.write(rows, colums, 0,simpleFormat);
                }
                else{
                    CourseTest* courseTest;
                    CourseTask* courseTask;
                    if ((courseTask = qobject_cast<CourseTask*>(submits[i]->work)) != nullptr)
                    {
                        xlsxW.write(rows, colums, courseTask->getVerdict(),simpleFormat);
                    }
                    else if ((courseTest = qobject_cast<CourseTest*>(submits[i]->work)) != nullptr)
                    {
                        xlsxW.write(rows, colums, courseTest->getVerdict(),simpleFormat);
                    }
                    i++;
                }
            }
            if(allSubmits.size()>0)
            {
                CellRange range(rows,3,rows,colums-1);
                xlsxW.write(rows, colums, "=SUM("+range.toString()+")",simpleFormat);
                qInfo()<<range.toString();
                QString formula = QString("=%1%2/%3%4").arg(char('A' + colums - 1)).arg(rows).arg( char('A' + allSubmits.size()+3 - 1)).arg(4+group->getParticipants().size());
                xlsxW.write(rows,colums+1,formula,doubleFormat);
            }
        }
    CellRange rangeByTotalProcents(4,4+allSubmits.size(),4+group->getParticipants().size()-1,4+allSubmits.size());
    xlsxW.write(1, allSubmits.size()+7, "Статистика",Boldformat);
    xlsxW.write(3, allSubmits.size()+7, "Средний процент выполнения",simpleFormat);
    xlsxW.write(3, allSubmits.size()+7+1, "Процент вовлечености",simpleFormat);
    xlsxW.write(3, allSubmits.size()+7+2, "Средний процент выполнения вовлеченных",simpleFormat);
    if(allSubmits.size()>0)
    {
        QString formula = QString("=SUM("+rangeByTotalProcents.toString()+")/"+QString::number(group->getParticipants().size()));
        xlsxW.write(4, allSubmits.size()+7, formula,doubleFormat);
        formula = "=COUNTIF("+rangeByTotalProcents.toString()+",\">60%\")/"+QString::number(group->getParticipants().size());
        xlsxW.write(4, allSubmits.size()+7+1, formula,doubleFormat);
        formula = "=IF(COUNTIF("+rangeByTotalProcents.toString()+",\">60%\")>0, SUMIF("+rangeByTotalProcents.toString()+",\">60%\")/COUNTIF("+rangeByTotalProcents.toString()+",\">60%\"), 0)";
        xlsxW.write(4,allSubmits.size()+7+2, formula,doubleFormat);
    }


    xlsxW.autosizeColumnWidth();
    QString path;
    if(downloadPath.size()>0&&downloadPath[0]!="")
        path=downloadPath[0]+"/"+course->GetTitle()+group->getClassname()+".xlsx";
    else{
        path=QDir::homePath()+"/"+course->GetTitle()+group->getClassname()+".xlsx";
    }
    int p=1;
    do
    {
        QFileInfo check_file(path);
        if (!check_file.exists()) {
            break;
        } else {
            if(downloadPath.size()>0&&downloadPath[0]!="")
                path=downloadPath[0]+"/"+course->GetTitle()+group->getClassname()+".xlsx";
            else{
                path=QDir::homePath()+"/"+course->GetTitle()+group->getClassname()+".xlsx";
            }
            for(int j=path.size()-1; j>=0; j--)
                if(path[j]=='.')
                {
                    path.insert(j,"("+QString::number(p++)+")");
                    break;
                }
        }
    }
    while(true);
    ClientState::GetInstance()->ShowNotifacate("Файл оценок добавлен в загрузки\nИмя файла "+course->GetTitle()+"_"+group->getClassname()+"("+QString::number(p-1)+")"+".xlsx","black");
    xlsxW.saveAs(path);
}
