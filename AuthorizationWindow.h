//
// Created by Uiqkos on 07.03.2021.
//

#ifndef TODO_LIST_AUTHORIZATIONWINDOW_H
#define TODO_LIST_AUTHORIZATIONWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AuthorizationWindow; }
QT_END_NAMESPACE

class AuthorizationWindow : public QWidget {
Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);

    ~AuthorizationWindow() override;

private slots:
    void signIn();
    void signUp();

private:
    Ui::AuthorizationWindow *ui;
};

#endif //TODO_LIST_AUTHORIZATIONWINDOW_H
