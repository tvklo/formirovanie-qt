#include "functions.h"
void Func::msgBox(QString msg){
    QMessageBox box;
    box.setText(msg);
    box.exec();
}
