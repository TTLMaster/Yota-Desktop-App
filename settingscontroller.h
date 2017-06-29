#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H
#include <QSettings>

class SettingsController
{
public:
    SettingsController();
    void saveCookies(QByteArray cookies);
    QByteArray getCookies();
    void clearCookies();
    void setplan(int type);
    int getplan();
    int getLastAutoPlan();
    void setLastAutoPlan(int type);

private:
    QSettings settings;
};

#endif // SETTINGSCONTROLLER_H
