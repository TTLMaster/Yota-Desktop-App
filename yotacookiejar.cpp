#include "yotacookiejar.h"

QList<QNetworkCookie> YotaCookieJar::getAllCookies()
{
    return allCookies();
}

void YotaCookieJar::load()
{
    QSettings settings;
    settings.beginGroup(QLatin1String("cookies"));
    QList<QNetworkCookie> savedCookies = QNetworkCookie::parseCookies(settings.value("cookies").toByteArray());

    for (int j = 0; j < savedCookies.count(); j++)
        insertCookie(savedCookies.at(j));
}

void YotaCookieJar::save()
{
    QList<QNetworkCookie> cookies = allCookies();
    QSettings settings;
    settings.beginGroup(QLatin1String("cookies"));
    settings.setValue("cookies", cookies[0].toRawForm());
}
