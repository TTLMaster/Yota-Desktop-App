#ifndef YOTAWA_H
#define YOTAWA_H

#include <QNetworkAccessManager>
#include <QObject>
#include <QtNetwork>
#include "yotacookiejar.h"
#include "settingscontroller.h"


class YotaWA : public QObject
{
    Q_OBJECT
public:
    YotaWA();

    void getHome();

signals:
    void getHomeFinished(double balance, QString internet, QString next, int price, QString pricedesc);
    void getHomeError(int code, QString message="Описание ошибки отсутствует");

private:
    QNetworkAccessManager *networkManager;
    YotaCookieJar *cookieJar;
    SettingsController *settings;
    int autoplan=0;
    void loadPage(QString plan);

private slots:
    void onResult(QNetworkReply *reply);
};

#endif // YOTAWA_H
