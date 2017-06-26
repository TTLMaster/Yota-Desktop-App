#include "yota.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Yota w;
    w.show();

    return a.exec();
}
