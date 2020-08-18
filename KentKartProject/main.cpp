#include "mainwindow.h"
#include <QApplication>
#include  <QtXml>
#include <QXmlStreamReader>
#include  <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
