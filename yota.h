#ifndef YOTA_H
#define YOTA_H

#include <QMainWindow>
#include "yotawa.h"
#include "settings.h"
#include <QtGui>

namespace Ui {
class Yota;
}

class Yota : public QMainWindow
{
    Q_OBJECT

public:
    explicit Yota(QWidget *parent = 0);
    ~Yota();

private slots:
    void onResult(double balance, QString internet, QString next, int price, QString pricedesc);

    void on_yotabypass_clicked();

    void on_update_clicked();

    void on_toolButton_clicked();

    void onError(int code, QString message="Описание ошибки отсутствует.");

private:
    Ui::Yota *ui;
    YotaWA *webapi;
    void update();
    Settings *set;
    QLabel* status;
};

#endif // YOTA_H
