#include "startfrom.h"
#include "ui_startfrom.h"
#include "mainwindow.h"

StartFrom::StartFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartFrom)
{
    ui->setupUi(this);

    setWindowTitle("开始界面");

    //监听关卡按钮点击 第一关
    connect(ui->pushButton, &QPushButton::clicked, [=]()
    {
        //点击按钮进入关卡
        MainWindow *mainwindow = new MainWindow(0);

        mainwindow->show(); //关卡显示
    });

    //第二关
    connect(ui->pushButton_2, &QPushButton::clicked, [=]()
    {
        MainWindow *mainwindow = new MainWindow(1);
        mainwindow->show(); //关卡显示
    });

    //第三关
    connect(ui->pushButton_3, &QPushButton::clicked, [=]()
    {
        MainWindow *mainwindow = new MainWindow(2);
        mainwindow->show(); //关卡显示
    });

}

StartFrom::~StartFrom()
{
    delete ui;
}
