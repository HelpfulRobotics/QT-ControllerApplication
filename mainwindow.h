#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytcpserver.h"
#include "gamepadserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 Ui::MainWindow *ui;

 float remap(float value, float from1, float to1, float from2, float to2);
protected slots:

  void catchGamepadState(const GamepadState & gps, const int & playerId); //For connection to gamepad server

private slots:


    void on_Button_CommandSend_clicked();

    void on_Button_SerialConnection_clicked();

    void on_Button_NetworkConnect_clicked();

    void on_Button_Move_Forward_clicked();

    void on_Button_Move_Reverse_clicked();

    void on_Button_Move_Right_clicked();

    void on_Button_Move_Reverse_2_clicked();

    void on_Button_Move_Right_2_clicked();

    void on_textIntput_Command_returnPressed();

    void on_Button_Move_Forward_clicked(bool checked);

private:
    void sendController(const GamepadState & gps);
    myTCPServer* myTCP=nullptr;
};
#endif // MAINWINDOW_H
