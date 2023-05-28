#ifndef SALESMANSQL_H
#define SALESMANSQL_H
#include <QObject>
#include <QSqlDatabase>
struct SalesmanInfo{
    QString number;
    QString password;
    QString name;
    quint8 age;
    QString sex;
    QString phone;
    quint16 id;
};

class salesmanSql : public QObject
{
    Q_OBJECT
public:
    static salesmanSql* ptrSalesmanSql;
    static salesmanSql* getInstance();
    explicit salesmanSql(QObject *parent = nullptr);

    void init();

    quint32 getSalesmanCnt();

    bool addSalesman(SalesmanInfo info);

    bool delSalesman(int id);

    bool updateSalesmanInfo(SalesmanInfo info);

    QList<SalesmanInfo>getAllSalesman();

    bool isExit(QString strSalesman);
    bool isExitNumber(QString number);
    QString getPasswordByNumber(QString number);
signals:
private:
    QSqlDatabase salesman_db;
};

#endif // SALESMANSQL_H
