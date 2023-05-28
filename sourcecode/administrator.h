#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include <QWidget>
#include"salesmansql.h"
#include"productsql.h"
#include"dlg_addsalesman.h"
#include"dlg_addproduct.h"
#include "salessql.h"
#include "dlg_addsales.h"
namespace Ui {
class Administrator;
}

class Administrator : public QWidget
{
    Q_OBJECT

public:
    explicit Administrator(QWidget *parent = nullptr);
    ~Administrator();
private slots:
    void on_pushButton_2_clicked();

    void on_btn_salesman_clicked();

    void on_btn_product_clicked();

    void on_btn_sales_clicked();

    void on_btn_add_clicked();

    void on_btn_delete_clicked();

    void on_btn_modify_clicked();

    void on_btn_search_clicked();

    void on_btn_product_search_clicked();

    void on_btn_product_add_clicked();

    void on_btn_product_modify_clicked();

    void on_btn_sales_search_clicked();


    void on_btn_sales_add_clicked();



    void on_btn_product_delete_clicked();

    void on_btn_filter_clicked();

    void on_btn_statistics_clicked();

private:
    Ui::Administrator *ui;
    salesmanSql* m_ptrSalesmanSql;
    productSql* m_ptrProductSql;
    salesSql* m_ptrSalesSql;
    Dlg_AddSalesman m_dlgAddSalesman;
    Dlg_AddProduct m_dlgAddProduct;
    Dlg_AddSales m_dlgAddSales;
    void updateTable();
    void updateProductTable();
    void updateSalesTable();
};

#endif // ADMINISTRATOR_H
