#include "dlg_addsales.h"
#include "ui_dlg_addsales.h"

#include <QMessageBox>
#include"productsql.h"
Dlg_AddSales::Dlg_AddSales(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_AddSales)
{
    ui->setupUi(this);
}

Dlg_AddSales::~Dlg_AddSales()
{
    delete ui;
}




void Dlg_AddSales::on_btn_save_clicked()
{
    auto ptr=salesSql::getInstance();
    auto ptrProductSql=productSql::getInstance();
    ProductInfo info;
    m_info.id=ui->le_id->text();
    info.id=m_info.id;
    quint32 quantity=ptrProductSql->getProductQuantity(info.id);
    m_info.name=ptrProductSql->getNameById(m_info.id);
    info.name=m_info.name;
    m_info.manufacturer=ptrProductSql->getManufacturerById(m_info.id);
    info.manufacturer=m_info.manufacturer;
    m_info.price=ptrProductSql->getPriceById(m_info.id);
    info.price=m_info.price;
    m_info.number=ui->le_number->text().toUInt();
    info.quantity=quantity-m_info.number;
    m_info.date=ui->le_date->text();
    if(!ptrProductSql->isExit(info.id)){
        QMessageBox::warning(nullptr,"waring!","Are you serious?You don't even have such product!");
        return;
    }
    ptr->addSales(m_info);
    ptrProductSql->updateProductInfo(info);
    QMessageBox::information(nullptr,"message","add successfully!");

}


void Dlg_AddSales::on_btn_cancel_clicked()
{
    this->hide();
}

