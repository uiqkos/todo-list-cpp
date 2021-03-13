#include <QApplication>
#include <QPushButton>
#include "AuthorizationWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("todo-list");

    auto authorizationWindow = AuthorizationWindow();
    authorizationWindow.show();

    return QApplication::exec();
}
