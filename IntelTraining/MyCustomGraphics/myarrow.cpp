#include "myarrow.h"
#include <QPolygon>
#include <QPainter>
#include <QDebug>
#include <QString>

const qreal PI = 3.14;

QRectF MyArrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void MyArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!mIsShow) {
        QPen myPen = pen();
        myPen.setColor(QColor(255,0,255));
        painter->setPen(myPen);
        painter->setBrush(QColor(255,0,255));
        return;
    }
    qreal arrowSize = 20;
    painter->setBrush(QColor(0,0,0));

    double angle = ::atan2(mEnd.y() - mStart.y(), mEnd.x() - mStart.x()) + PI;

    QPointF arrowP1(mEnd.x() + arrowSize*cos(angle - PI/6), mEnd.y() + arrowSize*sin(angle - PI/6));
    QPointF arrowP2(mEnd.x() + arrowSize*cos(angle + PI/6), mEnd.y() + arrowSize*sin(angle + PI/6));

    arrowHead.clear();
    arrowHead << mEnd << arrowP2 << arrowP1;
    painter->drawLine(mStart, mEnd);
    painter->drawPolygon(arrowHead);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath MyArrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

MyArrow::MyArrow(QPointF start, QPointF end) : mIsShow(false)
{
    mStart = start;
    mEnd = end;
}

MyArrow::~MyArrow()
{
}
