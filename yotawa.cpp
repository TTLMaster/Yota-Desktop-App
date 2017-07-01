#include "yotawa.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>


YotaWA::YotaWA()

{
    settings = new SettingsController();
    networkManager = new QNetworkAccessManager();
    cookieJar = new YotaCookieJar();
    connect(networkManager, &QNetworkAccessManager::finished, this, &YotaWA::onResult);
}

void YotaWA::getHome()
{
    cookieJar->load();
    networkManager->setCookieJar(cookieJar);
    QString plan;
    switch(settings->getplan())
    {
        case 1: plan="voice"; autoplan=0; break;
        case 2: plan="tablet"; autoplan=0; break;
        default:
        autoplan=true;
        if(settings->getLastAutoPlan()==2)
        {
            plan="tablet";
            autoplan=2;
        }
        else
        {
            plan="voice";
            autoplan=1;
        }
    }
    loadPage(plan);
}

void YotaWA::loadPage(QString plan)
{
    networkManager->get(QNetworkRequest(QUrl("https://wa.yota.ru/webapi-v3/view/"+plan+"/home")));
}

void YotaWA::onResult(QNetworkReply *reply)
{
    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();
        if(root.value("_exception").toBool())
        {
            if(root.value("code").toInt()==110600&&autoplan)
            {
                autoplan==2?loadPage("voice"):loadPage("tablet");
                settings->setLastAutoPlan(autoplan==2?1:2);
                autoplan=0;
            }
            else
                emit getHomeError(root.value("code").toInt(), root.value("message").toString());
        }
        else
        {
            if(autoplan)
            {
                autoplan=0;
                if(!settings->getLastAutoPlan())
                    settings->setLastAutoPlan(1);
            }
            double balance = root.value("userBalance").toObject().value("value").toDouble();
            QString internet = root.value("optionStates").toArray()[0].toObject().value("descriptionText").toString();
            QString next = root.value("mainDescription").toString();
            QJsonObject price = root.value("price").toObject();
            int priceval = price.value("value").toInt();
            QString pricedesc = price.value("units").toString()+" "+price.value("descriptionText").toString();
            cookieJar->save();
            emit getHomeFinished(balance, internet, next, priceval, pricedesc);
        }
        reply->deleteLater();
    }
    else
    {
        emit getHomeError(-1, "Нет соединения с сервером");
    }
}
