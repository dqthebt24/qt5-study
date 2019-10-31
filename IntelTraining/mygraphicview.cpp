#include "mygraphicview.h"
#include <QMenu>
MyGraphicView::MyGraphicView(QWidget *parent) : QGraphicsView (parent)
{
    initScene();
}

MyGraphicView::~MyGraphicView()
{
    delete mScene;
}

void MyGraphicView::initScene()
{
    mScene = new QGraphicsScene();
    //mScene->setBackgroundBrush(Qt::red);

    this->setScene(mScene);
    this->setGeometry(0,0, 100, 100);
}

void MyGraphicView::setGraphicViewSize(int w, int h)
{
    this->setGeometry(0,0, w, h);
}

void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
    qDebug("Clicked at [%d, %d]", event->x(), event->y());
    if (event->button() == Qt::RightButton) {
        mClickedPoint = QPoint(event->x(), event->y());
        showMenu(QPoint(event->globalX(), event->globalY()));
    }
}

void MyGraphicView::showMenu(const QPoint p)
{
    QMenu myMenu;
    QAction drawRectangle("Draw rectangle");
    QAction drawCircle("Draw circle");

    myMenu.addAction(&drawRectangle);
    myMenu.addAction(&drawCircle);
    QAction* selectedItem = myMenu.exec(p);
    if (selectedItem)
    {
        if (selectedItem->text() == "Draw circle") {
            this->drawCircle();
        }
        else {
            this->drawRectangle();
        }
    }
    else
    {
        qDebug("nothing was chosen");
    }
}

void MyGraphicView::drawRectangle()
{
    qDebug("Draw rectangle at [%d, %d]", mClickedPoint.x(), mClickedPoint.y());
}

void MyGraphicView::drawCircle()
{
    qDebug("Draw circle at [%d, %d]", mClickedPoint.x(), mClickedPoint.y());
}
