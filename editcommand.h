#ifndef EDITCOMMAND_H
#define EDITCOMMAND_H

#include <QDialog>

namespace Ui {
class EditCommand;
}

class EditCommand : public QDialog
{
    Q_OBJECT

public:
    explicit EditCommand(QWidget *parent = 0);
    ~EditCommand();

private:
    Ui::EditCommand *ui;
};

#endif // EDITCOMMAND_H
