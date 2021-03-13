//
// Created by Uiqkos on 07.03.2021.
//

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QCryptographicHash>
#include <qdebug.h>
#include <QStandardPaths>
#include <QDir>
#include "UserService.h"

QString SALT = "Q9st02dS";

UserService* UserService::instance = nullptr;

QSqlError UserService::signUp(const UserService::User& user) {
    QSqlQuery query;
    query.prepare("insert into users(username, email, password_hash) values(?, ?, ?)");
    query.addBindValue(user.username);
    query.addBindValue(user.email);
    query.addBindValue(generateHash(user.password));

    if (!query.exec()) {
        return query.lastError();
    }

    QSqlQuery lastIdQuery("select * from users order by id desc");
    lastIdQuery.exec();

    if (!lastIdQuery.first()) return lastIdQuery.lastError();

    userId = lastIdQuery.value(0).toInt();

    qDebug() << userId;

    return lastIdQuery.lastError();
}

QSqlError UserService::signIn(const UserService::User &user) {
    QSqlQuery query("select id from users where password_hash = ? and username = ?");
    query.addBindValue(generateHash(user.password));
    query.addBindValue(user.username);

    if (!query.exec()) return query.lastError();
    if (!query.first())
        return QSqlError("Sqlite: ",
        "user not found",QSqlError::TransactionError);

    userId = query.value(0).toInt();

    return query.lastError();
}

QString UserService::generateHash(const QString& data) {
    QCryptographicHash hash(QCryptographicHash::Algorithm::Sha256);
    hash.addData(data.toLatin1());
    hash.addData(SALT.toLatin1());
    return QString(hash.result().toHex());
}

UserService::UserService() {
    db = QSqlDatabase::addDatabase("QSQLITE");

    QDir applicationDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

    if (!applicationDir.exists())
        applicationDir.mkpath(".");

    QString dbPath = QString("%1%2todo-list.database")
        .arg(applicationDir.absolutePath())
        .arg(QDir::separator());

    qDebug() << dbPath;

    db.setDatabaseName(dbPath);

    qDebug() << db.open();

    QSqlQuery query(""
        "create table if not exists users("
            "id integer primary key autoincrement,"
            "username text not null,"
            "email text not null,"
            "password_hash text not null)"
    );
    query.exec();
}

void UserService::printUsers() {
    QSqlQuery query;
    query.exec("select id, username, email from users");
    while (query.next()) {
        QString id = query.value(0).toString();
        QString username = query.value(1).toString();
        QString email = query.value(2).toString();

        qDebug() << id << username << email;

    }

}

UserService *UserService::getInstance() {
    if (instance == nullptr)
        instance = new UserService();
    return instance;
}

UserService::~UserService() {
    db.close();
}


