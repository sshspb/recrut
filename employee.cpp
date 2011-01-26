/*
 * file: employee.cpp
 */

#include "employeeform.h"
#include "employee.h"

using namespace Recruter;

Employee::Employee(QWidget *parent)
    : QDialog(parent)
{

  QWidget::setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

  employeeModel = new QSqlTableModel(this);
  employeeModel->setEditStrategy (QSqlTableModel::OnManualSubmit);
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
//  employeeView->setSelectionBehavior(QAbstractItemView::SelectRows);
  employeeView->setColumnHidden(Emp_EmpId, true );
  
  educationModel = new QSqlTableModel(this);
  educationModel->setEditStrategy (QSqlTableModel::OnManualSubmit);
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
  educationView->setSelectionMode(QAbstractItemView::SingleSelection);
//  educationView->setSelectionBehavior(QAbstractItemView::SelectRows);
  educationView->setColumnHidden(Edu_EduId, true );
  educationView->setColumnHidden(Edu_EmpId, true );

  experienceTextEdit = new QTextEdit;

  experienceModel = new QSqlTableModel(this);
  experienceModel->setEditStrategy (QSqlTableModel::OnManualSubmit);
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
  experienceView->setSelectionMode(QAbstractItemView::SingleSelection);
//  experienceView->setSelectionBehavior(QAbstractItemView::SelectRows);
  experienceView->setColumnHidden(Exp_ExpId, true );
  experienceView->setColumnHidden(Exp_EmpId, true );

  languageModel = new QSqlRelationalTableModel(this);
  languageModel->setEditStrategy (QSqlTableModel::OnManualSubmit);
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
//  languageView->setSelectionBehavior(QAbstractItemView::SelectRows);
  languageView->setColumnHidden(Lan_LanId, true);
  languageView->setColumnHidden(Lan_EmpId, true);

  buttonExit = new QPushButton(tr("Выход"), this);
  buttonAddEmployee = new QPushButton(tr("Добавить работника"), this);
  buttonEditEmployee = new QPushButton(tr("Редактировать работника"), this);
  buttonDeleteEmployee = new QPushButton(tr("Удалить работника"), this); buttonDeleteEmployee->setEnabled(false);
  buttonAddEducation = new QPushButton(tr("Добавить образование"), this);
  buttonDeleteEducation = new QPushButton(tr("Удалить образование"), this); buttonDeleteEducation->setEnabled(false);
  buttonAddExperience = new QPushButton(tr("Добавить работу"), this); buttonAddExperience->setEnabled(false);
  buttonDeleteExperience = new QPushButton(tr("Удалить  работу"), this); buttonDeleteExperience->setEnabled(false);
  buttonAddLanguage = new QPushButton(tr("Добавить язык"), this);
  buttonDeleteLanguage = new QPushButton(tr("Удалить язык"), this); buttonDeleteLanguage->setEnabled(false);
  connect(buttonAddEmployee, SIGNAL(clicked()), this, SLOT(addEmployee()));
  connect(buttonEditEmployee, SIGNAL(clicked()), this, SLOT(editEmployee()));
  connect(buttonAddEducation, SIGNAL(clicked()), this, SLOT(addEducation()));
  connect(buttonDeleteEducation, SIGNAL(clicked()), this, SLOT(deleteEducation()));
  connect(buttonAddExperience, SIGNAL(clicked()), this, SLOT(addExperience()));
  connect(buttonAddLanguage, SIGNAL(clicked()), this, SLOT(addLanguage()));
  connect(buttonDeleteEmployee, SIGNAL(clicked()), this, SLOT(deleteEmployee()));
  connect(buttonDeleteExperience, SIGNAL(clicked()), this, SLOT(deleteExperience()));
  connect(buttonDeleteLanguage, SIGNAL(clicked()), this, SLOT(deleteLanguage()));
  connect(buttonExit, SIGNAL(clicked()), this, SLOT(close()));
  connect(employeeView->selectionModel(),
          SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(currentEmployeeChange(const QModelIndex &)));
  connect(employeeModel, SIGNAL(beforeInsert(QSqlRecord&)),
          this, SLOT(beforeInsertEmployee(QSqlRecord&)));
  connect(educationModel, SIGNAL(beforeInsert(QSqlRecord&)),
          this, SLOT(beforeInsertEducation(QSqlRecord&)));
  connect(experienceModel, SIGNAL(beforeInsert(QSqlRecord&)),
          this, SLOT(beforeInsertExperience(QSqlRecord&)));
  connect(languageModel, SIGNAL(beforeInsert(QSqlRecord&)),
          this, SLOT(beforeInsertLanguage(QSqlRecord&)));
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
  experienceLayout->addWidget(experienceTextEdit, 1);
  
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
   /*
    * редактирование записи работника
    */
    // номер редактируемой строки (записи)
    int row = employeeView->currentIndex().row();

    // отправим запись в форму для редактирования
    QSqlRecord record = employeeModel->record(row);
    EmployeeForm employeeForm(record, this);
    employeeForm.exec();

    // заменим запись в модели на отредактированную
    employeeForm.getRecord(record);
    employeeModel->setRecord (row, record);

    // теперь изменения фиксируем в базе данных
    employeeModel->submitAll();

    // однако в submitAll() набор всех записей перечитался,
    // нумерация строк изменилась,
    // надо позиционировать курсор по значению PRIMARY KEY,
    // но если строка новая, id ни в employeeModel ни в record нет
    int id = record.value(Emp_EmpId).toInt(); //
    if (!id) id = idToInsert;
    row = 0;
    while (employeeModel->data(employeeModel->index(row, Emp_EmpId)) != id
           && row < employeeModel->rowCount())
        row++;
    employeeView->setCurrentIndex(employeeModel->index(row, Emp_EmpId));
}

void Employee::editEducation()
{
}

void Employee::editExperience()
{
}

void Employee::editLanguage()
{
}

void Employee::addEducation()
{
    int row = educationModel->rowCount();
    educationModel->insertRow(row);
}

void Employee::addExperience()
{
    int row = experienceModel->rowCount();
    experienceModel->insertRow(row);
}

void Employee::addLanguage()
{
    int row = languageModel->rowCount();
    languageModel->insertRow(row);
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

void Employee::beforeInsertEmployee(QSqlRecord &recordToInsert)
{
   /*
    * Вызывается перед SQL-запросом INSERT, а не перед employeeModel->insertRow()
    */
    // инициализируем значение полей даты создания и PRIMARY KEY
    recordToInsert.setValue(Emp_Created, QDate::currentDate());
    QSqlQuery query;
    query.exec("SELECT nextval('employee_employee_id_seq')");
    if (query.next()) {
        idToInsert = query.value(0).toInt(); // PRIMARY KEY
        recordToInsert.setValue(Emp_EmpId, idToInsert);
    } else {
        qDebug() << "ERROR : in Employee::beforeInsertEmployee nextval id = " << query.value(0).toInt();
    }
}

void Employee::beforeInsertEducation(QSqlRecord &recordToInsert)
{
   /*
    * Вызывается перед SQL-запросом INSERT, а не перед educationModel->insertRow()
    */
    // инициализируем значение FOREIGN KEY
    recordToInsert.setValue(Edu_EmpId, idToInsert);
    // запросим у генератора очередное значение PRIMARY KEY
    QSqlQuery query;
    query.exec("SELECT nextval('education_education_id_seq')");
    if (query.next()) {
        // инициализируем в новой записи значение PRIMARY KEY
        recordToInsert.setValue(Edu_EduId, query.value(0).toInt());
    } else {
        qDebug() << "ERROR : in Employee::beforeInsertEducation nextval id = " << query.value(0).toInt();
    }
}

void Employee::beforeInsertExperience(QSqlRecord &recordToInsert)
{
   /*
    * Вызывается перед SQL-запросом INSERT, а не перед experienceModel->insertRow()
    */
    // инициализируем значение FOREIGN KEY
    recordToInsert.setValue(Exp_EmpId, idToInsert);
    // запросим у генератора очередное значение PRIMARY KEY
    QSqlQuery query;
    query.exec("SELECT nextval('experience_experience_id_seq')");
    if (query.next()) {
        // инициализируем в новой записи значение PRIMARY KEY
        recordToInsert.setValue(Exp_ExpId, query.value(0).toInt());
    } else {
        qDebug() << "ERROR : in Employee::beforeInsertExperience nextval id = " << query.value(0).toInt();
    }
}

void Employee::beforeInsertLanguage(QSqlRecord &recordToInsert)
{
   /*
    * Вызывается перед SQL-запросом INSERT, а не перед languageModel->insertRow()
    */
    // инициализируем значение FOREIGN KEY
    recordToInsert.setValue(Lan_EmpId, idToInsert);
    // запросим у генератора очередное значение PRIMARY KEY
    QSqlQuery query;
    query.exec("SELECT nextval('language_language_id_seq')");
    if (query.next()) {
        // инициализируем в новой записи значение PRIMARY KEY
        recordToInsert.setValue(Lan_LanId, query.value(0).toInt());
    } else {
        qDebug() << "ERROR : in Employee::beforeInsertLanguage nextval id = " << query.value(0).toInt();
    }
}

void Employee::currentEmployeeChange(const QModelIndex & employeeIndex)
{
   /*
    * При перемещении курсора в employeeView на другого работника
    * требуется перечитать наборы данных в дочерних таблицах
    */
    // запомнить изменения в дочерних таблицах
    educationModel->submitAll();
    experienceModel->submitAll();
    languageModel->submitAll();

    // новые выборки в дочерних таблицах по FOREIGN KEY employee_id
    if (!employeeIndex.isValid())
        return;
    QVariant id = employeeModel->data(employeeModel->index(employeeIndex.row(), Emp_EmpId));
    QString clause = QString("employee_id = " + id.toString());
    educationModel->setFilter(clause);
    educationModel->select();
    experienceModel->setFilter(clause);
    experienceModel->select();
    languageModel->setFilter(clause);
    languageModel->select();
    // при добавление записей в дочерних таблицах понадобится FOREIGN KEY
    idToInsert = id.toInt();
}

void Employee::refreshEducationViewHeader()
{
}

void Employee::refreshExperienceViewHeader()
{
}

void Employee::refreshLanguageViewHeader()
{
}

void Employee::close()
{
// qDebug() << "Employee::close()";
    employeeModel->submitAll();
    educationModel->submitAll();
    experienceModel->submitAll();
    languageModel->submitAll();
    QWidget::close();
}

void Employee::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
        if (employeeView->hasFocus()) editEmployee();
        else if (educationView->hasFocus()) editEducation();
        else if (experienceView->hasFocus()) editExperience();
        else if (languageView->hasFocus()) editLanguage();
        else QWidget::keyPressEvent(event);
    default:
        QWidget::keyPressEvent(event);
    }
}
