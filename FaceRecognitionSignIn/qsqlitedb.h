
#ifndef QSQLITEDB_H
#define QSQLITEDB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef struct
{
    int id;
    QString name;
    QString time;
}w2dba;

class QSqlitedb
{
public:
    QSqlitedb();
    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    // 查询全部数据
    map<int,string> queryTable();
    // 插入数据
    void singleInsertData(string name,string time); // 插入单条数据
    void moreInsertData(QList<w2dba> &moreData); // 插入多条数据
    // 修改数据
    void modifyData(int id, QString name, QString time);
    // 删除数据
    void deleteData(int id);
    //删除数据表
    void deleteTable(QString& tableName);
    // 关闭数据库
    void closeDb(void);
private:
    QSqlDatabase database;// 用于建立和数据库的连接
};

#endif // QSQLITEDB_H
