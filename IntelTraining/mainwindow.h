#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QPalette>
#include <QVBoxLayout>
#include "mygraphicview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVBoxLayout* vLayout;
    MyGraphicView *mGraphicView;

    void initWindow();
    void initGraphicView();
};

#endif // MAINWINDOW_H
