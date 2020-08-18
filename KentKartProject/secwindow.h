#ifndef SECWINDOW_H
#define SECWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QTextCursor>
#include "mainwindow.h"
namespace Ui {
class SecWindow;
}

class SecWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecWindow(QWidget *parent = 0);
    ~SecWindow();
    int count1;
    QString word1;
    QString word2;
    QString Ref1;

public slots:
     void myFunction();
     void myFunction2();

private slots:

    int on_pushButton_search_clicked();
    int searchFunc(QString text);
    int on_pushButton_search2_clicked();
    int searchFunc2(QString text);

    void on_pushButton_logout_clicked();
    void on_pushButton_openfile_clicked();
    void getTextFile();

    void on_pushButton_clearpage_clicked();

    void refresher(QTextCursor curRefresh);
private:
    Ui::SecWindow *ui;
    MainWindow *mainWin;
//    QTimer *timer;
};

#endif // SECWINDOW_H
