#ifndef MYARROW_H
#define MYARROW_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

class MyArrow : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
private:
    bool mIsShow;
    QPointF mStart;
    QPointF mEnd;
    QPolygonF arrowHead;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    MyArrow(QPointF start, QPointF end);
    ~MyArrow();
    void enable() {mIsShow = true;}
    QPainterPath shape() const;
    void setEnd(QPointF end) {mEnd = end;}
    void setStart(QPointF start) {mStart = start;}
};

#endif // MYARROW_H
