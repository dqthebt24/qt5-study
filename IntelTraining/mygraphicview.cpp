#include <QMenu>
#include <QGraphicsRectItem>

#include "mygraphicview.h"
MyGraphicView::MyGraphicView(QWidget *parent) : QGraphicsView (parent), isDrawed(false)
{
    initScene();
}

MyGraphicView::~MyGraphicView()
{
    if ( mRect != nullptr) {
        delete mRect;
    }
    delete mScene;
}

void MyGraphicView::initScene()
{
    mScene = new QGraphicsScene();
    // this->setBackgroundBrush(Qt::yellow);

    this->setScene(mScene);
    this->viewport()->size().width();
    this->setSceneRect(0, 0, this->viewport()->size().width(), this->viewport()->size().height());
}

void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
    qDebug("Clicked at [%d, %d]", event->x(), event->y());
    if (event->button() == Qt::RightButton && !isDrawed) {
        mClickedPoint = QPoint(event->x(), event->y());
        showMenu(QPoint(event->globalX(), event->globalY()));
    }
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicView::showMenu(const QPoint p)
{
    QMenu myMenu;
    QAction drawRectangle("Draw rectangle");
    QAction drawCircle("Clear rectangle");

    myMenu.addAction(&drawRectangle);
    myMenu.addAction(&drawCircle);
    QAction* selectedItem = myMenu.exec(p);
    if (selectedItem)
    {
        if (selectedItem->text() == "Draw rectangle") {
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
    if (mRect == nullptr) {
        qDebug("Create my rect");
        mRect = new MyRect();
        mScene->addItem(mRect);
    }

    mRect -> setRect(mClickedPoint.x(), mClickedPoint.y(), 100, 100);
    mRect ->setBrush(QBrush(Qt::green));
    isDrawed = true;
    qDebug("Draw rectangle at [%d, %d]", mClickedPoint.x(), mClickedPoint.y());

}
