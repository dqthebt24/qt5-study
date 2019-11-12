#include "mytreeview.h"

void MyTreeView::dragMoveEvent(QDragMoveEvent *event)
{
    Q_UNUSED(event);
}

void MyTreeView::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event);
}

MyTreeView::MyTreeView(QWidget *parent) : QTreeView(parent)
{
    setAcceptDrops(false);
}
