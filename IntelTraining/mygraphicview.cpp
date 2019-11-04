#include <QMenu>
#include <QGraphicsRectItem>
#include <QPointF>

#include "mygraphicview.h"
MyGraphicView::MyGraphicView(QWidget *parent) : QGraphicsView (parent), mIsCaptureMouseMove(false)
{
    initScene();
    initRects();
    initArrow();
}

MyGraphicView::~MyGraphicView()
{
    if ( mFirstRect != nullptr) {
        delete mFirstRect;
    }

    if ( mSecondRect != nullptr) {
        delete mSecondRect;
    }

    if (mArrow != nullptr) {
        delete mArrow;
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

void MyGraphicView::initRects()
{
    mFirstRect = new MyRect();
    mFirstRect->setBrush(QBrush(Qt::green));

    mSecondRect = new MyRect();
    mSecondRect->setBrush(QBrush(Qt::green));

    mScene->addItem(mFirstRect);
    mScene->addItem(mSecondRect);

    connect(mFirstRect, SIGNAL(sigDrawArrow(QPointF)), this, SLOT(onDrawArrow(QPointF)));
    connect(mSecondRect, SIGNAL(sigDrawArrow(QPointF)), this, SLOT(onDrawArrow(QPointF)));
    connect(mFirstRect, SIGNAL(sigHoldArrow(MyRect* const)), this, SLOT(onHoldArrow(MyRect* const)));
    connect(mSecondRect, SIGNAL(sigHoldArrow(MyRect* const)), this, SLOT(onHoldArrow(MyRect* const)));
}

void MyGraphicView::initArrow()
{
    mArrow = new MyArrow();
    mScene->addItem(mArrow);
}

void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
    qDebug("View clicked [%d,%d]", event->x(), event->y());
    if (event->button() == Qt::RightButton && !isFulledDraw()) {
        mClickedPoint = this->mapToScene(event->pos());
        showMenu(QPoint(event->globalX(), event->globalY()));
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void MyGraphicView::mouseMoveEvent(QMouseEvent *event)
{
    if (mArrow != nullptr && mIsCaptureMouseMove) {
        mArrow->setPos(this->mapToScene(event->pos()));
    }
}

void MyGraphicView::onDrawArrow(QPointF p)
{
    if (mArrow != nullptr) {
        mArrow->enable();
        mArrow->setPos(this->mapToScene(this->mapFromScene(p)));

        enableMoveMoveTrack();

        mFirstRect->disbaleShowMenuFunction();
        mSecondRect->disbaleShowMenuFunction();
    }
}

void MyGraphicView::onHoldArrow(MyRect * const rect)
{
    if (rect == mFirstRect) {
        qDebug("Rect 1 Hold");
    } else if (rect == mSecondRect) {
        qDebug("Rect 2 Hold");
    }
    disableMoveMoveTrack();
}

void MyGraphicView::showMenu(const QPoint p)
{
    QMenu myMenu;
    QAction drawRectangle("Draw rectangle");

    myMenu.addAction(&drawRectangle);
    QAction* selectedItem = myMenu.exec(p);
    if (selectedItem)
    {
        this->drawRectangle();
    }
    else
    {
        qDebug("nothing was chosen");
    }
}

void MyGraphicView::drawRectangle()
{
    if (mFirstRect->getDrawStatus() == false) {
        mFirstRect -> setRect(mClickedPoint.x(), mClickedPoint.y(), 200, 200);
        mFirstRect->setDrawStatus(true);
    } else if (mSecondRect->getDrawStatus() == false) {
        mSecondRect -> setRect(mClickedPoint.x(), mClickedPoint.y(), 200, 200);
        mSecondRect->setDrawStatus(true);
    }
}

bool MyGraphicView::isFulledDraw()
{
    return mFirstRect->getDrawStatus() && mSecondRect->getDrawStatus();
}

void MyGraphicView::enableMoveMoveTrack()
{
    mIsCaptureMouseMove = true;
    setMouseTracking(true);
}

void MyGraphicView::disableMoveMoveTrack()
{
    mIsCaptureMouseMove = false;
    setMouseTracking(false);
}
