#ifndef ADDBODY_H
#define ADDBODY_H

#include <QDialog>
#include <QSqlQuery>
#include <QCompleter>
#include <QSqlError>
#include "functions.h"
#include "settings.h"
#include "database.h"



namespace Ui {
class AddBody;
}

class AddBody : public QDialog
{
    Q_OBJECT


public slots:
    void add();

public:
    explicit AddBody(QWidget *parent = 0);
    ~AddBody();
    typedef struct{
            QDate   *arrDate;
            QDate   *birthDate;
            QString *district;
            QString *fName;
            QString *sName;
            QString *tName;
            QString *nToken;
            QString *nMilTicket;
            QString *MAS; //Military accounting speciality

        }Data;


private:
    Ui::AddBody *ui;
    void fillLists();
    void setDefaultValues();
    bool checkData(Data *data);
    Data *data;
};

#endif // ADDBODY_H
