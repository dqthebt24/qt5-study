#ifndef MYFILTER_H
#define MYFILTER_H
#include <QSortFilterProxyModel>

class MyFilter : public QSortFilterProxyModel
{
    Q_OBJECT
private:
    bool hasChildMatchFilter(QAbstractItemModel* model, QModelIndex parent = QModelIndex()) const;
public:
    MyFilter(QObject* parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // MYFILTER_H
