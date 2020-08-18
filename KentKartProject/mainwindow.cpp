#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "QMessageBox"
#include <QtWidgets>
#include <QXmlStreamReader>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QDebug>
#include <QString>
#include <QXmlSimpleReader>
#include <QDomDocument>
#include <QDomElement>
#include <QStyle>
#include <QDesktopWidget>
#include "secwindow.h"

using namespace std;
QString Username;
QString Password;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FileLoad();
    ui->lineEdit_2_password->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void outString(string ref1,string ref2)
{

    std::cout << "   Username = " << ref1 << std::endl;
    std::cout << "   Password = " << ref2 << std::endl;

}


int MainWindow::on_pushButton_Login_clicked()
{

    QString username2 = ui->lineEdit_username->text();
    QString password2 = ui->lineEdit_2_password->text();

   // outString(username2.toStdString(),password2.toStdString());
   // outString(Username.toStdString(),Password.toStdString());

    SecWindow secondWindow;
    secondWindow.setModal(true);

    for(int i=0 ; i<userID.count() ; i++)
    {
    if(username2 == userID[i] && password2 ==  userPass[i])
    {
        QMessageBox::information(this,"Login","<P><FONT COLOR='#000080'>Username and Password are correct. </FONT></P>");
        hide();
        secondWindow.exec();
        return 0;
    }
    }
        QMessageBox::warning(this,"Login","<P><FONT COLOR='#000080'>Username and Password are NOT correct. </FONT></P>");
        return 1;
}

int MainWindow::FileLoad()
{
    // Load xml file as raw data
    QFile LogFile("/home/mehmet/KentKartProject/Register.xml");
    if (!LogFile.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading file" << std::endl;
        return 1;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&LogFile);
    LogFile.close();
    FileCheck();
}

void MainWindow::FileCheck()
{
    QDomElement root00=xmlBOM.documentElement();

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement Information00=root00.firstChild().toElement();

    // Loop while there is a child
    while(!Information00.isNull())
    {
        // Check if the child tag name is Information
        if (Information00.tagName()=="Information")
        {

            // Read and display the component ID
            //QString ID=Information00.attribute("ID","No ID");

            // Get the first child of the component
            QDomElement Child=Information00.firstChild().toElement();


            // Read each child of the component node
            while (!Child.isNull())
            {
                // Read Name and value
                if (Child.tagName()=="Username") Username=Child.firstChild().toText().data();
                if (Child.tagName()=="Password") Password=Child.firstChild().toText().data();


                // Next child
                Child = Child.nextSibling().toElement();
            }

            // Display component data
            //std::cout << "Information " << ID.toStdString().c_str() << std::endl;
            std::cout << "   Username = " << Username.toStdString().c_str() << std::endl;
            std::cout << "   Password = " << Password.toStdString().c_str() << std::endl;
            std::cout << std::endl;

            userID.append(Username);
            userPass.append(Password);
       }

        // Next component
        Information00 = Information00.nextSibling().toElement();
    }

}

int MainWindow::on_pushButton_Register_clicked()
{

    QString username3 = ui->lineEdit_username->text();
    QString password3 = ui->lineEdit_2_password->text();

    QFile RegFile("/home/mehmet/KentKartProject/Register.xml");

   //RegFile.open(QFile::ReadWrite);
   //QXmlStreamWriter writer(&RegFile);
   //QXmlStreamReader reader(&RegFile);

    QString ctag = "</Login>\n";

    if (username3== "" || password3 == ""){
        QMessageBox::warning(this,"Login","<P><FONT COLOR='#000080'>Username and Password can NOT be empty. </FONT></P>");
        return 0;
    }


    if (username3.contains(" ") || password3.contains(" ")){
        QMessageBox::warning(this,"Login","<P><FONT COLOR='#000080'>Username and Password can NOT have empty characters. </FONT></P>");
        return 1;

    }

    if (username3.length() < 8 || password3.length() < 8){
        QMessageBox::warning(this,"Login","<P><FONT COLOR='#000080'>Username and Password can NOT be less than 8 characters. </FONT></P>");
        return 2;

    }


        qint64 s = RegFile.size();
        if (s > 0) {
            RegFile.open(QFile::ReadWrite);
            if (RegFile.seek(s - ctag.length()))
                Q_ASSERT(RegFile.pos() == s - ctag.length());

        } else
            RegFile.open(QFile::WriteOnly);

        QXmlStreamWriter xmlWriter(&RegFile);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.setAutoFormattingIndent(2);

        if (s == 0) {
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("Login");
        }

        xmlWriter.writeStartElement("Information");
        xmlWriter.writeTextElement("Username", username3);
        xmlWriter.writeTextElement("Password", password3);
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();

        if (s == 0) {
            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
        }
        else
            QTextStream(&RegFile) << ctag;


    //QDomDocument RegDoc;
    //RegDoc.setContent(&RegFile);
    //RegDoc.createTextNode("memed");
    //QDomElement root01=RegDoc.documentElement();
    //QDomElement Information01=root01.firstChild().toElement();

    //QXmlStreamReader Read(&RegFile);
    //QXmlStreamWriter Write(&RegFile);
    //if (!RegFile.open(QIODevice::WriteOnly ))
    //{
        // Error while loading file
     //   std::cerr << "Error while writig file" << std::endl;
    //}
    //  Write.setAutoFormatting(true);
    //  Write.writeStartDocument();
     // Write.writeStartElement("Login");
    //  Write.writeStartElement("Information");
     // Write.writeAttribute("ID", idCountString);
     // Write.writeTextElement("username", "tester1");
     // Write.writeTextElement("password", "test");
     // Write.writeEndElement(); // Login
     // Write.writeEndDocument();


        // Check if the child tag name is Information
     //   if (Information.tagName()=="Information")
      //  {

            // Read and display the component ID

            // Get the first child of the component
            //QDomElement Child01=Information01.firstChild().toElement();


            // Read each child of the component node

                // Read Name and value



                // Next child


            // Display component data

      //  }

        // Next component

        QMessageBox::information(this,"Login","<P><FONT COLOR='#000080'>You have successfully registered. </FONT></P>");
        FileLoad();

}
