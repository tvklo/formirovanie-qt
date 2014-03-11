#include "editcommand.h"
#include "ui_editcommand.h"

EditCommand::EditCommand(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCommand)
{
    ui->setupUi(this);
}

EditCommand::~EditCommand()
{
    delete ui;
}
