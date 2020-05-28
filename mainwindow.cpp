#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytcpserver.h"
#include "mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    myTCPServer mytcp;
//    myTCP=&mytcp;
    myTCP=new myTCPServer();
    myTCP->getUI(ui);
    //myTCP.getUI(ui);

    //For connection to gamepad
    connect(&GamepadServer::instance(), SIGNAL(stateUpdate(GamepadState, int)),
            this, SLOT(catchGamepadState(GamepadState, int)));

    this->setWindowTitle(tr("Gamepad Server v0.1"));
    ui->trottleM1->setValue(10);
    ui->trottleM2->setValue(15);

}

MainWindow::~MainWindow()
{
    delete ui;
}
float MainWindow::remap(float value, float from1,float to1, float from2, float to2)
{
    return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}
void MainWindow::sendController(const GamepadState & gps)
{
    int m1=(int)remap(gps.m_lTrigger,0,255,0,100);
    int m2=(int)remap(gps.m_rTrigger,0,255,0,100);

    QString message =" "+QString::number(m1)+" "+QString::number(m2);
    qDebug() << message;
    myTCP->sendMessage(message);
    ui->trottleM1->setValue(m1);
    ui->trottleM2->setValue(m2);


}
void MainWindow::catchGamepadState(const GamepadState & gps, const int & playerId) {
    sendController(gps);
    ui->Controller_status->setStyleSheet( "border-radius: 10px;"
                                           " background: green;"
                                             "color: green;"
                                            "height:24;"
                                            "width:24;"
                                          );

    qDebug() << "Player " << playerId << ": ";

    qDebug() << "Left Trigger: " << gps.m_lTrigger <<
                "\tRight Trigger: " << gps.m_rTrigger;
    qDebug() << "Left Thumb :: X Axis: " << gps.m_lThumb.xAxis <<
                "\t Y Axis: " << gps.m_lThumb.yAxis;
    qDebug() << "Right Thumb :: Y Axis: " << gps.m_rThumb.xAxis <<
                "\t Y Axis: " << gps.m_rThumb.yAxis;

    if (gps.m_pad_a) {
        qDebug() << "A Pressed.";
    }
    if (gps.m_pad_b) {
        qDebug() << "B Pressed.";
    }
    if (gps.m_pad_x) {
        qDebug() << "X Pressed.";
    }
    if (gps.m_pad_y) {
        qDebug() << "Y Pressed.";
    }
    if (gps.m_pad_up) {
        qDebug() << "Up Pressed.";
    }
    if (gps.m_pad_down) {
        qDebug() << "Down Pressed.";
    }
    if (gps.m_pad_left) {
        qDebug() << "Left Pressed.";
    }
    if (gps.m_pad_right) {
        qDebug() << "Right Pressed.";
    }
    if (gps.m_lShoulder) {
        qDebug() << "Left Shoulder Pressed.";
    }
    if (gps.m_rShoulder) {
        qDebug() << "Right Shoulder Pressed.";
    }
    if (gps.m_lThumb.pressed) {
        qDebug() << "Left Thumb Pressed.";
    }
    if (gps.m_rThumb.pressed) {
        qDebug() << "Right Thumb Pressed.";
    }
    if (gps.m_pad_start) {
        qDebug() << "Start Pressed.";
    }
    if (gps.m_pad_back) {
        qDebug() << "Back Pressed.";
    }

}


//Button Slots
void MainWindow::on_Button_CommandSend_clicked()
{
    QString input = ui->textIntput_Command->text();
    myTCP->sendMessage(input);
    input = "Controller: "+input;
    ui->commandTable->append(input);
    ui->textIntput_Command->clear();
}

void MainWindow::on_Button_SerialConnection_clicked()
{

}

void MainWindow::on_Button_NetworkConnect_clicked()
{

}

void MainWindow::on_Button_Move_Forward_clicked()
{

}

void MainWindow::on_Button_Move_Reverse_clicked()
{

}

void MainWindow::on_Button_Move_Right_clicked()
{

}

void MainWindow::on_Button_Move_Reverse_2_clicked()
{

}

void MainWindow::on_Button_Move_Right_2_clicked()
{

}

void MainWindow::on_textIntput_Command_returnPressed()
{
    QString input = ui->textIntput_Command->text();
    myTCP->sendMessage(input);
    input = "Controller: "+input;
    ui->commandTable->append(input);
    ui->textIntput_Command->clear();
}

void MainWindow::on_Button_Move_Forward_clicked(bool checked)
{

}
