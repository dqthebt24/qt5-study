#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QObject>

class MyRect : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    bool mIsDraw;
    bool mIsDisable;
    bool mIsShowMenu;
    bool mIsDecorate;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
//    void hoverEnterEvent (QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent (QGraphicsSceneHoverEvent * event);

signals:
    void sigDrawArrow(QPointF);
    void sigHoldArrow(MyRect* const);
    void sigDecorateClick();

public:
    MyRect(bool isDecorate = false);
    ~MyRect();
    void setDrawStatus(bool isDraw);
    bool getDrawStatus();
    void disbaleShowMenuFunction() {mIsShowMenu = false;}
    void enableHover();
    void disableHover();
    void setDashedPen();
};

#endif // MYRECT_H
