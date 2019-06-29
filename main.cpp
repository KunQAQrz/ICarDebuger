//#include "MainWindow.h"
#include <QApplication>
#include "Serial.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    int ret = -1;
    QApplication a(argc, argv);
    //MainWindow* w = MainWindow::NewInstance();
    Serial* w = Serial::NewInstance();

    if(w != NULL)
    {
        w->show();
        //qDebug()<<w->frameSize();
        ret = a.exec();
    }
    delete w;

    return ret;
}
