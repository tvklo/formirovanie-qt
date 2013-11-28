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
    this->model = new QSqlQueryModel(this);
    this->model->setQuery("SELECT * FROM `archive`",Database::Instance()->main_db);
    qDebug() << model->data(QModelIndex(1,1,model)).toString();
}
