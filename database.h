#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include "settings.h"
#include <QException>

class Database
{
public:
    static Database* Instance();
    QSqlDatabase main_db;
    QSqlDatabase add_db;



private:

    Database(const Settings *set);
    Database(Database const*);
    void operator = (Database const&);
    static Database *self;
    virtual ~Database();
};


#endif // DATABASE_H
