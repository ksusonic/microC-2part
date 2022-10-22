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
    port.setParity(QSerialPort::NoParity);
    port.setFlowControl(QSerialPort::NoFlowControl);

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

void MainWindow::on_textEdit_textChanged()
{

}

void MainWindow::on_textEdit_2_textChanged()
{

}


void MainWindow::on_button_enter_clicked()
{
    const auto test = ui->lineEdit->text().toStdString();
    //char data[3] = {'1', '2', '\0'};
    QByteArray data = ui->lineEdit->text().toLatin1();//
    data.append('\0');
     port.write(data);//, sizeof(data));
      // port.write(test.c_str(), test.size() < 7 ? test.size() : 7);
//    if (test.size() > 0) {
//        for (int i = 0;  i < (test.size() < 7 ? test.size() : 7); ++i) {
//            auto c = test[i];
//            qDebug() << "iteration " << i << " -> " << c;
//            auto cu = char(c.toLatin1());
//            port.write(&cu);
//        }

  //  port.write('\0');
    if (!port.waitForBytesWritten()) {
        qDebug() << "error sending byte";
    } else {
        qDebug() << "successfully written";
    }
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
