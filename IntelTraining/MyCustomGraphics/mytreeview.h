#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QTreeView>

class MyTreeView : public QTreeView
{
protected:
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
public:
    MyTreeView(QWidget *parent = 0);
    QModelIndexList selecteds() {return selectedIndexes();}
};

#endif // MYTREEVIEW_H
