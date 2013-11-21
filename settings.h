#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QtNetwork/QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include "functions.h"


struct db_config{
    QHostAddress *host;
    int port;
    QString username;
    QString password;
    QString database;
};

class Settings:QSettings{
    public:
        bool isLoad();
        db_config main_db;
        db_config add_db;
        static Settings* Instance();
    private:
        Settings(QString);

        Settings(Settings const&);
        void operator=(Settings const&);
        static Settings *self;
};


#endif // SETTINGS_H
