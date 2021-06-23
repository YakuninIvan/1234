#include "storage.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>

Storage::Storage(QObject* parent) : QObject(parent)
{

}

void Storage::openFile(const QString& fileName)
{
    _fileName = fileName;
    readFile();

    emit fileOpen();
}

QList<QString> Storage::getKeys() const
{
    QList<QString> list = _products.keys();
    return list;
}

void Storage::readFile()
{
    if (_fileName.isEmpty())
        throw std::runtime_error("File name is not set");

    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Could not open file");

    bool skipFirst = true;

    QTextStream fStream(&file);
    while (!fStream.atEnd())
    {
        QString line = fStream.readLine();
        if (line.isNull())
            continue;

        if(skipFirst)
        {
            skipFirst = false;
            continue;
        }

        QStringList list1= line.split(QLatin1Char(','));
        if (list1.size() < 3)
            continue;

        Product prod ={list1[0],list1[1],list1[2]};

        _products.insert(list1[0], prod);

    }

    file.close();
}

Product Storage::getDetails(const QString& product) const
{
    return _products[product];
}

void Storage::setDetails(Product prod)
{
    _products.insert(prod.name, prod);
}

int Storage::sizeoflist() const
{
    return _products.size();
}

void Storage::erase(QString& str)
{
    _products.remove(str);
}

