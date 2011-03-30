#include "employeeview.h"

using namespace Recruter;

EmployeeView::EmployeeView(QWidget *parent, QSqlDatabase db) :
    QTextEdit(parent)
{
    setReadOnly(true);
    prepare(db);
}

void EmployeeView::prepare(QSqlDatabase db) {

    employeeQuery = new QSqlQuery(db);
    employeeQuery->prepare("SELECT name, surname, dob, city, phone, sex, email, email_notifications, "
                          "computer, computer_level, applications, created "
                          "FROM employee "
                          "WHERE employee_id = :employee_id "
                          "ORDER BY surname ");

    educationQuery = new QSqlQuery(db);
    educationQuery->prepare("SELECT specialty, date_from, date_to, institution, additional "
                          "FROM education "
                          "WHERE employee_id = :employee_id "
                          "ORDER BY date_from ");

    languageQuery = new QSqlQuery(db);
    languageQuery->prepare("SELECT l.language, ll.language_level "
                          "FROM language l "
                          "INNER JOIN language_level ll ON l.language_level = ll.language_level_id "
                          "WHERE l.employee_id = :employee_id");

    experienceQuery = new QSqlQuery(db);
    experienceQuery->prepare("SELECT experience, company_name, date_from, date_to "
                          "FROM experience "
                          "WHERE employee_id = :employee_id "
                          "ORDER BY date_from ");
}


void EmployeeView::select(const QVariant employee_id)
 {
    employeeQuery->bindValue(":employee_id", employee_id);
    educationQuery->bindValue(":employee_id", employee_id);
    languageQuery->bindValue(":employee_id", employee_id);
    experienceQuery->bindValue(":employee_id", employee_id);

    employeeQuery->exec();
    educationQuery->exec();
    languageQuery->exec();
    experienceQuery->exec();
}

void EmployeeView::display()
     {

    QString t = QString();

    if (employeeQuery->next()) {
        t += QString("<h3>") + getName() + QString("</h3>") +
             getDob() + QString(tr(" рожд., ")) + getSex() + QString(tr(" пол<br>")) +
             getAdds() + QString("<br>") +
             QString(tr("Тел.")) + getTel() + QString("<br>") +
             getMail() + QString("<br><br>") +
             getComp() + QString("<br>") + getApps();
    }

    for(int i=0; languageQuery->next(); i++) {
        if(!i) t += QString("<br>");
        t += QString("<br>") + getLanguage();
    }

    for(int i=0; educationQuery->next(); i++) {
        if(i) t += QString("<br>");
        else t += QString(tr("<h4>Образование</h4>"));
        t += getSpec() + QString("<br>") + getInst();
    }

    for(int i=0; experienceQuery->next(); i++) {
        if(i) t += QString("<br>");
        else t += QString(tr("<h4>Работа</h4>"));
        t += getCompany() + QString("<br>") + getExperience();
    }

    QTextDocument * d = document();
    d->setHtml(t);
 }

QString EmployeeView::getName()
{
    return employeeQuery->value(0).toString() +
           QString(" ") + employeeQuery->value(1).toString();
}

QString EmployeeView::getDob()
{
    return employeeQuery->value(2).toString();
}

QString EmployeeView::getSex()
{
    return QString(tr(employeeQuery->value(5).toString() == QString("m") ? "муж" : "жен"));
}

QString EmployeeView::getAdds()
{
    return employeeQuery->value(3).toString();
}

QString EmployeeView::getTel()
{
    return employeeQuery->value(4).toString();
}

QString EmployeeView::getMail()
{
    return employeeQuery->value(6).toString() +
            QString(tr(" : email ")) +
           QString(tr(employeeQuery->value(7).toBool() ? "" : "НЕ")) +
           QString(tr("подтвержден"));
}

QString EmployeeView::getComp()
{
    return QString(tr("Компьютер: ")) + employeeQuery->value(8).toString() +
           QString(tr("; ")) + employeeQuery->value(9).toString() + QString(tr(" уровень"));
}

QString EmployeeView::getApps()
{
     return QString(tr("Владение программами: ")) +employeeQuery->value(10).toString();
}

QString EmployeeView::getSpec()
{
     return educationQuery->value(0).toString() +
            QString(tr(educationQuery->value(4).toBool() ? " (доп.)" : ""));
}

QString EmployeeView::getInst()
{
     return educationQuery->value(1).toString() + QString(" - ") +
             educationQuery->value(2).toString() + QString(" : ") +
            educationQuery->value(3).toString();
}

QString EmployeeView::getExperience()
{
     return experienceQuery->value(0).toString();
}

QString EmployeeView::getCompany()
{
     return experienceQuery->value(2).toString() + QString(" - ") +
             experienceQuery->value(3).toString() + QString(" : ") +
            experienceQuery->value(1).toString();
}

QString EmployeeView::getLanguage()
{
     return languageQuery->value(0).toString() + QString(" - ") +
            languageQuery->value(1).toString();
}
