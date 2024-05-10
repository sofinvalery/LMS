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
    Format format;
    format.setFontBold(true);
    xlsxW.write(1, 1, "Группа",format);
    xlsxW.write(1, 2, group->getClassname());
    xlsxW.write(3, 1, "логин");
    xlsxW.write(3, 2, "ФИО");
    int colums=3;
    int maxSum=0;
    double srProcent=0;
    double porogProcent=50.0;
    double srProcentInterested=0;
    int countInterested=0;
    QList<int32_t> allSubmits;
    for(auto temp:course->getListComponents())
    {
        CourseTest* courseTest;
        CourseTask* courseTask;
        if ((courseTask = qobject_cast<CourseTask*>(temp)) != nullptr)
        {
            xlsxW.write(3, colums, courseTask->getTitle());
            xlsxW.write(4+group->getParticipants().size(), colums++, courseTask->getMaxMark());
            allSubmits.append(courseTask->getId());
            maxSum+=courseTask->getMaxMark();
        }
        else if ((courseTest = qobject_cast<CourseTest*>(temp)) != nullptr)
        {
            xlsxW.write(3, colums, courseTest->getTitle());
            xlsxW.write(4+group->getParticipants().size(), colums++, courseTest->getMaxMark());
            allSubmits.append(courseTest->getId());
            maxSum+=courseTest->getMaxMark();
        }
    }
    colums=3+allSubmits.size();
    xlsxW.write(3, colums, "Итого");
    xlsxW.write(4+group->getParticipants().size(), 2, "Максимальный бал");
    xlsxW.write(4+group->getParticipants().size(), allSubmits.size()+3, maxSum);
    int rows=4;
    for(Authentication* auth:group->getParticipants())
    {
        xlsxW.write(rows++, 1, auth->GetLogin());
        xlsxW.write(rows++, 2, auth->GetFIO());
    }
    //четвертая строка - первый участник
    // 3 столбец - столбец первого задания
    if(submits.size()>0)
    {
        int i=0;
        for(rows=4;rows<group->getParticipants().size()-4;rows++)
        {
            int sum=0;
            for(colums=3;colums<allSubmits.size();colums++)
            {
                if(submits[i]->student->getId()!=group->getParticipants()[rows-4]->getId())
                {
                     xlsxW.write(rows, colums, 0);
                }
                else if(allSubmits[colums-3]!=submits[i]->work->getId())
                {
                    xlsxW.write(rows, colums, 0);
                }
                else{
                    CourseTest* courseTest;
                    CourseTask* courseTask;
                    if ((courseTask = qobject_cast<CourseTask*>(submits[i]->work)) != nullptr)
                    {
                        xlsxW.write(rows, colums, courseTask->getVerdict());
                        sum+=courseTask->getVerdict();
                    }
                    else if ((courseTest = qobject_cast<CourseTest*>(submits[i]->work)) != nullptr)
                    {
                        xlsxW.write(rows, colums, courseTest->getVerdict());
                        sum+=courseTask->getVerdict();
                    }
                    i++;
                }
            }
            double temp;
            temp=(double)sum/(double)maxSum*100.0;
            srProcent+=temp;
            if(temp>porogProcent)
            {
                srProcentInterested+=temp;
                countInterested++;
            }
            xlsxW.write(rows, colums, sum);
            xlsxW.write(rows,colums,QString::number(temp, 'f', 2)+"%");
        }
    }

    rows=8+group->getParticipants().size();
    xlsxW.write(rows++, 2, "Статистика",format);
    xlsxW.write(rows, 2, "Средний процент выполнения");
    xlsxW.write(rows, 3, "Процент вовлечености");
    xlsxW.write(rows++, 4, "Средний процент выполнения вовлеченных");
    rows=8+group->getParticipants().size()+1;
    xlsxW.write(rows, 2, QString::number(srProcent/group->getParticipants().size(), 'f', 2)+"%");
    xlsxW.write(rows, 3, QString::number(countInterested/group->getParticipants().size(), 'f', 2)+"%");
    xlsxW.write(rows++, 4, QString::number(srProcentInterested/countInterested, 'f', 2)+"%");


    xlsxW.autosizeColumnWidth();
    if(downloadPath.size()>0&&downloadPath[0]!="")
        xlsxW.saveAs(downloadPath[0]+"/"+course->GetTitle()+"_"+group->getClassname()+".xlsx");
    else{
        xlsxW.saveAs(QDir::homePath()+"/"+course->GetTitle()+"_"+group->getClassname()+".xlsx");
    }
}
