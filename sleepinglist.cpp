#include "sleepinglist.h"
#include "ui_sleepinglist.h"

SleepingList::SleepingList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SleepingList)
{
    //QDate tmpDate = QDate::currentDate();
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    //updateList(tmpDate);
    connect(ui->dateEdit,SIGNAL(dateChanged(const QDate)),
            this,SLOT(updateList(QDate)));
}

SleepingList::~SleepingList()
{
    delete ui;
}


void SleepingList::updateList(QDate newDate){
    int year,month,day;
    newDate.getDate(&year,&month,&day);

    qDebug() << year << month << day;
    Database::Instance();
    QSqlQuery query(Database::Instance()->main_db);
    QString qstr = "SELECT `no_com` FROM `plan_` WHERE "
                   "YEAR(`DATE`) = :year AND "
                   "MONTH(`DATE`)= :month AND "
                   "DAY(`DATE`)  = :day AND "
                   "CommandOK = 1";


    query.prepare(qstr);
    query.bindValue(":year",year);
    query.bindValue(":month",month);
    query.bindValue(":day",day);
    query.exec();
    qDebug() << query.executedQuery();
    qDebug("%s" , query.lastQuery().toStdString().c_str());
    //while (){
        qDebug() << query.value(0).toString();
    //}

    qDebug() << "Table updated";

}
