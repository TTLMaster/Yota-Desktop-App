#include "settingscontroller.h"

SettingsController::SettingsController()
{

}

void SettingsController::saveCookies(QByteArray cookies)
{
    settings.beginGroup(QLatin1String("cookies"));
    settings.setValue("cookies", cookies);
    settings.endGroup();
}

QByteArray SettingsController::getCookies()
{
    settings.beginGroup(QLatin1String("cookies"));
    QByteArray value=settings.value("cookies").toByteArray();
    settings.endGroup();
    return value;
}

void SettingsController::clearCookies()
{
    settings.beginGroup(QLatin1String("cookies"));
    settings.remove("");
    settings.endGroup();
}

void SettingsController::setplan(int type)
{
    settings.beginGroup(QLatin1String("usersettings"));
    settings.setValue("plan", type);
    settings.endGroup();
}

int SettingsController::getplan()
{
    settings.beginGroup(QLatin1String("usersettings"));
    int value=settings.value("plan").toInt();
    settings.endGroup();
    return value;
}

int SettingsController::getLastAutoPlan()
{
    settings.beginGroup(QLatin1String("usersettings"));
    int value=settings.value("autoplan").toInt();
    settings.endGroup();
    return value;
}

void SettingsController::setLastAutoPlan(int type)
{
    settings.beginGroup(QLatin1String("usersettings"));
    settings.setValue("autoplan", type);
    settings.endGroup();
}
