#ifndef SLEEPINGLIST_H
#define SLEEPINGLIST_H

#include <QDialog>
#include <QSqlQueryModel>
#include "database.h"
#include <QDebug>
#include <QSqlRecord>
#include <QCheckBox>
#include <QSqlQuery>
#include <QSqlResult>
#include <QDate>
#include <QVariant>

namespace Ui {
class SleepingList;
}

class SleepingList : public QDialog
{
    Q_OBJECT

public:
    explicit SleepingList(QWidget *parent = 0);
    ~SleepingList();

public slots:
    void updateList(QDate newDate);

private:
    Ui::SleepingList *ui;
    QSqlQueryModel *model;
};

#endif // SLEEPINGLIST_H
