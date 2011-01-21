/*
 * file: main.cpp
 */

#include <QApplication>

#include "config.h"
#include "connection.h"
#include "employee.h"

using namespace Recruter;

// Определения статических переменных, здесь им выделяется память.
QSqlDatabase Connection::db;
bool Connection::connected;
QString Config::password;
QString Config::login;
QString Config::database;
QString Config::host;
QString Config::driver;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");  
  QTextCodec::setCodecForTr(codec);

  Config config;
  config.readSettings();

  Connection connection;
  connection.exec();
  if (!Connection::connected)
    return 1;
  
  Employee employee;
  // XGA — 1024×768
  // SXGA — 1280×1024
  employee.setGeometry (5, 5, 1000, 700);
  employee.show();
  return employee.exec();
}
