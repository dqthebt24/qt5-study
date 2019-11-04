#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGraphicView();
    initWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete vLayout;
}

void MainWindow::initWindow()
{
    this->setGeometry(0,0, 800, 800);
    vLayout = new QVBoxLayout();
    vLayout->addWidget(mGraphicView);

    ui->centralWidget->setGeometry(0,0, 800, 800);
    ui->centralWidget->setLayout(vLayout);
    //setGraphicViewSize(ui->centralWidget->geometry().width(), ui->centralWidget->geometry().height());

}

void MainWindow::initGraphicView()
{
    mGraphicView = new MyGraphicView();
}


