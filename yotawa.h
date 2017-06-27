#ifndef YOTAWA_H
#define YOTAWA_H

#include <QNetworkAccessManager>
#include <QObject>

class YotaWA : public QObject
{
    Q_OBJECT
public:
    YotaWA();

    void getHome();

signals:
    void getHomeFinished(double balance, QString internet, QString next, int price, QString pricedesc);

private:
    QNetworkAccessManager *networkManager;

private slots:
    void onResult(QNetworkReply *reply);
};

#endif // YOTAWA_H
