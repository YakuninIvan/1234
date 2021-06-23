#include "addprod.h"
#include "ui_addprod.h"
#include "storage.h"

#include <QString>
#include <QMessageBox>

addprod::addprod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addprod)
{
    ui->setupUi(this);
}

addprod::~addprod()
{
    delete ui;
}

void addprod::setModelPointer(QStringListModel* model)
{
    pointerToModel = model;
}

void addprod::setDataPointer(Storage *prodData)
{
    pointerToProdData = prodData;
}

void addprod::on_pushButton_clicked()
{
    QString Name = ui->NameInp->text();

    QString Price = ui->PriceInp->text();

    bool correctvalue;

    int price = Price.toInt(&correctvalue);
    if (!correctvalue || price <= 0)
    {
        QMessageBox box;
        box.setText("Incorrect Value of Price");
        box.exec();
        return;
    }

    QString Quantity = ui->QuantityInp->text();

    int quantity = Quantity.toInt(&correctvalue);
    if (!correctvalue || quantity < 0)
    {
        QMessageBox box;
        box.setText("Incorrect Value of Quantity");
        box.exec();
        return;
    }

    Product prod = {Name, Price + " RUB", Quantity + " units"};

    int row  = pointerToModel->rowCount();
    pointerToModel->insertRows(row, 1);
    QModelIndex index = pointerToModel->index(row, 0, QModelIndex());
    pointerToModel->setData(index, Name);
    pointerToProdData->setDetails(prod);

}
