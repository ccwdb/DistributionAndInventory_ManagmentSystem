#ifndef SALESSQL_H
#define SALESSQL_H
#include <QObject>
#include <QSqlDatabase>
struct SalesInfo
{
    QString id;
    QString name;
    QString manufacturer;
    qreal price;
    quint32 number;
    QString date;
};

class salesSql
{
public:
    static salesSql* ptrSalesSql;
    static salesSql* getInstance();
    salesSql();

    void init();

    quint32 getSalesCnt();

    bool addSales(SalesInfo info);

    bool delSales(QString id);

    bool updateSales(SalesInfo info);

    QList<SalesInfo>getAllSales();

    bool isExit(QString strSales);
    QList<SalesInfo> filterSalesByDate(QString beginDate,QString endDate);
private:
    QSqlDatabase sales_db;
};

#endif // SALESSQL_H
