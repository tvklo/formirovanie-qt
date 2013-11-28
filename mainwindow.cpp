#include "mainwindow.h"
#include "ui_mainwindow.h"




void MainWindow::connectSlots(){
    connect(ui->search_submit,SIGNAL(clicked()),this,SLOT(search()));
    connect(ui->sleeping_list_act,SIGNAL(triggered()),this,SLOT(show_sleeping_list()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSlots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search()
{
    dataModel->setFilter("FirstName = '"+ui->search_secName->text()+"' "+
                         "AND ");
}

void MainWindow::show_sleeping_list(){
    this->sleeppingListForm = new SleepingList(this);
    this->sleeppingListForm->show();
}
