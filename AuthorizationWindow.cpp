//
// Created by Uiqkos on 07.03.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AuthorizationWindow.h" resolved

#include "AuthorizationWindow.h"
#include "ui_AuthorizationWindow.h"
#include "RegistrationWindow.h"
#include "MainWindow.h"
#include "UserService.h"
#include <qdebug.h>
#include <QSqlError>

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::AuthorizationWindow) {

    ui->setupUi(this);
    ui->errorLabel->hide();
    connect(ui->signInButton, &QPushButton::clicked, this, &AuthorizationWindow::signIn);
    connect(ui->signUpButton, &QPushButton::clicked, this, &AuthorizationWindow::signUp);
}

AuthorizationWindow::~AuthorizationWindow() {
    delete ui;
}

void AuthorizationWindow::signIn() {
    auto username = ui->loginLineEdit->text();
    auto password = ui->passwordLineEdit->text();

    if (UserService::getInstance()
        ->signIn({username, "", password}).type() == QSqlError::NoError){

        auto mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
        return;
    }

    ui->errorLabel->setText("Неверное имя пользоваеля или пароль");
    ui->errorLabel->show();
}

void AuthorizationWindow::signUp() {
    auto registrationWindow = new RegistrationWindow();
    registrationWindow->show();
    this->close();
}
