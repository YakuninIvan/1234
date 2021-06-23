#include "drawing.h"
#include "ui_drawing.h"

drawing::drawing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::drawing)
{
    ui->setupUi(this);
}

drawing::~drawing()
{
    delete ui;
}

void drawing::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.drawRect(QRect(10,10,100,200));

}
