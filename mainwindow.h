#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include "database.h"
#include "settings.h"

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
    void connectSlots();

public slots:
    void search();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
