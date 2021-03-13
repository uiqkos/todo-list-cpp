#include <QSqlDatabase>

class UserService {
private:
    QSqlDatabase db;
    int userId;
    static UserService* instance;
    UserService();

public:
    struct User {
        QString username;
        QString email;
        QString password;
    };

    static UserService* getInstance();

    ~UserService();

    QSqlError signUp(const User& user);
    QSqlError signIn(const User& user);
    void printUsers();

    static QString generateHash(const QString &data);
};
