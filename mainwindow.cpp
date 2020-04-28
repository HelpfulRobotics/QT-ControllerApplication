#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytcpserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // myTCPServer myTCP;

}

MainWindow::~MainWindow()
{
    delete ui;
}


//Button Slots
void MainWindow::on_Button_CommandSend_clicked()
{
    QString input = ui->textIntput_Command->text();
    myTCP.sendMessage(input);
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
    myTCP.sendMessage(input);
    input = "Controller: "+input;
    ui->commandTable->append(input);
    ui->textIntput_Command->clear();
}
