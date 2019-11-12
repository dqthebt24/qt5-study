#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include "MyCustomGraphics\myrect.h"
#include "MyCustomGraphics\myarrow.h"

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = nullptr);
    ~MyGraphicView();

protected:
    // Override functions
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
signals:
    void sigDropItem(QPoint p);
public slots:
    void onDrawArrow(QPointF p);
    void onHoldArrow(MyRect* const);
    void onDecorateClick();
    void onDrawRectAt(QPoint screenPos);

private:
    QGraphicsScene *mScene;
    MyRect *mFirstRect = nullptr;
    MyRect *mSecondRect = nullptr;
    MyArrow *mArrow = nullptr;
    bool mIsCaptureMouseMove;

    QPointF mClickedPoint;
    QList<QPointF> mListClickedPoint;
    QList<MyRect*> mListSurroundRect;
    QList<MyRect*> mListRandomRect;

    // Custom functions
    void initScene();
    void initRects();
    void initArrow();
    void showMenu(const QPoint p);
    void drawRectangle();
    bool isFulledDraw();
    void enableMoveMoveTrack();
    void disableMoveMoveTrack();
    void drawSurroundRect(const QPointF pTopLeft);
};

#endif // MYGRAPHICVIEW_H
