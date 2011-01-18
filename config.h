#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace Recruter {

class Config {

private:
    QSettings settings(const QString & organization, const QString & application = QString(), QObject * parent = 0);

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
