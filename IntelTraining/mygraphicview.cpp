#include <QMenu>
#include <QGraphicsRectItem>
#include <QPointF>

#include "mygraphicview.h"

#define M_WIDTH 200
#define M_HEIGHT 200
MyGraphicView::MyGraphicView(QWidget *parent) : QGraphicsView (parent), mIsCaptureMouseMove(false)
{
    initScene();
    initRects();
    initArrow();

    setMouseTracking(true);
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

    for (int i = 0 ;i < mListSurroundRect.size(); i++){
        delete mListSurroundRect[i];
    }

    for (int i = 0 ;i < mListRandomRect.size(); i++){
        delete mListRandomRect[i];
    }
    delete mScene;
}

void MyGraphicView::onDrawRectAt(QPoint screenPos)
{
    QPointF p = this->mapToScene(screenPos);
    MyRect *rect = new MyRect(true);
    rect->setBrush(QBrush(QColor(255, 0, 255)));
    rect->setRect(p.x(), p.y(), 30, 30);
    mListRandomRect.push_back(rect);
    mScene->addItem(rect);
}

void MyGraphicView::initScene()
{
    mScene = new QGraphicsScene();
//    this->setBackgroundBrush(Qt::yellow);
//    mScene->setBackgroundBrush(Qt::red);

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
    mArrow = new MyArrow(QPointF(0, 0), QPointF(0, 0));
    mScene->addItem(mArrow);
}

void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
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
        mArrow->setEnd(this->mapToScene(event->pos()));
        mScene->update();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicView::dragMoveEvent(QDragMoveEvent *event)
{
    Q_UNUSED(event);
}

void MyGraphicView::dropEvent(QDropEvent *event)
{
    emit sigDropItem(event->pos());
}

void MyGraphicView::onDrawArrow(QPointF p)
{
    if (mArrow != nullptr) {
        mArrow->enable();
        mArrow->setStart(this->mapToScene(this->mapFromScene(p)));
        mArrow->setEnd(this->mapToScene(this->mapFromScene(p)));

        enableMoveMoveTrack();

        mFirstRect->disbaleShowMenuFunction();
        mSecondRect->disbaleShowMenuFunction();
    }
}

void MyGraphicView::onHoldArrow(MyRect * const rect)
{
    if (rect == mFirstRect) {
        drawSurroundRect(mListClickedPoint[0]);
    } else if (rect == mSecondRect) {
        drawSurroundRect(mListClickedPoint[1]);
    }
    disableMoveMoveTrack();
}

void MyGraphicView::onDecorateClick()
{
    while(mListSurroundRect.size() > 0){
        MyRect* tmp = mListSurroundRect[0];
        mListSurroundRect.pop_front();
        delete tmp;
    }
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
        mFirstRect -> setRect(mClickedPoint.x(), mClickedPoint.y(), M_HEIGHT, M_WIDTH);
        mFirstRect->setDrawStatus(true);
        mListClickedPoint.push_back(mClickedPoint);
    } else if (mSecondRect->getDrawStatus() == false) {
        mListClickedPoint.push_back(mClickedPoint);
        mSecondRect -> setRect(mClickedPoint.x(), mClickedPoint.y(), M_HEIGHT, M_WIDTH);
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
}

void MyGraphicView::disableMoveMoveTrack()
{
    mIsCaptureMouseMove = false;
}

void MyGraphicView::drawSurroundRect(const QPointF pTopLeft)
{
    int margin = 10, size = 60;
    int space = (M_WIDTH - (3*size)) / 2;
    for (int i = 0; i < 3; i++) {
        MyRect *rectAbove = new MyRect(true);
        rectAbove->setRect(pTopLeft.x() + i*size + i* space, pTopLeft.y() - size - margin, size, size);
        mScene->addItem(rectAbove);
        mListSurroundRect.push_back(rectAbove);

        MyRect *rectBelow = new MyRect(true);
        rectBelow->setRect(pTopLeft.x() + i*size + i* space, pTopLeft.y() + M_WIDTH + margin, size, size);
        mScene->addItem(rectBelow);
        mListSurroundRect.push_back(rectBelow);
    }

    MyRect *rectLeft = new MyRect(true);
    rectLeft->setRect(pTopLeft.x() - margin - size, pTopLeft.y() + M_HEIGHT/2 - size/2, size, size);
    mScene->addItem(rectLeft);
    mListSurroundRect.push_back(rectLeft);

    MyRect *rectRight = new MyRect(true);
    rectRight->setRect(pTopLeft.x() + margin + M_WIDTH, pTopLeft.y() + M_HEIGHT/2 - size/2, size, size);
    mScene->addItem(rectRight);
    mListSurroundRect.push_back(rectRight);

    for (int i = 0; i < mListSurroundRect.size(); i++) {
        mListSurroundRect[i]->enableHover();
        mListSurroundRect[i]->setDashedPen();
        connect(mListSurroundRect[i], SIGNAL(sigDecorateClick()), this, SLOT(onDecorateClick()));
    }
}
