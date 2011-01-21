/*
 * file: config.cpp
 */

#include "config.h"

using namespace Recruter;

Config::Config() : settings("Personalis", "Recruter")
{
}

Config::~Config()
{
    writeSettings();
}

void Config::readSettings()
{
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
    settings.beginGroup("/connection");
    settings.setValue("/password", password);
    settings.setValue("/login", login);
    settings.setValue("/database", database);
    settings.setValue("/host", host);
    settings.setValue("/driver", driver);
    settings.endGroup();
}
