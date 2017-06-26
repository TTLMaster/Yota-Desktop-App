#include "yota.h"
#include "ui_yota.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>
#include <QDesktopServices>

Yota::Yota(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Yota)
{
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Yota::onResult);
    ui->setupUi(this);
    this->update();
}


Yota::~Yota()
{
    delete ui;
}

void Yota::update()
{
    networkManager->get(QNetworkRequest(QUrl("https://wa.yota.ru/webapi-v3/view/voice/home")));
    ui->updating->setText("Обновляю...");
}

void Yota::onResult(QNetworkReply *reply)
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
        ui->balance->setText(QString::number(balance)+"₽");
        ui->internetstatus->setText(internet.replace("\n", " "));
        ui->next->setText(next);
        ui->price->setText(QString::number(priceval)+pricedesc);
        ui->updating->setText("Обновлено "+QDateTime::currentDateTime().toString("d MMM yyyy в hh:mm:ss"));
        reply->deleteLater();
    }
}

void Yota::on_yotabypass_clicked()
{
    QDesktopServices::openUrl(QUrl("http://4pda.ru/forum/index.php?showtopic=596728"));
}

void Yota::on_update_clicked()
{
    this->update();
}
