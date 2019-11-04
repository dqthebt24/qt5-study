#include <QMenu>
#include <QDialog>
#include <QPen>
#include "myrect.h"

#define M_QT_DEFAULT_BG Qt::gray
#define M_QT_HOVER_BG Qt::yellow

void MyRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (mIsDecorate) {
        emit sigDecorateClick();
        return;
    }
    if (!mIsDisable) {
        if (mIsShowMenu) {
            // Show menu
            if (event->button() == Qt::RightButton) {
                QMenu myMenu;
                QAction drawRectangle("Test 1");
                QAction drawCircle("Test 2");

                myMenu.addAction(&drawRectangle);
                myMenu.addAction(&drawCircle);
                QAction* selectedItem = myMenu.exec(event->screenPos());
                if (selectedItem) {
                    emit sigDrawArrow(event->pos());
                    mIsDisable = true;
                }
            }
        } else {
            mIsDisable = true;
            emit sigHoldArrow(this);
        }
    }
}

void MyRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(QBrush(M_QT_HOVER_BG));
    this->setPen(Qt::SolidLine);
    Q_UNUSED(event);
}

void MyRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(QBrush(M_QT_DEFAULT_BG));
    this->setPen(Qt::DashLine);
    Q_UNUSED(event);
}

MyRect::MyRect(bool isDecorate) : mIsDraw(false), mIsDisable(false), mIsShowMenu(true)
{
    mIsDecorate = isDecorate;
    this->setBrush(QBrush(M_QT_DEFAULT_BG));
}

MyRect::~MyRect()
{
}

void MyRect::setDrawStatus(bool isDraw)
{
    mIsDraw = isDraw;
}

bool MyRect::getDrawStatus()
{
    return mIsDraw;
}

void MyRect::enableHover()
{
    setAcceptHoverEvents(true);
}

void MyRect::disableHover()
{
    setAcceptHoverEvents(false);
}

void MyRect::setDashedPen()
{
    this->setPen(Qt::DashLine);
}
