#include <QMenu>
#include <QGraphicsRectItem>

#include "mygraphicview.h"
MyGraphicView::MyGraphicView(QWidget *parent) : QGraphicsView (parent), isDrawed(false)
{
    setMouseTracking(true);
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
    this->setBackgroundBrush(Qt::yellow);
    mScene->setBackgroundBrush(Qt::red);

    this->setScene(mScene);
    this->viewport()->size().width();
    this->setSceneRect(0, 0, this->viewport()->size().width(), this->viewport()->size().height());
}

void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && !isDrawed) {
        mClickedPoint = this->mapToScene(event->pos());
        showMenu(QPoint(event->globalX(), event->globalY()));
    } else {
        QGraphicsView::mousePressEvent(event);
    }

    if (event->button() == Qt::RightButton && isDrawed) {
        MyArrow *arrow = new MyArrow();
        mScene->addItem(arrow);
        arrow->setPos(this->mapToScene(event->pos()));
        qDebug("Draw arrow!");
    }
}

void MyGraphicView::mouseMoveEvent(QMouseEvent *event)
{
    if(isDrawed) {
        QPointF p = this->mapToScene(event->pos());
        // mRect -> setRect( p.x(), p.y(), 200, 200);
    }
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
        mRect ->setBrush(QBrush(Qt::green));
    }

    mRect -> setRect(mClickedPoint.x(), mClickedPoint.y(), 200, 200);
    isDrawed = true;
}
