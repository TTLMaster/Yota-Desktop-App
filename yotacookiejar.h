#ifndef YOTACOOKIEJAR_H
#define YOTACOOKIEJAR_H

#include <QList>
#include <QtNetwork>

class YotaCookieJar : public QNetworkCookieJar
{
public:
    QList<QNetworkCookie> getAllCookies();
    void save();
    void load();
};

#endif // YOTACOOKIEJAR_H
