#include <QMenu>
#include <QDialog>
#include "myrect.h"

void MyRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
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

MyRect::MyRect() : mIsDraw(false), mIsDisable(false), mIsShowMenu(true)
{
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
