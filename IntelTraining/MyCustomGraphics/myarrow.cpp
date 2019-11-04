#include "myarrow.h"
#include <QPolygon>
#include <QPainter>

QRectF MyArrow::boundingRect() const
{
    return QRectF(-mWidth/2,-mHeight/2, mWidth, mHeight);
}

void MyArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(0,-mHeight/2) << QPoint(mWidth/2, 0) << QPoint(mWidth/4, 0) << QPoint(mWidth/4, mHeight/2) << QPoint(-mWidth/4, mHeight/2)
            << QPoint(-mWidth/4, 0) << QPoint(-mWidth/2, 0);
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

MyArrow::MyArrow() : mWidth(50), mHeight(50)
{

}

MyArrow::~MyArrow()
{
}
