#ifndef DRAWING_H
#define DRAWING_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class drawing;
}

class drawing : public QDialog
{
    Q_OBJECT

public:
    explicit drawing(QWidget *parent = nullptr);
    ~drawing();

private:
    Ui::drawing *ui;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // DRAWING_H
