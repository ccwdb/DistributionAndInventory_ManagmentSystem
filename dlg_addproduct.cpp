#include "dlg_addproduct.h"
#include "ui_dlg_addproduct.h"
#include"productsql.h"
#include<QMessageBox>
#include<QFile>
#include<QFileDialog>
Dlg_AddProduct::Dlg_AddProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_AddProduct)
{
    ui->setupUi(this);
}

Dlg_AddProduct::~Dlg_AddProduct()
{
    delete ui;
}

void Dlg_AddProduct::setType(bool isAdd, ProductInfo info)
{
    m_isAdd=isAdd;
    m_info=info;
    ui->le_id->setText(info.id);
    ui->le_name->setText(info.name);
    ui->le_manufacturer->setText(info.manufacturer);
    ui->le_price->setText(QString::number(info.price));
    ui->le_quantity->setText(QString::number(info.quantity));
}

void Dlg_AddProduct::on_btn_product_cancel_clicked()
{
    this->hide();
}


void Dlg_AddProduct::on_btn_product_save_clicked()
{
    ProductInfo info;
    auto ptr=productSql::getInstance();
    m_info.id=ui->le_id->text();
    m_info.name=ui->le_name->text();
    m_info.manufacturer=ui->le_manufacturer->text();
    m_info.price=ui->le_price->text().toDouble();
    m_info.quantity=ui->le_quantity->text().toUInt();
    if(m_isAdd){
        if(ptr->isExit(m_info.id)){
            QMessageBox::warning(nullptr,"warning","The product has already exit!");
        }
        else{
            ptr->addProduct(m_info);
            QMessageBox::information(nullptr,"message","Add successfully");
        }
    }
    else{
        ptr->updateProductInfo(m_info);
        QMessageBox::information(nullptr,"message","Modify successfully");
    }
}




void Dlg_AddProduct::on_btn_batch_clicked()
{
    auto ptr=productSql::getInstance();
    QString path=QFileDialog::getOpenFileName(this,"Open File","");
    if (path.isEmpty()){
        return;
    }
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line=in.readLine();
    ProductInfo info;
    while(!in.atEnd()){
        line=in.readLine();
        QStringList dataList=line.split(" ");
        info.id=dataList[0];
        info.name=dataList[1];
        info.manufacturer=dataList[2];
        info.price=dataList[3].toDouble();
        info.quantity=dataList[4].toUInt();
        ptr->addProduct(info);
    }
    QMessageBox::information(nullptr,"information","Add successfully");
}

