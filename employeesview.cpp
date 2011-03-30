#include "employeesview.h"

using namespace Recruter;

EmployeesView::EmployeesView(QWidget *parent, QSqlDatabase db) :
    QWidget(parent)
{
    // CREATE VIEW employeeview AS SELECT employee_id, surname, name, pol, age, city FROM employee;
    empHead.push_back(Heading("employee_id", tr("id"), 0));
    empHead.push_back(Heading("surname", tr("Фамилия"), 90));
    empHead.push_back(Heading("name", tr("Имя Отчество"), 150));
    empHead.push_back(Heading("pol", tr("Пол"), 50));
    empHead.push_back(Heading("age", tr("Лет"), 50));
    empHead.push_back(Heading("city", tr("Город"), 120));

    empModel = new QSqlTableModel(this, db);
    empModel->setEditStrategy (QSqlTableModel::OnManualSubmit);
    empModel->setTable("employeeview");
    empModel->select();

    empView = new QTableView(this);
    empView->setModel(empModel);
    empView->setShowGrid(false);
    empView->verticalHeader()->setVisible(false);
    empView->setAlternatingRowColors(true);
    empView->setSelectionMode(QAbstractItemView::SingleSelection);
    empView->setSelectionBehavior(QAbstractItemView::SelectRows);

    for(int i = 0; i < empModel->rowCount(); i++)
        empView->setRowHeight(i, 16);

    for (int i = 0; i < empHead.size(); i++) {
        empModel->setHeaderData(i, Qt::Horizontal, empHead[i].header);
        if (empHead[i].width)
            empView->setColumnWidth (i, empHead[i].width);
        else
            empView->setColumnHidden(i, true );
    }

    detail = new EmployeeView(this, db);

    connect(empView->selectionModel(),
            SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
            this, SLOT(follow(const QModelIndex &, const QModelIndex &)));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(empView);
    mainLayout->addWidget(detail);
    setLayout(mainLayout);

    setWindowTitle(tr("Recruter : работнички"));

    empView->selectRow(0);
}

void EmployeesView::follow(const QModelIndex & current, const QModelIndex & previous )
 {
    if (!current.isValid())
        return;
    QVariant employee_id = empModel->data(empModel->index(current.row(), 0));
    detail->select(employee_id);
    detail->clear();
    detail->display();
    detail->cursorForPosition(QPoint());
}
