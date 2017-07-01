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
    connect (webapi, &YotaWA::getHomeError, this, &Yota::onError);
    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());
    status = new QLabel(this);
    statusBar()->addWidget(status);
    QFont fixQtFontBug = ui->balance->font();
    fixQtFontBug.setPointSize(fixQtFontBug.pointSize());
    ui->balance->setFont(fixQtFontBug);
    this->update();
}


Yota::~Yota()
{
    delete ui;
}

void Yota::update()
{
    webapi->getHome();
    status->setText("Обновляю...");
}

void Yota::onResult(double balance, QString internet, QString next, int price, QString pricedesc)
{
    ui->balance->setText(QString::number(balance)+"₽");
    ui->internetstatus->setText(internet.replace("\n", " "));
    ui->next->setText(next);
    ui->price->setText(QString::number(price)+pricedesc);
    status->setText("Обновлено "+QDateTime::currentDateTime().toString("d MMM yyyy в hh:mm:ss"));
}

void Yota::onError(int code, QString message)
{
    QMessageBox errorBox;
    QString myMessage;
    switch (code) {
    case 110403:
        myMessage="Вы не авторизированы!\nУбедитесь, что вы подключены к Интернету через Yota\nЕсли ошибка повторяется, выполните сброс авторизации в настройках";  break;
    case 110600: myMessage="Выбран неверный тариф!\nПереключите тариф в настройках, либо выберите \"Автоматически\""; break;
    case -1:
        myMessage="Ошибка при соединении с сервером.\nПроверьте соединение с Интернетом"; break;
    default:
        myMessage="Неизвестная ошибка";
        break;
    }
    ui->balance->setText("Н/Д");
    ui->internetstatus->setText("Нет данных");
    ui->next->setText("Нет данных");
    ui->price->setText("Нет данных");
    status->setText("Обновлено "+QDateTime::currentDateTime().toString("d MMM yyyy в hh:mm:ss"));
    errorBox.critical(0,"Не удалось получить данные от сервера!",myMessage+"\nОписание ошибки от сервера:\n"+message);
    errorBox.setFixedSize(500,200);
}

void Yota::on_yotabypass_clicked()
{
    QDesktopServices::openUrl(QUrl("http://4pda.ru/forum/index.php?showtopic=596728"));
}

void Yota::on_update_clicked()
{
    this->update();
}

void Yota::on_toolButton_clicked()
{
    Settings *set;
    QWidget *wdg = new QWidget;
    wdg->setWindowTitle("Настройки");
    set = new Settings(wdg);
    wdg->show();
}
