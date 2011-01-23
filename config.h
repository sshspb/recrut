/*
 * file: config.h
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QString>

namespace Recruter {

class Config {

private:
    QSettings settings;

public:
    Config();
    ~Config();
    void readSettings();
    void writeSettings();
    static QString password;
    static QString login;
    static QString database;
    static QString host;
    static QString driver;
};
}

#endif // CONFIG_H
