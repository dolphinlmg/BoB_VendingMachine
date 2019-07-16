#include "widget.h"
#include "ui_widget.h"
#include <qmessagebox.h>
#include <qstring.h>

// TO-DO: reset button
//          when click btn show qmessagebox
//          disable ninus

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    checkDisableBtn();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::checkDisableBtn(){
    if (this->money < 200)
        ui->pbCoke->setDisabled(true);
    if(this->money < 150)
        ui->pbTea->setDisabled(true);
    if(this->money < 100)
        ui->pbCoffee->setDisabled(true);
    if(this->money >= 100)
        ui->pbCoffee->setDisabled(false);
    if(this->money >= 150)
        ui->pbTea->setDisabled(false);
    if(this->money >= 200)
        ui->pbCoke->setDisabled(false);
}

int* Widget::reset(){
    int* p = new int[4]{0,};
    int arr[] = {500,100,50,10};
    for(int i = 0; i < 4; i++){
        while(this->money - arr[i] >= 0){
            *(p+i) += 1;
            this->money -= arr[i];
        }
    }
    return p;
}

void Widget::showMsgbox(int *p){
    QString str = QString();
    QMessageBox msg;
    msg.information(nullptr, "Reset",
                    "500: " + QString::number(*p) + "\n" +
                    "100: " + QString::number(*(p+1)) + "\n" +
                    "50: " + QString::number(*(p+2)) + "\n" +
                    "10: " + QString::number(*(p+3)) + "\n"
                    );

}

void Widget::changeMoney(int n){
    this->money += n;
    ui->lcdNumber->display(this->money);
    checkDisableBtn();
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);
}

void Widget::on_pbTea_clicked()
{
    changeMoney(-150);
}

void Widget::on_pbCoke_clicked()
{
    changeMoney(-200);
}

void Widget::on_tbReset_clicked()
{
    showMsgbox(reset());
    changeMoney(0);
}
