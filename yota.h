#ifndef YOTA_H
#define YOTA_H

#include <QMainWindow>
#include <QNetworkAccessManager>

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
    void onResult(QNetworkReply *reply);

    void on_yotabypass_clicked();

    void on_update_clicked();

private:
    Ui::Yota *ui;
    QNetworkAccessManager *networkManager;
    void update();
};

#endif // YOTA_H
