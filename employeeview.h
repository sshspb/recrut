#ifndef EMPLOYEEVIEW_H
#define EMPLOYEEVIEW_H

//#include <QWidget>
#include <QtGui>
#include <QtSql>
#include "connection.h"

namespace Recruter {

class EmployeeView : public QTextEdit
{
Q_OBJECT

    QSqlQuery *employeeQuery;
    QSqlQuery *educationQuery;
    QSqlQuery *languageQuery;
    QSqlQuery *experienceQuery;
    void prepare(QSqlDatabase db);
    QString getName();
    QString getDob();
    QString getSex();
    QString getAdds();
    QString getTel();
    QString getMail();
    QString getComp();
    QString getApps();
    QString getSpec();
    QString getInst();
    QString getCompany();
    QString getExperience();
    QString getLanguage();

public:
    explicit EmployeeView(QWidget *parent = 0, QSqlDatabase db = Connection::db);
    void select(const QVariant employee_id);
    void display();


signals:

private slots:

public slots:

};

}

#endif // EMPLOYEEVIEW_H
