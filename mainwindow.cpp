#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::connectSlots(){
    connect(ui->search_submit,SIGNAL(clicked()),this,SLOT(search()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dataModel = new QSqlRelationalTableModel(this,Database::Instance()->main_db);
    dataModel->setTable("archive");
    dataModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    dataModel->select();
    dataModel->removeColumn(0); // don't show the ID
    //dataModel->setHeaderData(0, Qt::Horizontal, tr("Фамилия"));
    //dataModel->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    //dataModel->setHeaderData(2, Qt::Horizontal, tr("Отчество"));
    dataModel->setRelation(7,QSqlRelation("destination","ID_DEST","DEVISION"));
    ui->search->setModel(dataModel);
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
