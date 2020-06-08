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
    curveC=ui->curveConstant->text().toFloat();
    QPixmap pix(":/new/photo/Logo.png");
    int w= ui->logoLabel->width();
    int h =ui->logoLabel->height();
    ui->logoLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

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

    double m1Set;
    double m2Set;
    maxSpeed =ui->maxSpeedInput->text().toUInt();
    if(ui->xCotrollerCheck->isChecked())
    {
    m1=(int)remap(gps.m_lTrigger,0,255,50,maxSpeed);  //Set last 0-100 for test robot,  set 50-100 for main robot
    m2=(int)remap(gps.m_rTrigger,0,255,50,maxSpeed);  //Set last 0-100 for test robot,  set 50-100 for main robot


     //m1Set=(double)remap(gps.m_lTrigger,0,255,15.1,20.1);  //Set last 0-100 for test robot,  set 50-100 for main robot
    // m2Set=(int)remap(gps.m_rTrigger,0,255,15.1,10.1);  //Set last 0-100 for test robot,  set 50-100 for main robot
    }
    if(ui->xCotrollerCheck_Joystick->isChecked())
    {

        m1=(int)remap(gps.m_lTrigger,5000,32767,50,maxSpeed);  //Set last 0-100 for test robot,  set 50-100 for main robot
        m2=(int)remap(gps.m_rTrigger,5000,32767,50,maxSpeed);  //Set last 0-100 for test robot,  set 50-100 for main robot
    }
    if(ui->xCotrollerCheck_SingleTrigger->isChecked())
    {

        m1=(int)remap(gps.m_rTrigger,0,255,50,maxSpeed);  //Set last 0-100 for test robot,  set 50-100 for main robot
        m2=m1;   //Set last 0-100 for test robot,  set 50-100 for main robot
    }

    else if (gps.m_pad_b) {
        qDebug() << "B Pressed.";
        m1=45;
        m2=45;
    }




   // int xjoy=

    QString message =" "+QString::number(m1)+" "+QString::number(m2);

    qDebug() << message;
    myTCP->sendMessage(message);

    //Format and display the message to be sent on terminal
    if(ui->checkBox_AutoMessageShow->isChecked())
    {
    message="Controller: "+message;
    ui->commandTable->append(message);
    }

    //Set the trottle levels on the UI
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
    if(refreshCount>10)
    {
    ui->statusLight_ObstacleAvoid->setStyleSheet( "border-radius: 10px;"
                                           " background: red;"
                                             "color: red;"
                                            "height:24;"
                                            "width:24;"
                                          );
    refreshCount=0;
    }
    refreshCount++;


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



void MainWindow::on_Button_Move_Forward_released()
{

}

void MainWindow::on_xCotrollerCheck_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->xCotrollerCheck_Joystick->setCheckState(Qt::CheckState::Unchecked);
        ui->xCotrollerCheck_SingleTrigger->setCheckState(Qt::CheckState::Unchecked);
    }

}

void MainWindow::on_xCotrollerCheck_SingleTrigger_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->xCotrollerCheck->setCheckState(Qt::CheckState::Unchecked);
        ui->xCotrollerCheck_Joystick->setCheckState(Qt::CheckState::Unchecked);
    }
}
