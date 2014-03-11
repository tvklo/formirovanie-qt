#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QTableWidgetItem>
#include <QShortcut>
#include "database.h"
#include "settings.h"
#include "addbody.h"
#include "sleepinglist.h"




namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlRelationalTableModel *dataModel;



public slots:
    void search();
    void show_sleeping_list();
    void toLeft();
    void toRight();
    void allLeft();
    void allRight();
    void updateCommandList(int);
    void configStatusBar();
    void showAddBodyDialog();
    void fillList();
    void viewCommandContent(QTableWidgetItem*);
    void delBody();



private:
    Ui::MainWindow *ui;
    SleepingList *sleeppingListForm;
    AddBody *addBody;
    void configTables();
    void connectSlots();

};

#endif // MAINWINDOW_H
