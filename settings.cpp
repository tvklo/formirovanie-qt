#include "settings.h"

Settings* Settings::self=NULL;

Settings* Settings::Instance(){
    if(!self){
        self = new Settings("../formirovanie-qt/sets.ini");
    }
    return self;
}


Settings::Settings(QString filename):QSettings(filename, QSettings::IniFormat){
    QString host;
    int port;
    QString database;
    QString username;
    QString password;

    this->beginGroup("MAIN_DB");
    host = this->value("host").toString();
    port = this->value("port").toInt();
    database = this->value("database").toString();
    username = this->value("username").toString();
    password = this->value("password").toString();
    this->endGroup();

    this->main_db.host = new QHostAddress(host);
    this->main_db.port = port;
    this->main_db.database = database;
    this->main_db.username = username;
    this->main_db.password = password;

    this->beginGroup("ADD_DB");
    host = this->value("host").toString();
    port = this->value("port").toInt();
    database = this->value("database").toString();
    username = this->value("username").toString();
    password = this->value("password").toString();
    this->endGroup();

    this->add_db.host = new QHostAddress(host);
    this->add_db.port = port;
    this->add_db.database = database;
    this->add_db.username = username;
    this->add_db.password = password;

#ifdef _DEBUG
    qDebug() << "-->Loading settings:";
    qDebug() << "->Main database:";
    qDebug() << "Host:" << this->main_db.host->toString();
    qDebug() << "Port:" << this->main_db.port;
    qDebug() << "DB:" << this->main_db.database;
    qDebug() << "Username:" << this->main_db.username;
    qDebug() << "Password:" << this->main_db.password;
    qDebug() << "->Addition database:";
    qDebug() << "Host:" << this->add_db.host->toString();
    qDebug() << "Port:" << this->add_db.port;
    qDebug() << "DB:" << this->add_db.database;
    qDebug() << "Username:" << this->add_db.username;
    qDebug() << "Password:" << this->add_db.password;
#endif

    if (!this->isLoad()){
        Func::msgBox("Ошибка при загрузке настроек из sets.ini");
    }
}

bool Settings::isLoad(){
    if(this->main_db.host->toString() == ""){
        return false;
    }else if(this->main_db.database == ""){
        return false;
    }else if(this->main_db.username == ""){
        return false;
    }else if((this->main_db.port < 1) || (this->main_db.port > 65535)){
        return false;
    }else if(this->add_db.host->toString() == ""){
        return false;
    }else if(this->add_db.database == ""){
        return false;
    }else if(this->add_db.username == ""){
        return false;
    }else if((this->add_db.port < 1) || (this->add_db.port > 65535)){
        return false;
    }
    return true;
}
