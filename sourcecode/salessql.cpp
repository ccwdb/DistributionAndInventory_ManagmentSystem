#include "salessql.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include<qDebug>
salesSql::salesSql()
{
    init();
}

void salesSql::init()
{
    if(QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";
    sales_db = QSqlDatabase::addDatabase("QSQLITE");
#if 0
    auto str = QCoreApplication::applicationDirPath()+"/user.data";
#endif
    auto str=QString("D:/Qtfiles/ManageSystem/user.data");
    sales_db.setDatabaseName(str);
    if(!sales_db.open())
        qDebug()<<"Unable to open database";
    else
        qDebug()<<"open successfully";
}

quint32 salesSql::getSalesCnt()
{
    QSqlQuery sql(sales_db);
    sql.exec("SELECT COUNT(*) FROM sales");
    if (sql.next()) {
        int rowCount = sql.value(0).toInt();
        return rowCount;
    }
    else return 0;
}

bool salesSql::addSales(SalesInfo info)
{
    QSqlQuery sql(sales_db);
    QString strSql = QString("insert into sales values('%1','%2','%3',%4,%5,'%6')").
                     arg(info.id).
                     arg(info.name).
                     arg(info.manufacturer).
                     arg(info.price).
                     arg(info.number).
                     arg(info.date);
    bool success = sql.exec(strSql);
    return success;
}

bool salesSql::delSales(QString id)
{
    QSqlQuery sql(sales_db);
    bool success=sql.exec(QString("delete from sales where id = '%1'").arg(id));
    return success;
}

bool salesSql::updateSales(SalesInfo info)
{
    QSqlQuery sql(sales_db);
    QString strSql = QString("UPDATE sales SET name='%1',manufacturer='%2',price=%3,number=%4,date='%5' WHERE id='%6'").
                     arg(info.name).
                     arg(info.manufacturer).
                     arg(info.price).
                     arg(info.number).
                     arg(info.date).
                     arg(info.id);

    bool success = sql.exec(strSql);
    return success;
}

QList<SalesInfo> salesSql::getAllSales()
{
    QList<SalesInfo>l;
    QSqlQuery sql(sales_db);
    QString strsql=QString("select * from sales");
    sql.exec(strsql);
    SalesInfo info;
    while(sql.next()){
        qDebug()<<"sql.next";
        info.id=sql.value(0).toString();
        info.name=sql.value(1).toString();
        info.manufacturer=sql.value(2).toString();
        info.price=sql.value(3).toReal();
        info.number=sql.value(4).toUInt();
        info.date=sql.value(5).toString();
        l.push_back(info);
    }
    return l;
}

bool salesSql::isExit(QString strSales)
{
    QSqlQuery sql(sales_db);
    sql.exec(QString("select * from sales where id = '%1'").arg(strSales));
    return sql.next();
}



QList<SalesInfo> salesSql::filterSalesByDate(QString beginDate,QString endDate)
{
    QSqlQuery sql(sales_db);
    QString query = QString("select * FROM sales where date between '%1' and '%2'")
                        .arg(beginDate)
                        .arg(endDate);
    sql.exec(query);
    QList<SalesInfo>salesInfo;
    SalesInfo info;
    while (sql.next())
    {
        info.id=sql.value(0).toString();
        info.name=sql.value(1).toString();
        info.manufacturer=sql.value(2).toString();
        info.price=sql.value(3).toDouble();
        info.number=sql.value(4).toUInt();
        info.date=sql.value(5).toString();
        salesInfo.push_back(info);
    }
    return salesInfo;
}

salesSql* salesSql::ptrSalesSql;
salesSql* salesSql::getInstance(){
    if(nullptr==ptrSalesSql){
        ptrSalesSql=new salesSql;
    }
    return ptrSalesSql;
}
