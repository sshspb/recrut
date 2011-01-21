/*
 * file: connection.h
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QSqlDatabase;
class QWidget;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

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
