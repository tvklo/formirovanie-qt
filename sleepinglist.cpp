#include "sleepinglist.h"
#include "ui_sleepinglist.h"

SleepingList::SleepingList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SleepingList)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
//    updateList(QDate::currentDate());
    connect(ui->dateEdit,SIGNAL(editingFinished()),this,SLOT(updateList()));
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
    QString q = "SELECT * FROM `plan_` WHERE `DATE` = '" +
            QString::number(year)+"-"+QString::number(month)+"-"+QString::number(day)+"'";
    this->model->setQuery(q,Database::Instance()->main_db);
    qDebug() << q;

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(model->rowCount());
    for (int i = 0; i < model->rowCount(); ++i) {
             int id = model->record(i).value("ID_PLAN").toInt();
             QString name = model->record(i).value("no_com").toString();
             qDebug() << id << name;
             ui->tableWidget->setItem(i,1,new QTableWidgetItem(name));
             ui->tableWidget->setCellWidget(i, 0, new QCheckBox);

    }
    ui->tableWidget->viewport()->update();
    qDebug() << "Table updated";
}
