#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// port btn
void MainWindow::on_pushButton_clicked()
{
    QString s;
    s = ui->textEdit->toPlainText();
    port.setPort(QSerialPortInfo(s));
    port.setDataBits(QSerialPort::Data8);
    port.setStopBits(QSerialPort::OneStop);
    port.open(QIODevice::ReadWrite);
    QMessageBox msgBox;
    msgBox.setText(port.portName());
    msgBox.exec();
}

// baud btn
void MainWindow::on_pushButton_2_clicked()
{
    QString s;
    s = ui->textEdit_2->toPlainText();
    this->port.setBaudRate(s.toInt()); //Установка
    QMessageBox msgBox;
    qint32 msgText = this->port.baudRate();
    msgBox.setText(QString::number(msgText));
    msgBox.exec();

}

void MainWindow::on_button_enter_clicked()
{
    auto test = ui->textEdit_4->toPlainText().toStdString();
    if (ui->textEdit_4->toPlainText().size() > 0) {
         const char* str = test.c_str();
        qDebug() << "writing " << str;
        port.write(str);
        if (!port.waitForBytesWritten()) {
            qDebug() << "error sending byte";
        }

    } else {
        qDebug() << "textEdit_3 is empty";
    }
}

void MainWindow::startWrite() {
    int lastIndex = ui->textEdit_4->toPlainText().length() - 1;
    QChar contentToSend = ui->textEdit_4->toPlainText()[lastIndex];
    QByteArray byteArray = QString("%1").arg(contentToSend).toLocal8Bit();
    //qDebug() << byteArray.data() << byteArray << contentToSend << QString("%1").arg(contentToSend);
    port.write(byteArray.data());
}


void MainWindow::on_button_see_clicked()
{
    int numRead = 0;
    char buffer[50];
    QString result;

    if (port.bytesAvailable() > 0) {
        numRead  = port.read(buffer, 50);
        for (int i = 0; i < numRead; ++i) {
            if (buffer[i] != '\0') {
                result += buffer[i];
            }
        }
        ui->textEdit_3->setPlainText(result);
    } else {
        qDebug() << "No data input";
    }
}
