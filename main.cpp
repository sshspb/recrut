/*
 * file: main.cpp
 */

#include <QApplication>

#include "connection.h"
#include "employeesview.h"

using namespace Recruter;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");  
  QTextCodec::setCodecForTr(codec);
  Connection connection;
  connection.exec();
  if (!Connection::connected)
    return 1;

//  EmployeesView employees = EmployeesView();
EmployeesView employees;
  // XGA — 1024×768
  // SXGA — 1280×1024
  employees.setGeometry (5, 5, 1000, 700);
  employees.show();

  int ret = app.exec();

  Connection::db.close();

  return ret;
}
