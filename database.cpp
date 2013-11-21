#include "database.h"

Database* Database::self=NULL;

Database* Database::Instance(){
    if (!self){
        self = new Database(Settings::Instance());
    }
    return self;
}

Database::~Database(){
    if(main_db.isOpen()){
        main_db.close();
    }
    if(add_db.isOpen()){
        add_db.close();
    }
    delete self;
    self = NULL;
}


Database::Database(const Settings *set){
    this->main_db = QSqlDatabase::addDatabase("QMYSQL","main_db");
    this->main_db.setHostName(set->main_db.host->toString());
    this->main_db.setPort(set->main_db.port);
    this->main_db.setDatabaseName(set->main_db.database);
    this->main_db.setUserName(set->main_db.username);
    this->main_db.setPassword(set->main_db.password);

    this->add_db = QSqlDatabase::addDatabase("QMYSQL","add_db");
    this->add_db.setHostName(set->add_db.host->toString());
    this->add_db.setPort(set->add_db.port);
    this->add_db.setDatabaseName(set->add_db.database);
    this->add_db.setUserName(set->add_db.username);
    this->add_db.setPassword(set->add_db.password);

    if ((!this->main_db.open()) || (!this->add_db.open())){
        Func::msgBox("Ошибка подключения к БД");
    }
}

