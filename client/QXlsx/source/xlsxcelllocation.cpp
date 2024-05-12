// xlsxcelllocation.cpp

#include "../header/xlsxcelllocation.h"

#include "../header/xlsxcell.h"
#include "../header/xlsxglobal.h"

#include <QList>
#include <QObject>
#include <QString>
#include <QVector>
#include <QtGlobal>

QT_BEGIN_NAMESPACE_XLSX

CellLocation::CellLocation()
{
    col = -1;
    row = -1;

    cell.reset();
}

QT_END_NAMESPACE_XLSX
