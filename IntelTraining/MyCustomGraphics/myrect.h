#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class MyRect : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    MyRect();
    ~MyRect();
    void setDrawStatus(bool isDraw);
    bool getDrawStatus();
    void disbaleShowMenuFunction() {mIsShowMenu = false;}

signals:
    void sigDrawArrow(QPointF);
    void sigHoldArrow(MyRect* const);

private:
    bool mIsDraw;
    bool mIsDisable;
    bool mIsShowMenu;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYRECT_H
