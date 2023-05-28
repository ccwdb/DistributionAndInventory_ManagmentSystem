#ifndef SALESMAN_H
#define SALESMAN_H

#include <QWidget>
#include"productsql.h"
#include"dlg_addproduct.h"
#include "salessql.h"
#include "dlg_addsales.h"
namespace Ui {
class Salesman;
}

class Salesman : public QWidget
{
    Q_OBJECT

public:
    explicit Salesman(QWidget *parent = nullptr);
    ~Salesman();

private slots:
    void on_btn_exit_clicked();

    void on_btn_product_clicked();

    void on_btn_sales_clicked();

    void on_btn_product_search_clicked();

    void on_btn_product_add_clicked();

    void on_btn_product_modify_clicked();

    void on_btn_product_delete_clicked();

    void on_btn_sales_search_clicked();

    void on_btn_sales_add_clicked();

private:
    Ui::Salesman *ui;
    productSql* m_ptrProductSql;
    salesSql* m_ptrSalesSql;
    Dlg_AddProduct m_dlgAddProduct;
    Dlg_AddSales m_dlgAddSales;
    void updateProductTable();
    void updateSalesTable();
};

#endif // SALESMAN_H
