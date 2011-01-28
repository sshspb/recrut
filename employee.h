/*
 * file: employee.h
 */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QtGui>
#include <QtSql>

namespace Recruter {

class Employee : public QDialog
{
    Q_OBJECT

public:
    Employee(QWidget *parent = 0);

private slots:
    void addEmployee();
    void addEducation();
    void addExperience();
    void addLanguage();
    void deleteEmployee();
    void deleteEducation();
    void deleteExperience();
    void deleteLanguage();
    void beforeInsertEmployee(QSqlRecord &record);
    void beforeInsertEducation(QSqlRecord &record);
    void beforeInsertExperience(QSqlRecord &record);
    void beforeInsertLanguage(QSqlRecord &record);
    void currentEmployeeChange(const QModelIndex & current, const QModelIndex & previous);
    void currentExperienceChange(const QModelIndex & current, const QModelIndex & previous);
    void refreshEducationViewHeader();
    void refreshExperienceViewHeader();
    void refreshLanguageViewHeader();
    void editEmployee();
    void editEducation();
    void editExperience();
    void editLanguage();
    void close();

private:
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

  enum {
    Edu_EduId = 0,
    Edu_EmpId = 1,
    Edu_Specialty = 2,
    Edu_DateFrom = 3,
    Edu_DateTo = 4,
    Edu_Institution = 5,
    Edu_Additional = 6,
  };

  enum {
    Exp_ExpId = 0,
    Exp_EmpId = 1,
    Exp_Experience = 2,
    Exp_CompanyName = 3,
    Exp_DateFrom= 4,
    Exp_DateTo = 5,
  };

  enum {
    Lan_LanId = 0,
    Lan_EmpId = 1,
    Lan_Language = 2,
    Lan_LanguageLevel = 3,
  };

  int idToInsert;
  QSqlDatabase db;
  QSqlTableModel *employeeModel;
  QSqlTableModel *educationModel;
  QSqlTableModel *experienceModel;
  QSqlRelationalTableModel *languageModel;
  QTableView *employeeView;
  QTableView *educationView;
  QTableView *experienceView;
  QTableView *languageView;
  QPlainTextEdit *experienceTextEdit;
  QPushButton *buttonAddEmployee;
  QPushButton *buttonEditEmployee;
  QPushButton *buttonAddEducation;
  QPushButton *buttonAddExperience;
  QPushButton *buttonAddLanguage;
  QPushButton *buttonDeleteEmployee;
  QPushButton *buttonDeleteEducation;
  QPushButton *buttonDeleteExperience;
  QPushButton *buttonDeleteLanguage;
  QPushButton *buttonExit;
  void keyPressEvent(QKeyEvent *event);
};

}

#endif
