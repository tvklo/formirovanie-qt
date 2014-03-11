#include "addbody.h"
#include "ui_addbody.h"
#include "mainwindow.h"

AddBody::AddBody(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBody)
{
    this->data = new Data;
    ui->setupUi(this);
    fillLists();
    setDefaultValues();
    connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(add()));
    connect(this,SIGNAL(rejected()),this->parent(),SLOT(fillList()));
}

AddBody::~AddBody()
{
    delete ui;
}

void AddBody::add(){
    memset(this->data,0,sizeof(Data));
    data->arrDate = new QDate(ui->arrDate->date());

    data->birthDate = new QDate(ui->birthDate->date());
    data->district = new QString(ui->district->itemData(ui->district->currentIndex()).toString());
    data->fName = new QString(ui->fName->text());
    data->sName = new QString(ui->sName->text());
    data->tName = new QString(ui->tName->text());
    data->MAS = new QString(ui->MAS->itemData(ui->MAS->currentIndex()).toString());
    data->nMilTicket = new QString(ui->nMilTicket->text());
    data->nToken = new QString(ui->nToken->text());

    if (!checkData(this->data)){
        Func::msgBox("Неправильно заполнена форма");
    }else{
        QString main_db,add_db;
        main_db = Settings::Instance()->main_db.database;
        add_db = Settings::Instance()->add_db.database;
        QSqlQuery query(Database::Instance()->main_db);

        QString qstr = "INSERT INTO archive (FirstName,NAME,SecName,BirthDay,ArrDate,id_region,id_MilSpec,NUMBER,LABLE,commands)"
                "VALUES ('"+*(data->fName)+"','"+*(data->sName)+"','"+*(data->tName)+"','"+data->birthDate->toString("yyyy-MM-dd")+"','"
                +data->arrDate->toString("yyyy-MM-dd")+"','"+*(data->district)+"','"+*(data->MAS)+"','"+*(data->nMilTicket)+"','"
                +*(data->nToken)+"',0);";
        qDebug() << qstr;
        if (!query.exec(qstr)){
            Func::msgBox("Ошибка при добавлении записи:"+query.lastError().text());
        }
    }
}

void AddBody::fillLists(){
    QSqlQuery query(Database::Instance()->add_db);
    QString qstr = "SELECT "
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
        ui->district->addItem(query.value("REGION").toString(),query.value("ID_REGION").toInt());
        listDIS << query.value("REGION").toString();
    }while(query.next());
    QCompleter *completerDIS = new QCompleter(listDIS, this);
    completerDIS->setCaseSensitivity(Qt::CaseInsensitive);
    ui->district->setCompleter(completerDIS);

    qstr = "SELECT "
            "ID_MilSpec, "
            "MilSpec "
            "FROM "
            "spec_mil "
            "ORDER BY MilSpec ASC;";
    query.exec(qstr);
    query.first();
    QStringList listMAS;
    do{
        ui->MAS->addItem(query.value("MilSpec").toString(),query.value("ID_MilSpec").toString());
        listMAS << query.value("MilSpec").toString();
    }while(query.next());
    QCompleter *completerMAS = new QCompleter(listMAS, this);
    completerMAS->setCaseSensitivity(Qt::CaseInsensitive);
    ui->MAS->setCompleter(completerMAS);
}

void AddBody::setDefaultValues(){
    ui->arrDate->setDate(QDate::currentDate());
    ui->birthDate->setDate(QDate(1970,1,1));

}

bool AddBody::checkData(Data *data){
    QDate maxDate = QDate::currentDate().addYears(-17);
    QDate minDate = QDate::currentDate().addYears(-28);
    qDebug() << maxDate.toString() << minDate.toString();
    if ((*data->birthDate > maxDate) || (*data->birthDate < minDate)) return false;
    else if (*data->district == "0") return false;
    else if (*data->fName == "") return false;
    else if (*data->sName == "") return false;
    else if (*data->tName == "") return false;
    else if (*data->MAS == "") return false;
    else if (*data->nMilTicket == "") return false;
    else if (*data->nToken == "") return false;

    return true;
}
