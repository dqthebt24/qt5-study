#include <QMenu>
#include <QDialog>
#include "myrect.h"

void MyRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[MyRect] Rect clicked at [%f, %f]", event->pos().x(), event->pos().y());

    if (event->button() == Qt::RightButton) {
        QMenu myMenu;
        QAction drawRectangle("Test 1");
        QAction drawCircle("Test 2");

        myMenu.addAction(&drawRectangle);
        myMenu.addAction(&drawCircle);
        QAction* selectedItem = myMenu.exec(event->screenPos());
        if (selectedItem) {
            QDialog a;
            a.setModal(true);
            a.exec();
        }
    }
}

MyRect::MyRect()
{
}

MyRect::~MyRect()
{
}
