#ifndef SLEEPINGLIST_H
#define SLEEPINGLIST_H

#include <QDialog>
#include <QSqlQueryModel>
#include "database.h"
#include <QDebug>

namespace Ui {
class SleepingList;
}

class SleepingList : public QDialog
{
    Q_OBJECT

public:
    explicit SleepingList(QWidget *parent = 0);
    ~SleepingList();
    void updateList();

private:
    Ui::SleepingList *ui;
    QSqlQueryModel *model;
};

#endif // SLEEPINGLIST_H
