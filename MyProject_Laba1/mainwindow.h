#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_textEdit_textChanged();
    void on_textEdit_2_textChanged();
    void on_textEdit_4_textChanged();
    void on_button_enter_clicked();
    void on_button_see_clicked();
    void startWrite();

private:
    Ui::MainWindow *ui;
    QSerialPort port;
    QMutex m_mutex;
};
#endif // MAINWINDOW_H
