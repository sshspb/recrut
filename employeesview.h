#ifndef EMPLOYEESVIEW_H
#define EMPLOYEESVIEW_H

//#include <QWidget>
#include <QtGui>
#include <QtSql>
#include "connection.h"
#include "employeeview.h"

namespace Recruter {

class EmployeesView : public QWidget
{
Q_OBJECT

struct Heading
{
    Heading(const QString &f = QString(), const QString &h = QString(), int w = 0): field(f), header(h), width(w) {}
    QString field;
    QString header;
    int width;
};
QVector<Heading> empHead;

QSqlTableModel *empModel;
QTableView *empView;
EmployeeView *detail;

public:
//    explicit EmployeesView(QWidget *parent = 0, QSqlDatabase db = Connection::db);
    EmployeesView(QWidget *parent = 0, QSqlDatabase db = Connection::db);

signals:

private slots:
//    void addEmployee();
//    void deleteEmployee();
//    void editEmployee();
    void follow(const QModelIndex & current, const QModelIndex & previous);

public slots:

};

}

#endif // EMPLOYEESVIEW_H
