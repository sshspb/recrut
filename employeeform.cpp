/*
 * file: employeeform.cpp
 */

#include "employeeform.h"
#include "ui_employeeform.h"

EmployeeForm::EmployeeForm(QSqlRecord &record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeForm)
{
    ui->setupUi(this);

    ui->nameEdit->setText(record.value(Emp_Name).toString());
    ui->surnameEdit->setText(record.value(Emp_Surname).toString());
    ui->dobEdit->setDate(record.value(Emp_Dob).toDate());
    ui->cityEdit->setText(record.value(Emp_City).toString());
    ui->phoneEdit->setText(record.value(Emp_Phone).toString());
    ui->maleRadioButton->setChecked(record.value(Emp_Sex).toString() == "m");
//    femaleRadioButton->setChecked(record->value(Emp_Sex).toString() != "m");
    ui->emailEdit->setText(record.value(Emp_Email).toString());
    ui->enotCheckBox->setChecked(record.value(Emp_EmailNotif).toBool());
    ui->computerEdit->setText(record.value(Emp_Computer).toString());
    ui->computer_levelEdit->setText(record.value(Emp_CompLevel).toString());
    ui->applicationsEdit->setText(record.value(Emp_Application).toString());
}

EmployeeForm::~EmployeeForm()
{
    delete ui;
}

void EmployeeForm::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void EmployeeForm::getRecord(QSqlRecord &record)
{
    record.setValue(Emp_Name, ui->nameEdit->text());
    record.setValue(Emp_Surname, ui->surnameEdit->text());
    record.setValue(Emp_Dob, ui->dobEdit->date());
    record.setValue(Emp_City, ui->cityEdit->text());
    record.setValue(Emp_Phone, ui->phoneEdit->text());
    if (ui->maleRadioButton->isChecked()) record.setValue(Emp_Sex, "m");
    else record.setValue(Emp_Sex, "f");
    record.setValue(Emp_Email, ui->emailEdit->text());
    if (ui->enotCheckBox->isChecked()) record.setValue(Emp_EmailNotif, true);
    else record.setValue(Emp_EmailNotif, false);
    record.setValue(Emp_Computer, ui->computerEdit->text());
    record.setValue(Emp_CompLevel, ui->computer_levelEdit->text());
    record.setValue(Emp_Application, ui->applicationsEdit->text());

}
