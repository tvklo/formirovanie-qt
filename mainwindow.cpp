#include "mainwindow.h"
#include "ui_mainwindow.h"




void MainWindow::connectSlots(){
    connect(ui->search_submit,SIGNAL(clicked()),this,SLOT(search()));
    connect(ui->sleeping_list_act,SIGNAL(triggered()),this,SLOT(show_sleeping_list()));
    connect(ui->add_body_act,SIGNAL(triggered()),this,SLOT(showAddBodyDialog()));
    connect(ui->toRightBtn,SIGNAL(clicked()),this,SLOT(toRight()));
    connect(ui->toLeftBtn,SIGNAL(clicked()),this,SLOT(toLeft()));
    connect(ui->orders,SIGNAL(currentIndexChanged(int)),this,SLOT(updateCommandList(int)));
    connect(ui->commandList,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(viewCommandContent(QTableWidgetItem*)));
    new QShortcut(QKeySequence(Qt::Key_Delete), this, SLOT(delBody()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configStatusBar();
    connectSlots();
    configTables();
    fillList();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configStatusBar(){

    ui->statusBar->addWidget(new QLabel("Всего в БД: 1231"));
    ui->statusBar->addWidget(new QLabel("Резерв: 0, Сегодня: 0 "));
    ui->statusBar->addWidget(new QLabel("Отправлено: 2981, из них в ВС: 2671"));
    ui->statusBar->addWidget(new QLabel("Слева: 0, Справа: 0, Команд: 0"));

}

void MainWindow::configTables(){
    QStringList labels;
    labels << "Фамилия" << "Имя" << "Отчество" << "Родился" << "Прибыл" << "Район" << "Специальность" << "Жетон" << "Билет";
    ui->list->setColumnCount(labels.count());
    ui->buffer->setColumnCount(labels.count());
    ui->list->setHorizontalHeaderLabels(labels);
    ui->buffer->setHorizontalHeaderLabels(labels);
    labels.clear();
    labels << "Команда" << "ВОСО" << "Кол-во" << "Дата";
    ui->commandList->setColumnCount(labels.count());
    ui->commandList->setHorizontalHeaderLabels(labels);
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

    qstr = "SELECT * FROM `order_` ORDER BY `OrderDate` DESC;";
    query.exec(qstr);
    query.first();
    do{
        ui->orders->addItem(query.value("No_ORDER").toString()+" от "+query.value("OrderDate").toString(),query.value("id_"));
    }while(query.next());

    qstr = "SELECT "
            "plan_.no_com, "
            "plan_.VOSO, "
            "plan_.CountNow, "
            "plan_.DATE "
            "FROM "
            "plan_ "
            "WHERE "
            "plan_.id_order = "+ui->orders->itemData(0).toString()+";";
    query.exec(qstr);
    query.first();
    //qDebug() << qstr;
    row = 0;
    do{
        ui->commandList->setRowCount(query.size());
        for(int col=0;col<ui->commandList->columnCount();col++){
            ui->commandList->setItem(row,col,new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }while(query.next());


    query = QSqlQuery(Database::Instance()->add_db);
    qstr = "SELECT "
            "region.ID_REGION, "
            "region.REGION "
            "FROM "
            "region "
            "ORDER BY REGION ASC;";
    qDebug() << qstr;
    query.exec(qstr);
    query.first();
    QStringList listDIS;
    do{
        ui->search_district->addItem(query.value("REGION").toString(),query.value("ID_REGION").toInt());
        listDIS << query.value("REGION").toString();
    }while(query.next());
    QCompleter *completerDIS = new QCompleter(listDIS, this);
    completerDIS->setCaseSensitivity(Qt::CaseInsensitive);
    ui->search_district->setCompleter(completerDIS);
}


void MainWindow::updateCommandList(int index){
    QString main_db,add_db;
    main_db = Settings::Instance()->main_db.database;
    add_db = Settings::Instance()->add_db.database;
    QSqlQuery query(Database::Instance()->main_db);
    QString qstr = "SELECT "
            "plan_.no_com, "
            "plan_.VOSO, "
            "plan_.CountNow, "
            "plan_.DATE "
            "FROM "
            "plan_ "
            "WHERE "
            "plan_.id_order = "+ui->orders->currentData().toString()+";";
    query.exec(qstr);
    query.first();
    //qDebug() << qstr;
    int row = 0;
    do{
        ui->commandList->setRowCount(query.size());
        for(int col=0;col<ui->commandList->columnCount();col++){
            ui->commandList->setItem(row,col,new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }while(query.next());
}

void MainWindow::search(){
    QString main_db,add_db;
    ui->list->setRowCount(0);
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
            "Inner Join "+add_db+".region ON "+add_db+".region.ID_REGION = "+main_db+".`archive`.id_region ";

            if (ui->search_radioALL->isChecked()){
                qstr += "WHERE 1=1 ";
            }else{
                qstr += "WHERE " +main_db+".`archive`.commands = 0 ";
            }

            if (ui->search_secName->text() != ""){
                qstr+= "AND "+main_db+".`archive`.FirstName LIKE  '%"+ui->search_secName->text()+"%' ";
            }
            if (ui->search_district->itemData(ui->search_district->currentIndex()).toString() != "0"){
                qstr+= "AND "+add_db+".region.ID_REGION = "+ui->search_district->itemData(ui->search_district->currentIndex()).toString()+" ";
            }
            if (ui->search_vbnum->text() != ""){
                qstr+= "AND "+main_db+".`archive`.NUMBER = "+ui->search_vbnum->text()+" ";
            }
            if (ui->search_token->text()!= ""){
                qstr+= "AND "+main_db+".`archive`.LABLE = "+ui->search_token->text()+" ";
            }
    qstr+=";";
    qDebug() << qstr;
    query.exec(qstr);
    query.first();
    int row = 0;
    do{
        ui->list->setRowCount(query.size());
        for(int col=0;col<ui->list->columnCount();col++){
            ui->list->setItem(row,col,new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }while(query.next());
}

void MainWindow::toLeft(){
    if ((ui->buffer->rowCount() > 0) && (!ui->buffer->selectedItems().empty())){
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
    if ((ui->list->rowCount() > 0) && (!ui->list->selectedItems().empty())){
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

void MainWindow::viewCommandContent(QTableWidgetItem* item){
    QString main_db,add_db;
    ui->buffer->setRowCount(0);
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
            +main_db+".`archive`.NUMBER, "
            +main_db+".plan_.no_com, "
            +main_db+".plan_.id_order "
            "FROM "
            +main_db+".`archive` "
            "Inner Join "+add_db+".spec_mil ON "+add_db+".spec_mil.ID_MilSpec = `"+main_db+"`.`archive`.id_MilSpec "
            "Inner Join "+add_db+".region ON "+add_db+".region.ID_REGION = "+main_db+".`archive`.id_region "
            "Inner Join "+main_db+".com_archive ON "+main_db+".com_archive.id_archive = "+main_db+".`archive`.ID_ARCHIVE "
            "Inner Join "+main_db+".plan_ ON "+main_db+".com_archive.id_plan = "+main_db+".plan_.ID_PLAN "
            "WHERE "
            +main_db+".plan_.no_com = '"+ui->commandList->item(item->row(),0)->text()+"' AND "
            +main_db+".plan_.id_order = "+ui->orders->currentData().toString();
    qDebug() << qstr;
    query.exec(qstr);
    query.first();
    int row = 0;
    do{
        ui->buffer->setRowCount(query.size());
        for(int col=0;col<ui->buffer->columnCount();col++){
            ui->buffer->setItem(row,col,new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }while(query.next());
}

void MainWindow::allLeft(){

}


void MainWindow::allRight(){

}


void MainWindow::show_sleeping_list(){
    this->sleeppingListForm = new SleepingList(this);
    this->sleeppingListForm->show();
}

void MainWindow::showAddBodyDialog(){
    this->addBody = new AddBody(this);
    this->addBody->show();
}

void MainWindow::delBody(){
    ui->list->removeRow(ui->list->currentRow());
}


