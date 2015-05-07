#include "aplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    APlay w;
    w.show();

    return a.exec();
}

