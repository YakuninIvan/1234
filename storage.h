#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QMap>
#include <iostream>


struct Product {
    QString name;
    QString price;
    QString quantity;
};

class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject* parent = nullptr);

public:
    void openFile(const QString& fileName);
    QList<QString> getKeys() const;
    Product getDetails(const QString& product) const;
    void setDetails(Product prod);
    int sizeoflist() const;
    void erase(QString& str);

protected:
    void readFile();

protected:
    QString _fileName;
    QMap<QString, Product> _products;

signals:
    void fileOpen();

};

#endif // STORAGE_H
