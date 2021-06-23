#ifndef ADDPROD_H
#define ADDPROD_H

#include <QDialog>
#include <QStringListModel>
#include <QStandardItemModel>
#include "storage.h"

namespace Ui {
class addprod;
}

class addprod : public QDialog
{
    Q_OBJECT

public:
    explicit addprod(QWidget *parent = nullptr);
    ~addprod();
    void setModelPointer(QStringListModel* pointerToModel);
    void setDataPointer(Storage* prodData);


private slots:
    void on_pushButton_clicked();

private:
    Ui::addprod *ui;
    QStringListModel* pointerToModel;
    Storage* pointerToProdData;
};

#endif // ADDPROD_H
