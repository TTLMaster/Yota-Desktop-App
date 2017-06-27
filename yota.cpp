#include "yota.h"
#include "ui_yota.h"
#include <QUrl>
#include <QDesktopServices>

Yota::Yota(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Yota)
{
    webapi = new YotaWA();
    connect (webapi, &YotaWA::getHomeFinished, this, &Yota::onResult);
    ui->setupUi(this);
    this->update();
}


Yota::~Yota()
{
    delete ui;
}

void Yota::update()
{
    webapi->getHome();
    ui->updating->setText("Обновляю...");
}

void Yota::onResult(double balance, QString internet, QString next, int price, QString pricedesc)
{
    ui->balance->setText(QString::number(balance)+"₽");
    ui->internetstatus->setText(internet.replace("\n", " "));
    ui->next->setText(next);
    ui->price->setText(QString::number(price)+pricedesc);
    ui->updating->setText("Обновлено "+QDateTime::currentDateTime().toString("d MMM yyyy в hh:mm:ss"));
}

void Yota::on_yotabypass_clicked()
{
    QDesktopServices::openUrl(QUrl("http://4pda.ru/forum/index.php?showtopic=596728"));
}

void Yota::on_update_clicked()
{
    this->update();
}
