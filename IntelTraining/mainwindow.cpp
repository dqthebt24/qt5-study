#include "mainwindow.h"
#include "ui_mainwindow.h"

#define NUM_CHILD 4
#define CHILD_ICON_PATH_1 "C://Users//the.do//Desktop//icon-child-1.png"
#define CHILD_ICON_PATH_2 "C://Users//the.do//Desktop//icon-child-2.png"
#define PARENT_ICON_PATH "C://Users//the.do//Desktop//icon-parent.png"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();
}

MainWindow::~MainWindow()
{
    delete mGraphicView;

    for (int i = 0; i < mListItem1.length(); i++) {
        delete mListItem1[i];
    }
    for (int i = 0; i < mListItem2.length(); i++) {
        delete mListItem2[i];
    }

    delete mItemParentFirst;
    delete mItemParentSecond;
    delete mSourceModel;
    delete mTreeView;
    delete mHLayout;

    delete mFilterText;
    delete mProxyModel;
    delete ui;
}

void MainWindow::onDropItem(QPoint pos)
{
    emit sigDrawRectAtDropPos(pos);

    QModelIndex selected = mTreeView->currentIndex();
    qDebug(QString("%0 | %1").arg(selected.parent().row() == 0 ? mListItem1[selected.row()]->text() : mListItem2[selected.row()]->text())
            .arg(selected.parent().row() == 0 ? CHILD_ICON_PATH_1 : CHILD_ICON_PATH_2).toStdString().c_str());
}

void MainWindow::onFilterTextChanged()
{
    mProxyModel->setFilterRegExp(QRegExp(mFilterText->toPlainText(), Qt::CaseSensitive,
                                       QRegExp::FixedString));
}

void MainWindow::initWindow()
{
    this->setGeometry(0,0, 800, 800);
    mHLayout = new QHBoxLayout();

    initLeftPanel();
    mHLayout->addItem(mVLeftPanel);


    initRightPanel();
    mHLayout->addItem(mVRightPanel);

    ui->centralWidget->setGeometry(0,0, 100, 100);
    ui->centralWidget->setLayout(mHLayout);
}

void MainWindow::initLeftPanel()
{
    mVLeftPanel = new QVBoxLayout();

    initGraphicView();
    mVLeftPanel->addWidget(mGraphicView);
}

void MainWindow::initRightPanel()
{
    mVRightPanel = new QVBoxLayout();

    mFilterText = new QPlainTextEdit();
    mFilterText->setFixedSize(400, 30);
    mFilterText->setStyleSheet("QPlainTextEdit {margin-bottom: 5px}");
    mFilterText->setLineWrapMode(QPlainTextEdit::NoWrap);
    mFilterText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mFilterText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mFilterText->setPlainText("");
    connect(mFilterText, SIGNAL(textChanged()), this, SLOT(onFilterTextChanged()));

    initTreeView();

    mVRightPanel->addWidget(mFilterText);
    mVRightPanel->addWidget(mTreeView);
}

void MainWindow::initTreeView()
{
    mTreeView = new MyTreeView();
    mTreeView->setFixedWidth(400);

    mSourceModel = new QStandardItemModel();
    mItemParentFirst = new QStandardItem(QIcon(PARENT_ICON_PATH), "First parent");
    mItemParentFirst->setDragEnabled(false);

    mItemParentSecond = new QStandardItem(QIcon(PARENT_ICON_PATH), "Second parent");
    mItemParentSecond->setDragEnabled(false);

    for(int i = 0; i < NUM_CHILD; i++){
        QString text = "First child " + QString::number(i + 1);
        QStandardItem* item = new QStandardItem(QIcon(CHILD_ICON_PATH_1), text);
        item->setDragEnabled(true);
        mListItem1.append(item);
    }

    for(int i = 0; i < NUM_CHILD; i++){
        QString text = "Second child " + QString::number(i + 1);
        QStandardItem* item = new QStandardItem(QIcon(CHILD_ICON_PATH_2), text);
        item->setDragEnabled(true);
        mListItem2.append(item);
    }

    mItemParentFirst->appendRows(mListItem1);
    mItemParentSecond->appendRows(mListItem2);

    mSourceModel->appendRow(mItemParentFirst);
    mSourceModel->appendRow(mItemParentSecond);

    mProxyModel = new MyFilter(this);
    mProxyModel->setSourceModel(mSourceModel);

    mTreeView->setHeaderHidden(true);
    mTreeView->setModel(mProxyModel);
    mTreeView->setDragEnabled(true);
}

void MainWindow::initGraphicView()
{
    mGraphicView = new MyGraphicView();
    connect(mGraphicView, SIGNAL(sigDropItem(QPoint)), this, SLOT(onDropItem(QPoint)));
    connect(this, SIGNAL(sigDrawRectAtDropPos(QPoint)), mGraphicView, SLOT(onDrawRectAt(QPoint)));
}


