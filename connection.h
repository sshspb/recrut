/*
 * file: connection.h
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtGui>
#include <QtSql>

#include "config.h"

namespace Recruter {

class Connection : public QDialog {

Q_OBJECT

public:
    Connection(QWidget *parent = 0);
    static QSqlDatabase db;
    static bool connected;

private slots:
    void accept();

private:
    void createForm();
    void setFields();
    void getFields();
    bool connect();
    Config *config;
    QLabel *loginLabel;
    QLabel *passwordLabel;
    QLabel *driverLabel;
    QLabel *hostLabel;
    QLabel *databaseLabel;
    QLineEdit *driverLineEdit;
    QLineEdit *hostLineEdit;
    QLineEdit *databaseLineEdit;
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *connectButton;
    QPushButton *dataButton;
};

}

#endif
