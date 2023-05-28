#ifndef DLG_ADDPRODUCT_H
#define DLG_ADDPRODUCT_H

#include "productsql.h"

#include <QDialog>

namespace Ui {
class Dlg_AddProduct;
}

class Dlg_AddProduct : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_AddProduct(QWidget *parent = nullptr);
    ~Dlg_AddProduct();
    void setType(bool isAdd, ProductInfo={});
private slots:
    void on_btn_product_cancel_clicked();

    void on_btn_product_save_clicked();


    void on_btn_batch_clicked();

private:
    Ui::Dlg_AddProduct *ui;
    bool m_isAdd;
    ProductInfo m_info;
};

#endif // DLG_ADDPRODUCT_H
