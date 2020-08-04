#include "mainwindow.h"
#include "ui_mainwindow.h"

double value = 0.0;
bool addTrigger = false;
bool subTrigger = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(value));
    QPushButton *numButton[10];

    for(int i=0;i<10;++i){
        QString butName = "Button"+QString::number(i);
        numButton[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButton[i],SIGNAL(released()), this, SLOT(NumPressed() ));
    }

    connect(ui->ButtonAdd,SIGNAL(released()), this, SLOT(MathPressed() ));
    connect(ui->ButtonMinus,SIGNAL(released()), this, SLOT(MathPressed() ));
    connect(ui->ButtonEqual,SIGNAL(released()), this, SLOT(EqualPressed() ));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butValue = button->text();
    QString disValue = ui->Display->text();
    if(disValue.toDouble()==0||disValue.toDouble()==0.0){
        ui->Display->setText(butValue);
    }
    else {
        QString newValue = disValue+butValue;
        double dNewValue = newValue.toDouble();
        ui->Display->setText(QString::number(dNewValue,'g',16));
    }
}

void MainWindow::MathPressed(){
    addTrigger = false;
    subTrigger = false;
    QString disValue = ui->Display->text();
    value = disValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if (QString::compare(butVal,"+", Qt::CaseInsensitive)==0){
        addTrigger=true;
    } else if (QString::compare(butVal,"-", Qt::CaseInsensitive)==0){
        subTrigger=true;
    }

    ui->Display->setText("");

}

void MainWindow::EqualPressed(){
    double solution = 0.0;
    QString disValue = ui->Display->text();
    double dblValue = disValue.toDouble();
    if(addTrigger){
        solution = dblValue+value;
    }
    else if (subTrigger){
        solution = dblValue-value;
    }

    ui->Display->setText(QString::number(solution));

}

