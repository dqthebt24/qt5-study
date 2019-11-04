#ifndef MYARROW_H
#define MYARROW_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MyArrow : public QGraphicsRectItem
{
private:
    int mWidth;
    int mHeight;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    MyArrow();
    ~MyArrow();
};

#endif // MYARROW_H
