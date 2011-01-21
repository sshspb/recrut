/*
 * file: employeeform.h
 */

#ifndef EMPLOYEEFORM_H
#define EMPLOYEEFORM_H

#include <QtGui>
#include <QtSql>

namespace Ui {
    class EmployeeForm;
}

class EmployeeForm : public QDialog {
    Q_OBJECT

public:
    EmployeeForm(QSqlRecord &record, QWidget *parent = 0);
    ~EmployeeForm();
    void getRecord(QSqlRecord &record);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::EmployeeForm *ui;
    enum {
      Emp_EmpId = 0,
      Emp_Name = 1,
      Emp_Surname = 2,
      Emp_Dob = 3,
      Emp_City = 4,
      Emp_Phone = 5,
      Emp_Sex = 6,
      Emp_Email = 7,
      Emp_EmailNotif = 8,
      Emp_Computer = 9,
      Emp_CompLevel = 10,
      Emp_Application = 11,
      Emp_Created = 12,
    };

};

#endif // EMPLOYEEFORM_H
