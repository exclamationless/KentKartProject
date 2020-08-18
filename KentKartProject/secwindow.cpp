#include "secwindow.h"
#include "ui_secwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QWindow>
#include <QString>
#include <iostream>
#include <QIODevice>
#include <QTime>
#include <QThread>
#include <QDesktopWidget>
#include "mainwindow.h"

using namespace std;
QTextCursor textCursor;

SecWindow::SecWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecWindow)
{
    ui->setupUi(this);
}

SecWindow::~SecWindow()
{
    delete ui;
}
//void SecWindow::moveToCenter()
//{
//    move(qApp->desktop()->availableGeometry(this).center()-rect().center());
//}

void SecWindow::myFunction()
{
    SecWindow::searchFunc(word1);
}
void SecWindow::myFunction2()
{
     SecWindow::searchFunc2(word2);
}

int SecWindow::on_pushButton_search_clicked()
{
    word1 = ui->s1Txt->text();
    QTimer::singleShot(500,this,SLOT(myFunction()));

}

int SecWindow::on_pushButton_search2_clicked()
{
    word2 = ui->s2Txt->text();
    QTimer::singleShot(500,this,SLOT(myFunction2()));
    QString word = ui->s2Txt->text();
    ui->textEdit->find(word, QTextDocument::FindWholeWords);
//    ui->s2Lbl->setText(QString(searchFunc2(ui->s2Txt->text())));
//    qDebug() << searchFunc2(ui->s2Txt->text());

    //if(QTextDocument::end()){
       // textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);
    //}
}
int SecWindow::searchFunc(QString text){
    int counter = 0;
    QFile MyFile("/home/mehmet/KentKartProject/1408byStephenKing.txt");
    QThread::sleep(1);
    MyFile.open(QIODevice::ReadWrite);
    QTextStream in (&MyFile);
    QString content;
    while (!MyFile.atEnd()) {

            content = MyFile.readLine();
            if(content.contains(text))
            {
                counter++;
            }

        }
    MyFile.close();
    QString s = QString::number(counter);
    ui->s1Lbl->setText("Count : "  + s);
    return counter;
}

int SecWindow::searchFunc2(QString text){
    int counter = 0;
//    QString Ref2;
//    RefFunc(Ref2);
//    qDebug() << Ref2<<"02";
    QFile MyFile(Ref1);

    MyFile.open(QIODevice::ReadWrite);
    QTextStream in (&MyFile);
    QString content;
    while (!MyFile.atEnd()) {
            content = MyFile.readLine();
            if(content.contains(text))
            {
                counter++;
//                ui->s2Lbl->setText("Count: "+ QLocale().toString(counter));
            }
        }
    MyFile.close();
    QString s = QString::number(counter);
    ui->s2Lbl->setText("Count : "  + s);
    return counter;
}

void SecWindow::on_pushButton_logout_clicked()
{
     this->hide();
     mainWin= new MainWindow();
     mainWin-> show();

}

void SecWindow::on_pushButton_openfile_clicked()
{
    QString filter = "All File (*.*) ;; XML File (*.xml) ;; TXT File (*.txt)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file","/home",filter);
    QFile nfile(file_name);
    QFileInfo nfileinfo(nfile);
    Ref1=nfileinfo.absoluteFilePath();
    qDebug() << Ref1<<"is opened.";
    getTextFile();
}

void SecWindow::getTextFile(){

    QFile myFile (Ref1);
    myFile.open(QIODevice::ReadOnly);

    QTextStream textStream(&myFile);
    QString line = textStream.readAll();
    myFile.close();

    ui->textEdit->setPlainText(line);
    textCursor = ui->textEdit->textCursor();
    textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);

}

void SecWindow::on_pushButton_clearpage_clicked()
{

    refresher(textCursor);


}

void SecWindow::refresher(QTextCursor curRefresh)
{
    curRefresh.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);
    ui->textEdit->setTextCursor(curRefresh);
}


//void SecWindow::RefFunc(QString REF)
//{
//    REF=Ref1;
//    qDebug() << REF<<"01";
//}

//void SecWindow::myFunction(){
//    qDebug() << "Update...";
//}


//void WordCount::countSingleThreaded()
//  {
//      // Mark the application as active
//      m_active = true;
//      emit activeChanged();

//      // Start to measure the time
//      QTime time;
//      time.start();

//      // Count the words single threaded
//      const WordCountMap total = singleThreadedWordCount(m_files);

//      // Update the measured time
//      m_elapsedTime = time.elapsed();
//      emit elapsedTimeChanged();

//      // Accumulate the per-file word counts to the total word count
//      const QList<int> counts = total.values();
//      m_wordCount = std::accumulate(counts.begin(), counts.end(), 0);
//      emit wordCountChanged();

//      // Mark the application as inactive
//      m_active = false;
//      emit activeChanged();
//  }
//WordCountMap singleThreadedWordCount(const QStringList &files)
//    {
//        WordCountMap wordCount;

//        foreach (const QString &fileName, files) {
//            QFile file("/home/tarik/Masaüstü/TheLordOfTheRings");
//            file.open(QIODevice::ReadOnly);
//            QTextStream textStream(&file);
//            while (textStream.atEnd() == false) {
//                foreach(const QString &word, textStream.readLine().split(" "))
//                    wordCount[word] += 1;
//            }
//        }

//        return wordCount;
//    }
