#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPointer>
#include <QMainWindow>
#include <QXmlStreamReader>
#include <QDomDocument>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QDomDocument xmlBOM;
    QList<QString> userID;
    QList<QString> userPass;
    bool hidePassword();

private slots:
    int on_pushButton_Login_clicked();

    int FileLoad();

    void FileCheck();

    int on_pushButton_Register_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
