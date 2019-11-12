#ifndef MYTREEITEM_H
#define MYTREEITEM_H

#include <QObject>
#include <QStandardItem>

class MyTreeItem : public QObject, public QStandardItem
{
    Q_OBJECT
public:
    explicit MyTreeItem(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYTREEITEM_H
