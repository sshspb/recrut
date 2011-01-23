/*
 * file: config.cpp
 */

#include "config.h"

using namespace Recruter;

// Определения статических атрибутов, здесь им выделится память.
QString Config::password;
QString Config::login;
QString Config::database;
QString Config::host;
QString Config::driver;

/*
 *  класс Config обеспечивает работу с настройками
 */
Config::Config() : settings("Personalis", "Recruter")
{
//    readSettings();  // считать настройки
}

Config::~Config()
{
    writeSettings();  // сохранить настройки
}

void Config::readSettings()
{
    /*
     *  чтение настроек из внешней памяти
     */
    settings.beginGroup("/connection");
    password = settings.value("/password", "").toString();
    login = settings.value("/login", "").toString();
    database = settings.value("/database", "").toString();
    host = settings.value("/host", "").toString();
    driver = settings.value("/driver", "").toString();
    settings.endGroup();
}

void Config::writeSettings()
{
    /*
     *  сохранение настроек во внешней памяти
     */
    settings.beginGroup("/connection");
    settings.setValue("/password", password);
    settings.setValue("/login", login);
    settings.setValue("/database", database);
    settings.setValue("/host", host);
    settings.setValue("/driver", driver);
    settings.endGroup();
}
