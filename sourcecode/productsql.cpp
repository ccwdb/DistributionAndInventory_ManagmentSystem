#include "productsql.h"
#include<QCoreApplication>
#include<QMessageBox>
#include<QSqlQuery>
#include<qDebug>
#include<QSqlError>
productSql* productSql::ptrProductSql;
productSql* productSql::getInstance()
{
    if(nullptr==ptrProductSql){
        ptrProductSql=new productSql;
    }
    return ptrProductSql;
}

productSql::productSql()
{
    init();
}

void productSql::init()
{
    if(QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";
    product_db = QSqlDatabase::addDatabase("QSQLITE");
#if 1
    //auto str = QCoreApplication::applicationDirPath()+"/user.data";
#endif
    auto str=QString("D:/Qtfiles/ManageSystem/user.data");
    product_db.setDatabaseName(str);
    if(!product_db.open())
        qDebug()<<"Unable to open database";
    else
        qDebug()<<"open successfully";
}

quint32 productSql::getProductCnt()
{
    QSqlQuery sql(product_db);
    sql.exec("SELECT COUNT(*) FROM product");
    if (sql.next()) {
        int rowCount = sql.value(0).toInt();
        return rowCount;
    }
    else return 0;
}

bool productSql::addProduct(ProductInfo info)
{
    QSqlQuery sql(product_db);
    QString strSql = QString("insert into product values('%1','%2','%3',%4,%5)").
                     arg(info.id).
                     arg(info.name).
                     arg(info.manufacturer).
                     arg(info.price).
                     arg(info.quantity);
    return sql.exec(strSql);
}

bool productSql::delProduct(QString id)
{
    QSqlQuery sql(product_db);
    return sql.exec(QString("delete from product where id = '%1'").arg(id));
}

bool productSql::updateProductInfo(ProductInfo info)
{
    QSqlQuery sql(product_db);
    QString strSql = QString("UPDATE product SET name='%1', manufacturer='%2', price=%3, quantity=%4 WHERE id='%5'").
                     arg(info.name).
                     arg(info.manufacturer).
                     arg(info.price).
                     arg(info.quantity).
                     arg(info.id);

    bool success = sql.exec(strSql);
    return success;
}

QList<ProductInfo> productSql::getProduct()
{
    QList<ProductInfo>l;
    QSqlQuery sql(product_db);
    QString strsql=QString("select * from product");
    sql.exec(strsql);
    ProductInfo info;
    while(sql.next()){
        info.id = sql.value(0).toString();
        info.name = sql.value(1).toString();
        info.manufacturer = sql.value(2).toString();
        info.price = sql.value(3).toReal();
        info.quantity = sql.value(4).toUInt();
        l.push_back(info);
    }
    return l;
}

quint32 productSql::getProductQuantity(QString id)
{
    QSqlQuery sql(product_db);
    QString qStr = QString("SELECT quantity FROM product WHERE id = '%1'").arg(id);
    sql.exec(qStr);
    if (sql.next())
        return sql.value(0).toUInt();
    else
        return 0;
}

bool productSql::isExit(QString strProduct)
{
    QSqlQuery sql(product_db);
    sql.exec(QString("select * from product where id = '%1'").arg(strProduct));
    return sql.next();
}

QString productSql::getNameById(QString strId)
{
    QSqlQuery sql(product_db);
    QString qStr = QString("SELECT name FROM product WHERE id = '%1'").arg(strId);
    sql.exec(qStr);
    if (sql.next())
        return sql.value(0).toString();
    else
        return "";
}

QString productSql::getManufacturerById(QString strId)
{
    QSqlQuery sql(product_db);
    QString qStr = QString("SELECT manufacturer FROM product WHERE id = '%1'").arg(strId);
    sql.exec(qStr);
    if (sql.next())
        return sql.value(0).toString();
    else
        return "";
}

qreal productSql::getPriceById(QString strId)
{
    QSqlQuery sql(product_db);
    QString qStr = QString("SELECT price FROM product WHERE id = '%1'").arg(strId);
    sql.exec(qStr);
    if (sql.next())
        return sql.value(0).toDouble();
    else
        return 0;
}


