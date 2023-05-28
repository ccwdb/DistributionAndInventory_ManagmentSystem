#include "salesmansql.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
#include<QCoreApplication>
#include<QSqlError>
salesmanSql *salesmanSql::salesmanSql::getInstance(){
    if(nullptr==ptrSalesmanSql){
        ptrSalesmanSql=new salesmanSql;
    }
    return ptrSalesmanSql;
}

salesmanSql::salesmanSql(QObject *parent)
    : QObject{parent}
{
    init();
}
salesmanSql* salesmanSql::ptrSalesmanSql=nullptr;
void salesmanSql::init()
{
    if(QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";
    salesman_db = QSqlDatabase::addDatabase("QSQLITE");
#if 1
    //auto str = QCoreApplication::applicationDirPath()+"/user.data";
#endif
    auto str=QString("D:/Qtfiles/ManageSystem/user.data");
    salesman_db.setDatabaseName(str);
    if(!salesman_db.open())
        qDebug()<<"Unable to open database";
    else
        qDebug()<<"open successfully";

}

quint32 salesmanSql::getSalesmanCnt()
{
    QSqlQuery sql(salesman_db);
    sql.exec("select count(id) from salesman;");
    quint32 uiCnt=0;
    while(sql.next()){
        uiCnt=sql.value(0).toUInt();
    }
    return uiCnt;
}



bool salesmanSql::addSalesman(SalesmanInfo info)
{
    QSqlQuery sql(salesman_db);
    QString strSql = QString("insert into salesman values(null,'%1','%2','%3',%4,'%5','%6')").
                     arg(info.number).
                     arg(info.password).
                     arg(info.name).
                     arg(info.age).
                     arg(info.sex).
                     arg(info.phone);
    return sql.exec(strSql);
}

bool salesmanSql::delSalesman(int id)
{
    QSqlQuery sql(salesman_db);
    return sql.exec(QString("delete from salesman where id = %1").arg(id));
}



bool salesmanSql::updateSalesmanInfo(SalesmanInfo info)
{
    QSqlQuery sql(salesman_db);
    QString strSql = QString("UPDATE salesman SET number = '%1',password='%2',name='%3',age=%4,sex='%5',phone='%6' WHERE id=%7").
                     arg(info.number).
                     arg(info.password).
                     arg(info.name).
                     arg(info.age).
                     arg(info.sex).
                     arg(info.phone).
                     arg(info.id);

    bool success = sql.exec(strSql);
    return success;
}

QList<SalesmanInfo> salesmanSql::getAllSalesman()
{
    QList<SalesmanInfo>l;
    QSqlQuery sql(salesman_db);
    QString strsql=QString("select * from salesman");
    sql.exec(strsql);
    SalesmanInfo info;
    while(sql.next()){
        qDebug()<<"sql.next";
        info.id=sql.value(0).toUInt();
        info.number=sql.value(1).toString();
        info.password=sql.value(2).toString();
        info.name=sql.value(3).toString();
        info.age=sql.value(4).toUInt();
        info.sex=sql.value(5).toString();
        info.phone=sql.value(6).toString();
        l.push_back(info);
    }
    return l;
}


bool salesmanSql::isExit(QString strSalesman)
{
    QSqlQuery sql(salesman_db);
    sql.exec(QString("select * from salesman where name='%1'").arg(strSalesman));
    return sql.next();
}

bool salesmanSql::isExitNumber(QString number)
{
    QSqlQuery sql(salesman_db);
    sql.exec(QString("select * from salesman where number='%1'").arg(number));
    return sql.next();
}

QString salesmanSql::getPasswordByNumber(QString number)
{
    QSqlQuery sql(salesman_db);
    QString qStr = QString("SELECT password FROM salesman WHERE number = '%1'").arg(number);
    sql.exec(qStr);
    if (sql.next())
        return sql.value(0).toString();
    else
        return "";
}





