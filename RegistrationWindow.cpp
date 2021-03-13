//
// Created by Uiqkos on 07.03.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RegistrationWindow.h" resolved

#include <QRegExpValidator>
#include <qdebug.h>
#include <QSqlError>
#include "RegistrationWindow.h"
#include "ui_RegistrationWindow.h"
#include "UserService.h"
#include "MainWindow.h"

const QRegExp EMAIL_REGEXP = QRegExp("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");

RegistrationWindow::RegistrationWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::RegistrationWindow) {
    ui->setupUi(this);
    ui->errorLabel->hide();

    auto passwordValidator = new QRegExpValidator(QRegExp("\\w+"));
    ui->passwordLineEdit->setValidator(passwordValidator);

    connect(ui->signUpButton, &QPushButton::clicked, this, &RegistrationWindow::signUp);
}

RegistrationWindow::~RegistrationWindow() {
    delete ui;
}

void RegistrationWindow::signUp() {
    if (validateForm()) {
        auto sqlError = UserService::getInstance()
            ->signUp({
             ui->usernameLineEdit->text(),
             ui->emailLineEdit->text(),
             ui->passwordLineEdit->text()
         });

        if (sqlError.type() == QSqlError::NoError) {
            auto mainWindow = new MainWindow();
            mainWindow->show();
            this->close();
        } else {
            ui->errorLabel->show();
            ui->errorLabel->setText("Ошибка: " + sqlError.text());
        }
    }
}

bool RegistrationWindow::validateForm() {
    auto emailValidator = new QRegExpValidator(EMAIL_REGEXP);
    int pos = 0;
    QString email = ui->emailLineEdit->text();

    if (ui->usernameLineEdit->text().length() < 3) {
        ui->errorLabel->show();
        ui->errorLabel->setText("Имя пользователя должно содержать не менее 3 символов");

    } else if (emailValidator->validate(email, pos) != QValidator::Acceptable) {
        ui->errorLabel->show();
        ui->errorLabel->setText("Невалидный адрес электронной почты");

    } else if (ui->passwordLineEdit->text().length() < 5) {
        ui->errorLabel->show();
        ui->errorLabel->setText("Пароль должен содержать не менее 5 символов");

    } else if (
            !ui->passwordLineEdit->text().contains(QRegExp("\\d")) ||
            !ui->passwordLineEdit->text().contains(QRegExp("[A-Z]")) ||
            !ui->passwordLineEdit->text().contains(QRegExp("[a-z]"))
            ) {
        ui->errorLabel->show();
        ui->errorLabel->setText("Пароль должен содержать прописные, строчные буквы и цифры");

    } else {
        return true;
    }
    return false;
}
