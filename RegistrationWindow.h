//
// Created by Uiqkos on 07.03.2021.
//

#ifndef TODO_LIST_REGISTRATIONWINDOW_H
#define TODO_LIST_REGISTRATIONWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class RegistrationWindow; }
QT_END_NAMESPACE

class RegistrationWindow : public QWidget {
Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);

    ~RegistrationWindow() override;

private slots:
    void signUp();

private:
    Ui::RegistrationWindow *ui;
    bool validateForm();
};

#endif //TODO_LIST_REGISTRATIONWINDOW_H
