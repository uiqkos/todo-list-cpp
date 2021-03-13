//
// Created by Uiqkos on 07.03.2021.
//

#ifndef TODO_LIST_MAINWINDOW_H
#define TODO_LIST_MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};

#endif //TODO_LIST_MAINWINDOW_H
