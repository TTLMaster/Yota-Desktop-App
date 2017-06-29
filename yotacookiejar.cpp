#include "yotacookiejar.h"

YotaCookieJar::YotaCookieJar()
{
    settings = new SettingsController();
}

QList<QNetworkCookie> YotaCookieJar::getAllCookies()
{
    return allCookies();
}

void YotaCookieJar::load()
{
    QList<QNetworkCookie> savedCookies = QNetworkCookie::parseCookies(settings->getCookies());
    setAllCookies(savedCookies);
}

void YotaCookieJar::save()
{
    QList<QNetworkCookie> cookies = allCookies();
    settings->saveCookies(cookies[0].toRawForm());
}
