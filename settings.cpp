#include "settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent),
    ui(new Ui::Settings)
{
    settings=new SettingsController();
    ui->setupUi(this);
    switch(settings->getplan())
    {
        case 1: ui->smartphoneRB->setChecked(true); break;
        case 2: ui->tabletRB->setChecked(true); break;
        default: ui->autoRB->setChecked(true); break;
    }
}

void Settings::on_aboutB_clicked()
{
    QMessageBox::about(this, "О программе", "Неофициальное приложение Yota\nВерсия "+QString(VERSION_STRING)+"\nВерсия Qt "+QT_VERSION_STR);
}

void Settings::on_clearSettingsB_clicked()
{
    settings->clearCookies();
    QMessageBox::information(this, "Выполнено", "Авторизация сброшена успешно");
}

void Settings::on_bugtrackerB_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/TTLMaster/Yota-Desktop-App/issues"));
}

void Settings::on_autoRB_pressed()
{
    settings->setplan(0);
}

void Settings::on_smartphoneRB_pressed()
{
    settings->setplan(1);
}

void Settings::on_tabletRB_pressed()
{
    settings->setplan(2);
}
