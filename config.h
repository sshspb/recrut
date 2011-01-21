/*
 * file: config.h
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

QT_BEGIN_NAMESPACE
class QString;
//class QSettings;
QT_END_NAMESPACE

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
