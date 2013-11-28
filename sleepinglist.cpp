#include "sleepinglist.h"
#include "ui_sleepinglist.h"

SleepingList::SleepingList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SleepingList)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    updateList();
}

SleepingList::~SleepingList()
{
    delete ui;
}


void SleepingList::updateList(){
    int day = ui->dateEdit->date().day();
    int month = ui->dateEdit->date().month();
    int year = ui->dateEdit->date().year();

    this->model = new QSqlQueryModel(this);
    this->model->setQuery("SELECT * FROM `plan_`",Database::Instance()->main_db);
    qDebug() << model->rowCount();
    for (int i = 0; i < model->rowCount(); ++i) {
             int id = model->record(i).value("ID_PLAN").toInt();
             QString name = model->record(i).value("no_com").toString();
             qDebug() << id << name;
             ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));
    }
}
