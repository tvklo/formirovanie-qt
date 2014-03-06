#include "mainwindow.h"
#include "ui_mainwindow.h"




void MainWindow::connectSlots(){
    connect(ui->search_submit,SIGNAL(clicked()),this,SLOT(search()));
    connect(ui->sleeping_list_act,SIGNAL(triggered()),this,SLOT(show_sleeping_list()));
    connect(ui->toRightBtn,SIGNAL(clicked()),this,SLOT(toRight()));
    connect(ui->toLeftBtn,SIGNAL(clicked()),this,SLOT(toLeft()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSlots();
    configTables();
    fillList();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configTables(){
    QStringList labels;
    labels << "Фамилия" << "Имя" << "Отчество" << "Родился" << "Прибыл" << "Район" << "Специальность" << "Жетон" << "Билет";
    ui->list->setColumnCount(labels.count());
    ui->buffer->setColumnCount(labels.count());
    ui->list->setHorizontalHeaderLabels(labels);
    ui->buffer->setHorizontalHeaderLabels(labels);
}

void MainWindow::fillList(){
    QString main_db,add_db;
    main_db = Settings::Instance()->main_db.database;
    add_db = Settings::Instance()->add_db.database;
    QSqlQuery query(Database::Instance()->main_db);
    QString qstr = "SELECT "
            +main_db+".`archive`.FirstName, "
            +main_db+".`archive`.`NAME`, "
            +main_db+".`archive`.SecName, "
            +main_db+".`archive`.BirthDay, "
            +main_db+".`archive`.ArrDate, "
            +add_db+".region.REGION, "
            +add_db+".spec_mil.MilSpec, "
            +main_db+".`archive`.LABLE, "
            +main_db+".`archive`.NUMBER "
            "FROM "
            +main_db+".`archive` "
            "Inner Join "+add_db+".spec_mil ON "+add_db+".spec_mil.ID_MilSpec = "+main_db+".`archive`.id_MilSpec "
            "Inner Join "+add_db+".region ON "+add_db+".region.ID_REGION = "+main_db+".`archive`.id_region "
            "WHERE "
            +main_db+".`archive`.commands = 0;";
    query.exec(qstr);
    query.first();
    qDebug() << qstr;
    int row = 0;
    do{
        ui->list->setRowCount(query.size());
        for(int col=0;col<ui->list->columnCount();col++){
            ui->list->setItem(row,col,new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }while(query.next());

    qstr = "SELECT ";


}

void MainWindow::search(){

}

void MainWindow::toLeft(){
    if (ui->buffer->rowCount() > 0){
        QTableWidgetItem *item;
        QList<QTableWidgetItem*> items = ui->buffer->selectedItems();
        QList<QTableWidgetItem*>::iterator i = items.begin();
        ui->list->setRowCount(ui->list->rowCount()+1);
        for (int col = 0; col < ui->list->columnCount(); col++){
            item = new QTableWidgetItem;
            *item = **i;
            ui->list->setItem(ui->list->rowCount()-1,col,item);
            i++;
        }
        ui->buffer->removeRow(items[0]->row());
    }
}

void MainWindow::toRight(){
    if (ui->list->rowCount() > 0){
        QTableWidgetItem *item;
        QList<QTableWidgetItem*> items = ui->list->selectedItems();
        QList<QTableWidgetItem*>::iterator i = items.begin();
        ui->buffer->setRowCount(ui->buffer->rowCount()+1);
        for (int col = 0; col < ui->buffer->columnCount(); col++){
            item = new QTableWidgetItem;
            *item = **i;
            ui->buffer->setItem(ui->buffer->rowCount()-1,col,item);
            i++;
        }
        ui->list->removeRow(items[0]->row());
    }
}

void MainWindow::allLeft(){

}


void MainWindow::allRight(){

}


void MainWindow::show_sleeping_list(){
    this->sleeppingListForm = new SleepingList(this);
    this->sleeppingListForm->show();
}
