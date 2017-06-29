#ifndef SETTINGS_H
#define SETTINGS_H
#include <QWidget>
#include <QObject>
#include <QUrl>
#include <QDesktopServices>
#include <QMainWindow>
#include <QMessageBox>
#include "ui_settings.h"
#include "settingscontroller.h"

class Settings : public QWidget
{
    Q_OBJECT
public:
    Settings(QWidget *parent = 0);

private slots:
    void on_aboutB_clicked();

    void on_clearSettingsB_clicked();

    void on_bugtrackerB_clicked();

    void on_autoRB_pressed();

    void on_smartphoneRB_pressed();

    void on_tabletRB_pressed();

private:
    Ui::Settings *ui;
    SettingsController *settings;

};

#endif // SETTINGS_H
