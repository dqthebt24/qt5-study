#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = nullptr);
    ~MyGraphicView();

private:
    QGraphicsScene *mScene;
    QPoint mClickedPoint;

    void initScene();
    void setGraphicViewSize(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void showMenu(const QPoint p);
    void drawRectangle();
    void drawCircle();
};

#endif // MYGRAPHICVIEW_H
