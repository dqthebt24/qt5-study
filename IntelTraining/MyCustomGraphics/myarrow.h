#ifndef MYARROW_H
#define MYARROW_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MyArrow : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int mWidth;
    int mHeight;
    bool mIsShow;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    MyArrow();
    ~MyArrow();
    void enable() {mIsShow = true;}
};

#endif // MYARROW_H
