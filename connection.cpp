/*
 *  file: connection.cpp
 */

#include <QtGui>
#include <QtSql>

#include "config.h"
#include "connection.h"

using namespace Recruter;

Connection::Connection(QWidget *parent)
    : QDialog(parent)
{
    connected = false;
    createForm();
    setFields();
}

void Connection::createForm()
{
    passwordLabel = new QLabel(tr("Пароль"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    loginLabel = new QLabel(tr("Пользователь"));
    loginLineEdit = new QLineEdit;
    databaseLabel = new QLabel(tr("База"));
    databaseLineEdit = new QLineEdit;
    hostLabel = new QLabel(tr("Узел"));
    hostLineEdit = new QLineEdit;
    driverLabel = new QLabel(tr("Драйвер"));
    driverLineEdit = new QLineEdit;

    connectButton = new QPushButton(tr("Соединить"));
    connectButton->setDefault(true);
    dataButton = new QPushButton(tr("Дополнительно..."));
    dataButton->setCheckable(true);
    dataButton->setAutoDefault(false);

    QGroupBox *userGroup = new QGroupBox;
    QWidget *extension = new QWidget;

    QObject::connect(dataButton, SIGNAL(toggled(bool)), extension, SLOT(setVisible(bool)));
    QObject::connect(connectButton, SIGNAL(clicked()), this, SLOT(accept ()));

    QGridLayout *userLayout = new QGridLayout;
    userLayout->setVerticalSpacing (15);
    userLayout->addWidget(passwordLabel, 0, 1);
    userLayout->addWidget(passwordLineEdit, 0, 2, 1, 2);
    userLayout->addWidget(connectButton, 1, 2, 1, 2);
    userLayout->addWidget(dataButton, 2, 3, 1, 2);
    userGroup->setLayout(userLayout);

    QGridLayout *dataLayout = new QGridLayout;
    dataLayout->addWidget(loginLabel, 0, 0);
    dataLayout->addWidget(loginLineEdit, 0, 1, 1, 2);
    dataLayout->addWidget(databaseLabel, 1, 0);
    dataLayout->addWidget(databaseLineEdit, 1, 1, 1, 2);
    dataLayout->addWidget(hostLabel, 2, 0);
    dataLayout->addWidget(hostLineEdit, 2, 1, 1, 2);
    dataLayout->addWidget(driverLabel, 3, 0);
    dataLayout->addWidget(driverLineEdit, 3, 1, 1, 2);
    extension->setLayout(dataLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(userGroup);
    mainLayout->addWidget(extension);
    setLayout(mainLayout);

    setWindowTitle(tr("Параметры соединения"));
    extension->hide();
}

void Connection::setFields()
{
    passwordLineEdit->setText(Config::password);
    loginLineEdit->setText(Config::login);
    databaseLineEdit->setText(Config::database);
    hostLineEdit->setText(Config::host);
    driverLineEdit->setText(Config::driver);
}

void Connection::getFields()
{
    Config::password = passwordLineEdit->text();
    Config::login = loginLineEdit->text();
    Config::database = databaseLineEdit->text();
    Config::host = hostLineEdit->text();
    Config::driver = driverLineEdit->text();
}

bool Connection::connect()
{
/*
 * Для соединения с базой необходимо вызвать статический
 * метод QSqlDatabase::addDatabase() и в созданном
 * экземпляре класса выполнить метод open().
 */
    db = QSqlDatabase::addDatabase(Config::driver);
    db.setHostName(Config::host);
    db.setDatabaseName(Config::database);
    db.setUserName(Config::login);
    db.setPassword(Config::password);
    connected = db.open();
    if (!connected) {
        QSqlError er = db.lastError();
        QMessageBox::information(0, "Error", er.text());
    }
    return connected;
}

void Connection::accept()
{
    getFields();
    connect();
    close();
}


