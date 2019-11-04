#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MyRect : public QGraphicsRectItem
{
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public:
    MyRect();
    ~MyRect();

};

#endif // MYRECT_H
