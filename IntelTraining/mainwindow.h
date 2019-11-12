#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QPalette>
#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include <QPlainTextEdit>
#include "mygraphicview.h"
#include "MyCustomGraphics/mytreeview.h"
#include "MyCustomGraphics/mytreeitem.h"
#include "MyCustomGraphics/myfilter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sigDrawRectAtDropPos(QPoint screenPos);

private slots:
    void onDropItem(QPoint p);
    void onFilterTextChanged();

private:
    Ui::MainWindow *ui;
    QHBoxLayout* mHLayout;
    QVBoxLayout* mVLeftPanel;
    QVBoxLayout* mVRightPanel;
    MyGraphicView *mGraphicView;
    QPlainTextEdit *mFilterText;
    MyTreeView* mTreeView;
    QList<QStandardItem*> mListItem1;
    QList<QStandardItem*> mListItem2;
    MyFilter *mProxyModel;
    QStandardItemModel* mSourceModel;
    QStandardItem* mItemParentFirst;
    QStandardItem* mItemParentSecond;

    void initWindow();
    void initLeftPanel();
    void initRightPanel();
    void initTreeView();
    void initGraphicView();
};

#endif // MAINWINDOW_H
