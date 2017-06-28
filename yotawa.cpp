#include "yotawa.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>


YotaWA::YotaWA()

{
    networkManager = new QNetworkAccessManager();
    cookieJar = new YotaCookieJar();
    cookieJar->load();
    networkManager->setCookieJar(cookieJar);
    connect(networkManager, &QNetworkAccessManager::finished, this, &YotaWA::onResult);
}

void YotaWA::getHome()
{
    networkManager->get(QNetworkRequest(QUrl("https://wa.yota.ru/webapi-v3/view/voice/home")));
}


void YotaWA::onResult(QNetworkReply *reply)
{
    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();
        double balance = root.value("userBalance").toObject().value("value").toDouble();
        QString internet = root.value("optionStates").toArray()[0].toObject().value("descriptionText").toString();
        QString next = root.value("mainDescription").toString();
        QJsonObject price = root.value("price").toObject();
        int priceval = price.value("value").toInt();
        QString pricedesc = price.value("units").toString()+" "+price.value("descriptionText").toString();
        qDebug() << "getAllCookies: " << cookieJar->getAllCookies()[0].value();
        cookieJar->save();
        emit getHomeFinished(balance, internet, next, priceval, pricedesc);
        reply->deleteLater();
    }
}
