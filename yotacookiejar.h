#ifndef YOTACOOKIEJAR_H
#define YOTACOOKIEJAR_H

#include <QList>
#include <QtNetwork>
#include "settingscontroller.h"

class YotaCookieJar : public QNetworkCookieJar
{
public:
    QList<QNetworkCookie> getAllCookies();
    void save();
    void load();
    YotaCookieJar();
private:
    SettingsController *settings;
};

#endif // YOTACOOKIEJAR_H
