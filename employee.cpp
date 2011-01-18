#include "employeeform.h"
#include "employee.h"

using namespace Recruter;

Employee::Employee(QWidget *parent)
    : QDialog(parent)
{

  QWidget::setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

  employeeModel = new QSqlTableModel(this);
  employeeModel->setEditStrategy (QSqlTableModel::OnManualSubmit); //  OnManualSubmit OnFieldChange OnRowChange
  employeeModel->setTable("employee");
  employeeModel->select();
  employeeModel->setHeaderData(Emp_EmpId, Qt::Horizontal, tr("ID"));
  employeeModel->setHeaderData(Emp_Name, Qt::Horizontal, tr("Имя Отчество"));
  employeeModel->setHeaderData(Emp_Surname, Qt::Horizontal, tr("Фамилия"));
  employeeModel->setHeaderData(Emp_Dob, Qt::Horizontal, tr("Добавлено"));
  employeeModel->setHeaderData(Emp_City, Qt::Horizontal, tr("Город"));
  employeeModel->setHeaderData(Emp_Phone, Qt::Horizontal, tr("Телефон"));
  employeeModel->setHeaderData(Emp_Sex, Qt::Horizontal, tr("Пол"));
  employeeModel->setHeaderData(Emp_Email, Qt::Horizontal, tr("Эл.почта"));
  employeeModel->setHeaderData(Emp_EmailNotif, Qt::Horizontal, tr("Подтв"));
  employeeModel->setHeaderData(Emp_Computer, Qt::Horizontal, tr("Компьютер"));
  employeeModel->setHeaderData(Emp_CompLevel, Qt::Horizontal, tr("Уровень"));
  employeeModel->setHeaderData(Emp_Application, Qt::Horizontal, tr("Приложение"));
  employeeModel->setHeaderData(Emp_Created, Qt::Horizontal, tr("Создано"));
  employeeView = new QTableView(this);
  employeeView->setModel(employeeModel);
  employeeView->setSelectionMode(QAbstractItemView::SingleSelection);
  employeeView->setSelectionBehavior(QAbstractItemView::SelectRows);
//  employeeView->setColumnHidden(Emp_EmpId, true );
  
  educationModel = new QSqlTableModel(this);
  educationModel->setTable("education");
  educationModel->select();
  educationModel->setSort(3, Qt::AscendingOrder);
  educationModel->setHeaderData(Edu_EduId, Qt::Horizontal, tr("ID"));
  educationModel->setHeaderData(Edu_EmpId, Qt::Horizontal, tr("employee_id"));
  educationModel->setHeaderData(Edu_Specialty, Qt::Horizontal, tr("Специальность"));
  educationModel->setHeaderData(Edu_DateFrom, Qt::Horizontal, tr("С даты"));
  educationModel->setHeaderData(Edu_DateTo, Qt::Horizontal, tr("По дату"));
  educationModel->setHeaderData(Edu_Institution, Qt::Horizontal, tr("Институт"));
  educationModel->setHeaderData(Edu_Additional, Qt::Horizontal, tr("Доп"));
  educationView = new QTableView(this);
  educationView->setModel(educationModel);
  educationView->setColumnHidden(Edu_EduId, true );
  educationView->setColumnHidden(Edu_EmpId, true );

  experienceTextEdit = new QTextEdit;

  experienceModel = new QSqlTableModel(this);
  experienceModel->setTable("experience");
  experienceModel->select();
  experienceModel->setHeaderData(Exp_ExpId, Qt::Horizontal, tr("ID"));
  experienceModel->setHeaderData(Exp_EmpId, Qt::Horizontal, tr("employee_id"));
  experienceModel->setHeaderData(Exp_Experience, Qt::Horizontal, tr("Опыт"));
  experienceModel->setHeaderData(Exp_CompanyName, Qt::Horizontal, tr("Организация"));
  experienceModel->setHeaderData(Exp_DateFrom, Qt::Horizontal, tr("С даты"));
  experienceModel->setHeaderData(Exp_DateTo, Qt::Horizontal, tr("По дату"));
  experienceView = new QTableView(this);
  experienceView->setModel(experienceModel);
  experienceView->setColumnHidden(Exp_ExpId, true );
  experienceView->setColumnHidden(Exp_EmpId, true );

  languageModel = new QSqlRelationalTableModel(this);
  languageModel->setTable("language");
  languageModel->select();
  languageModel->setRelation(Lan_LanguageLevel,
                             QSqlRelation("language_level", "language_level_id", "language_level"));
  languageModel->setHeaderData(Lan_LanId, Qt::Horizontal, tr("ID"));
  languageModel->setHeaderData(Lan_EmpId, Qt::Horizontal, tr("employee_id"));
  languageModel->setHeaderData(Lan_Language, Qt::Horizontal, tr("Язык"));
  languageModel->setHeaderData(Lan_LanguageLevel, Qt::Horizontal, tr("Уровень"));
  languageView = new QTableView(this);
  languageView->setModel(languageModel);
  languageView->setItemDelegate(new QSqlRelationalDelegate(languageView));
  languageView->setSelectionMode(QAbstractItemView::SingleSelection);
  languageView->setSelectionBehavior(QAbstractItemView::SelectRows);
  languageView->setColumnHidden(Lan_LanId, true);
  languageView->setColumnHidden(Lan_EmpId, true);

  buttonExit = new QPushButton(tr("Выход"), this);
  buttonAddEmployee = new QPushButton(tr("Добавить работника"), this);
  buttonEditEmployee = new QPushButton(tr("Редактировать работника"), this);
  buttonDeleteEmployee = new QPushButton(tr("Удалить работника"), this); buttonDeleteEmployee->setEnabled(false);
  buttonAddEducation = new QPushButton(tr("Добавить образование"), this); buttonAddEducation->setEnabled(false);
  buttonDeleteEducation = new QPushButton(tr("Удалить образование"), this); buttonDeleteEducation->setEnabled(false);
  buttonAddExperience = new QPushButton(tr("Добавить работу"), this); buttonAddExperience->setEnabled(false);
  buttonDeleteExperience = new QPushButton(tr("Удалить  работу"), this); buttonDeleteExperience->setEnabled(false);
  buttonAddLanguage = new QPushButton(tr("Добавить язык"), this); buttonAddLanguage->setEnabled(false);
  buttonDeleteLanguage = new QPushButton(tr("Удалить язык"), this); buttonDeleteLanguage->setEnabled(false);
  connect(buttonAddEmployee, SIGNAL(clicked()), this, SLOT(addEmployee()));
  connect(buttonEditEmployee, SIGNAL(clicked()), this, SLOT(editEmployee()));
  connect(buttonAddEducation, SIGNAL(clicked()), this, SLOT(addEducation()));
  connect(buttonAddExperience, SIGNAL(clicked()), this, SLOT(addExperience()));
  connect(buttonAddLanguage, SIGNAL(clicked()), this, SLOT(addLanguage()));
  connect(buttonDeleteEmployee, SIGNAL(clicked()), this, SLOT(deleteEmployee()));
  connect(buttonDeleteEducation, SIGNAL(clicked()), this, SLOT(deleteEducation()));
  connect(buttonDeleteExperience, SIGNAL(clicked()), this, SLOT(deleteExperience()));
  connect(buttonDeleteLanguage, SIGNAL(clicked()), this, SLOT(deleteLanguage()));
  connect(buttonExit, SIGNAL(clicked()), this, SLOT(close()));
  connect(employeeModel, SIGNAL(beforeInsert(QSqlRecord&)),
          this, SLOT(beforeInsertEmployee(QSqlRecord&)));
//  connect(employeeView->selectionModel(), 
//          SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
//          this, SLOT(currentEmployeeChange(const QModelIndex &)));
  connect(educationModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
          this, SLOT(refreshEducationViewHeader()));
  connect(experienceModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
          this, SLOT(refreshExperienceViewHeader()));
  connect(languageModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
          this, SLOT(refreshLanguageViewHeader()));

  QHBoxLayout *employeePanelLayout = new QHBoxLayout;
  employeePanelLayout->addWidget(buttonAddEmployee);
  employeePanelLayout->addWidget(buttonEditEmployee);
  employeePanelLayout->addWidget(buttonDeleteEmployee);
  employeePanelLayout->addStretch(1);
  employeePanelLayout->addWidget(buttonExit);
  QVBoxLayout *employeeLayout = new QVBoxLayout;
  employeeLayout->addLayout(employeePanelLayout);
  employeeLayout->addWidget(employeeView);

  QHBoxLayout *educationPanelLayout = new QHBoxLayout;
  educationPanelLayout->addWidget(buttonAddEducation);
  educationPanelLayout->addWidget(buttonDeleteEducation);
  educationPanelLayout->addStretch(1);
  QVBoxLayout *educationLayout = new QVBoxLayout;
  educationLayout->addWidget(educationView);
  educationLayout->addLayout(educationPanelLayout);
  
  QHBoxLayout *languagePanelLayout = new QHBoxLayout;
  languagePanelLayout->addStretch(1);
  languagePanelLayout->addWidget(buttonAddLanguage);
  languagePanelLayout->addWidget(buttonDeleteLanguage);
  QVBoxLayout *languageLayout = new QVBoxLayout;
  languageLayout->addWidget(languageView);
  languageLayout->addLayout(languagePanelLayout);
  
  QHBoxLayout *experiencePanelLayout = new QHBoxLayout;
  experiencePanelLayout->addWidget(buttonAddExperience);
  experiencePanelLayout->addWidget(buttonDeleteExperience);
  experiencePanelLayout->addStretch(1);
  QVBoxLayout *experienceViewLayout = new QVBoxLayout;
  experienceViewLayout->addWidget(experienceView);
  experienceViewLayout->addLayout(experiencePanelLayout);
  QHBoxLayout *experienceLayout = new QHBoxLayout;
  experienceLayout->addLayout(experienceViewLayout, 1);
  experienceLayout->addWidget(experienceTextEdit, 2);
  
  QHBoxLayout *detailLayout = new QHBoxLayout;
  detailLayout->addLayout(educationLayout, 3);
  detailLayout->addLayout(languageLayout, 1);
  
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(employeeLayout, 3);
  mainLayout->addLayout(detailLayout, 1);
  mainLayout->addLayout(experienceLayout,1);
  setLayout(mainLayout);

  setWindowTitle(tr("Recruter : работнички"));
}

void Employee::addEmployee()
{
  QMessageBox msgBox;
  msgBox.setText(tr("Добавление работника."));
  msgBox.setInformativeText(tr("Добавить запись нового работника?"));
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.setDefaultButton(QMessageBox::No);
  int ret = msgBox.exec();
  if (ret == QMessageBox::Yes)
  {
//    int row = 0;
//    if (employeeView->currentIndex().isValid())
//      row = employeeView->currentIndex().row();

    // строку в модели вставим за последней существующей строкой
    int row = employeeModel->rowCount();
    employeeModel->insertRow(row);

    // далее в editEmployee() нам понадобится номер реактируемой строки row, можно
    // передать его через значение QModelIndex QAbstractItemView::currentIndex () const
    employeeView->setCurrentIndex(employeeModel->index(row, Emp_Name));


    editEmployee();
  }
}

void Employee::editEmployee()
{
    QModelIndex index = employeeView->currentIndex();
    int row = index.row();
    QSqlRecord record = employeeModel->record(row);
    EmployeeForm employeeForm(record, this);
    employeeForm.exec();
    employeeForm.getRecord(record);
    employeeModel->setRecord (row, record);
    employeeModel->submitAll();
    employeeView->setCurrentIndex(index);
}

void Employee::addEducation()
{
}

void Employee::addExperience()
{
}

void Employee::addLanguage()
{
}

void Employee::deleteEmployee()
{
}

void Employee::deleteEducation()
{
}

void Employee::deleteExperience()
{
}

void Employee::deleteLanguage()
{
}

void Employee::beforeInsertEmployee(QSqlRecord &record)
{
    // инициализируем значение полей PRIMARY KEY и даты создания
//    employeeModel->setData(employeeModel->index(row, Emp_Created), QDate::currentDate());
    record.setValue(Emp_Created, QDate::currentDate());
    QSqlQuery query;
    query.exec("SELECT nextval('employee_employee_id_seq')");
    if (query.next()) {
//        employeeModel->setData(employeeModel->index(row, Emp_EmpId), query.value(0));
        record.setValue(Emp_EmpId, query.value(0));

    } else {
        qDebug() << "addEmployee: ERROR ON SELECT nextval('employee_employee_id_seq') return " << query.value(0).toInt();
    }
}

/*
void Employee::currentEmployeeChange(const QModelIndex & employeeIndex)
{
    if (!employeeIndex.isValid())
        return;

    QSqlQuery query;
        query.exec("SELECT nextval('employee_employee_id_seq')");
        if (query.next()) {
            qDebug() << "OK IN SELECT nextval('employee_employee_id_seq') return " << query.value(0);
        }
        else {
            qDebug() << "ERROR ON SELECT nextval('employee_employee_id_seq') return " << query.value(0);
        }

//employeeModel->submitAll();
    QSqlRecord record = employeeModel->record(employeeIndex.row());
    QString clause = QString("employee_id = " + record.value(Emp_EmpId).toString());
    educationModel->setFilter(clause);
    educationModel->select();
    experienceModel->setFilter(clause);
    experienceModel->select();
    languageModel->setFilter(clause);
    languageModel->select();
}
*/
void Employee::refreshEducationViewHeader()
{
}

void Employee::refreshExperienceViewHeader()
{
}

void Employee::refreshLanguageViewHeader()
{
}
