#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addprod.h"
#include "drawing.h"

#include <QFileDialog>
#include <QMessageBox>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _Storage = new Storage(this);
    _modelList =  new QStringListModel(this);
    _modelDetails =  new QStringListModel(this);

    ui->listView->setModel(_modelList);
    ui->listView2->setModel(_modelDetails);

    QObject::connect(_Storage, SIGNAL(fileOpen()),
                     this, SLOT(onDataStorageLoaded()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Data Storage"),
                                                    "",
                                                    tr("CSV Files (*.csv)"));
    if (fileName.isNull())
        return;

    _Storage->openFile(fileName);
}

void MainWindow::onDataStorageLoaded()
{
    _modelList->setStringList(_Storage->getKeys());
}

void MainWindow::on_pushButton_clicked()
{
    QString Value = ui->Input->text();

    bool correctValue;

    int Value1 = Value.toInt(&correctValue);
    if (!correctValue || Value1 < 0)
    {
        QMessageBox box;
        box.setText("Incorrect Value of Inserted money");
        box.exec();
        return;
    }
    QString value2 = ui->output->text();
    int Value2 = value2.toInt(&correctValue);

    int res= Value2 + Value1;
    ui->output->setText(QString::number(res));


}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString curProduct = index.data().toString();
    const Product& details = _Storage->getDetails(curProduct);

    QStringList detailedList;
    detailedList << "Name: " + details.name;
    detailedList << "Price: " + details.price;
    detailedList << "Quantity: " + details.quantity;
    _modelDetails->setStringList(detailedList);

}


void MainWindow::on_addBtn_clicked()
{
    addprod AddProd;
    AddProd.setModelPointer(_modelList);
    AddProd.setDataPointer(_Storage);
    AddProd.setModal(true);
    AddProd.exec();

}

void MainWindow::on_actionSaveFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Save file"),
                                                    "",
                                                    tr("CSV Files (*.csv)"));
    QFile f(fileName);
    f.open(QIODevice::WriteOnly);
    f.write("name,price,quantity\n");
    int size = _Storage->sizeoflist();
    QList<QString> listofkeys = _Storage->getKeys();
    for(int i = 0; i < size; i++)
    {
        Product details = _Storage->getDetails(listofkeys[i]);
        std::stringstream ss;
        std::string name = details.name.toStdString();
        std::string price = details.price.toStdString();
        std::string quantity = details.quantity.toStdString();
        ss << name << "," << price << "," << quantity << "\n";
        f.write(ss.str().c_str());
    }
    f.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    int selectedRow = ui->listView->currentIndex().row();
    _Storage->erase(_Storage->getKeys()[selectedRow]);
    _modelList->removeRows(selectedRow, 1);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString value2 = ui->output->text();
    if (value2.toInt() == 0)
        return;
    int row = _modelList->rowCount();
    _modelList->removeRows(0, row);
    row = 0;
    for (int i = 0; i < _Storage->getKeys().size(); i++)
    {
        Product prod = _Storage->getDetails(_Storage->getKeys()[i]);
        std::cout << prod.price.toStdString() << " " << prod.quantity.toStdString() << "\n";
        QStringList list1= prod.price.split(QLatin1Char(' '));
        int price = list1[0].toInt();

        QStringList list2= prod.quantity.split(QLatin1Char(' '));
        int quantity = list2[0].toInt();

        if (price <= value2 && quantity >= 1)
        {
            _modelList->insertRows(row, 1);
            QModelIndex index = _modelList->index(row, 0, QModelIndex());
            _modelList->setData(index, prod.name);
            row++;
        }

    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int row = _modelList->rowCount();
    _modelList->removeRows(0, row);
    row = 0;
    for (int i = 0; i < _Storage->getKeys().size(); i++)
    {
        _modelList->insertRows(row, 1);
        QModelIndex index = _modelList->index(row, 0, QModelIndex());
        _modelList->setData(index, _Storage->getKeys()[i]);
        row++;
    }
}

void MainWindow::on_actionHelp_triggered()
{
    drawing Drawing;
    Drawing.exec();
}
