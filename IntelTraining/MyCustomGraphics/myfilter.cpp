#include "myfilter.h"
#include <QDebug>
#include <QVariant>

bool MyFilter::hasChildMatchFilter(QAbstractItemModel *model, QModelIndex parent) const
{
    for(int r = 0; r < model->rowCount(parent); ++r) {
        QModelIndex index = model->index(r, 0, parent);
        QVariant name = model->data(index);
        if (name.value<QString>().contains(filterRegExp()))
            return true;

        if( model->hasChildren(index) ) {
            if (hasChildMatchFilter(model, index))
                return true;
        }
    }
    return false;
}

MyFilter::MyFilter(QObject *parent): QSortFilterProxyModel(parent)
{

}

bool MyFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex root = sourceModel()->index(source_row, 0, source_parent);
    return sourceModel()->data(root).toString().contains(filterRegExp()) || hasChildMatchFilter(sourceModel(), root);
}
