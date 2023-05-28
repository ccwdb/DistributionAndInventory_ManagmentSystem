#ifndef PRODUCTSQL_H
#define PRODUCTSQL_H
#include <QObject>
#include <QSqlDatabase>

struct ProductInfo{
    QString id;
    QString name;
    QString manufacturer;
    qreal price;
    quint16 quantity;
};

class productSql
{
public:
    static productSql* ptrProductSql;
    static productSql* getInstance();
    productSql();

    void init();

    quint32 getProductCnt();

    bool addProduct(ProductInfo info);

    bool delProduct(QString id);

    bool updateProductInfo(ProductInfo info);

    QList<ProductInfo>getProduct();

    quint32 getProductQuantity(QString id);
    QString getNameById(QString strId);
    QString getManufacturerById(QString strId);
    qreal getPriceById(QString strId);
    bool isExit(QString strProduct);
private:
    QSqlDatabase product_db;
};

#endif // PRODUCTSQL_H
