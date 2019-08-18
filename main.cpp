#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QVariantList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("CashSystem.db");

    if (database.open()){
        qDebug()<<"Database opened";

        QSqlQuery sql_query;
        /*创建数据库表 member*/
        QString create_sql = "create table member (id int primary key,name varchar(30), address varchar(30))";
        /*数据库表中插入数据*/
        QString insert_sql = "insert into member values(?,?,?)";

        /*查询数据库表中的数据*/
        QString select_all_sql = "select * from member";

        sql_query.prepare(create_sql);

        if (!sql_query.exec()){
            qDebug()<<QObject::tr("数据表创建失败");
            qDebug()<<sql_query.lastError();
        }else{
            qDebug()<<"数据库表创建成功！！！";

            /*数据库表中插入数据*/
            sql_query.prepare(insert_sql);

            QVariantList GroupIDs;
            GroupIDs.append(0);
            GroupIDs.append(1);
            GroupIDs.append(2);

            QVariantList GroupNames;
            GroupNames.append("张三");
            GroupNames.append("李四");
            GroupNames.append("王麻子");

            QVariantList GroupAddress;
            GroupAddress.append("山东");
            GroupAddress.append("济南");
            GroupAddress.append("历下区");

            sql_query.addBindValue(GroupIDs);
            sql_query.addBindValue(GroupNames);
            sql_query.addBindValue(GroupAddress);


            if (!sql_query.execBatch()){
                qDebug()<<sql_query.lastError();
            }else {
                qDebug()<<"插入数据记录成功！！！";
            }
               /*查询所有的记录*/
                sql_query.prepare(select_all_sql);
                if (!sql_query.exec()){
                    qDebug()<<sql_query.lastError();
                }else{
                    while (sql_query.next()){
                        int id = sql_query.value(0).toInt();
                        QString name = sql_query.value(1).toString();
                        QString address = sql_query.value(2).toString();
                        qDebug()<<QString("ID:%1 Name:%2 Address:%3").arg(id).arg(name).arg(address);
                    }
                }

            }
        }

        database.close();

        return a.exec();
    }
