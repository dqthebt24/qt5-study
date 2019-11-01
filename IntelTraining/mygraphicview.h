#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include "myrect.h"

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = nullptr);
    ~MyGraphicView();

protected:
    // Override functions
    void mousePressEvent(QMouseEvent *event);

private:
    QGraphicsScene *mScene;
    MyRect *mRect = nullptr;
    QPoint mClickedPoint;
    bool isDrawed;

    // Custom functions
    void initScene();
    void showMenu(const QPoint p);
    void drawRectangle();
};

#endif // MYGRAPHICVIEW_H
