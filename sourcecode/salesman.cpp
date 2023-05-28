#include "salesman.h"
#include "ui_salesman.h"

#include <QMessageBox>

Salesman::Salesman(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Salesman)
{
    ui->setupUi(this);
    m_ptrProductSql=productSql::getInstance();
    updateProductTable();
    m_ptrSalesSql=salesSql::getInstance();
    updateSalesTable();
}

Salesman::~Salesman()
{
    delete ui;
}

void Salesman::on_btn_exit_clicked()
{
    exit(0);
}


void Salesman::on_btn_product_clicked()
{
    ui->salesman_stackedWidget->setCurrentIndex(0);
}


void Salesman::on_btn_sales_clicked()
{
    ui->salesman_stackedWidget->setCurrentIndex(1);
}


void Salesman::on_btn_product_search_clicked()
{
    ui->tbwid_product_2->clear();
    QStringList l;
    ui->tbwid_product_2->setColumnCount(5);
    l<<"Id"<<"Name"<<"Manufacturer"<<"Price"<<"Quantity";
    ui->tbwid_product_2->setHorizontalHeaderLabels(l);
    ui->tbwid_product_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_product_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrProductSql->getProductCnt();
    QList<ProductInfo>lProduct=m_ptrProductSql->getProduct();
    ui->tbwid_product_2->setRowCount(cnt);
    int index=0;
    QString strFilter=ui->le_product->text();
    for(int i=0;i<lProduct.size();i++){
        if(!lProduct[i].name.contains(strFilter)&&!(strFilter==lProduct[i].name+lProduct[i].manufacturer)) continue;
        ui->tbwid_product_2->setItem(index,0,new QTableWidgetItem(lProduct[i].id));
        ui->tbwid_product_2->setItem(index,1,new QTableWidgetItem(lProduct[i].name));
        ui->tbwid_product_2->setItem(index,2,new QTableWidgetItem(lProduct[i].manufacturer));
        ui->tbwid_product_2->setItem(index,3,new QTableWidgetItem(QString::number(lProduct[i].price)));
        ui->tbwid_product_2->setItem(index,4,new QTableWidgetItem(QString::number(lProduct[i].quantity)));
        index++;
    }
}

void Salesman::updateProductTable()
{
    ui->tbwid_product_2->clear();
    QStringList l;
    ui->tbwid_product_2->setColumnCount(5);
    l<<"Id"<<"Name"<<"Manufacturer"<<"Price"<<"Quantity";
    ui->tbwid_product_2->setHorizontalHeaderLabels(l);
    ui->tbwid_product_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_product_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrProductSql->getProductCnt();
    QList<ProductInfo>lProduct=m_ptrProductSql->getProduct();
    ui->tbwid_product_2->setRowCount(cnt);
    for(int i=0;i<lProduct.size();i++){
        ui->tbwid_product_2->setItem(i,0,new QTableWidgetItem(lProduct[i].id));
        ui->tbwid_product_2->setItem(i,1,new QTableWidgetItem(lProduct[i].name));
        ui->tbwid_product_2->setItem(i,2,new QTableWidgetItem(lProduct[i].manufacturer));
        ui->tbwid_product_2->setItem(i,3,new QTableWidgetItem(QString::number(lProduct[i].price)));
        ui->tbwid_product_2->setItem(i,4,new QTableWidgetItem(QString::number(lProduct[i].quantity)));
    }
}

void Salesman::updateSalesTable()
{
    ui->tbwid_sales_2->clear();
    QStringList l;
    ui->tbwid_sales_2->setColumnCount(6);
    l<<"Id"<<"Name"<<"Manufacturer"<<"price"<<"number"<<"date";
    ui->tbwid_sales_2->setHorizontalHeaderLabels(l);
    ui->tbwid_sales_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_sales_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrSalesSql->getSalesCnt();
    QList<SalesInfo>lSales=m_ptrSalesSql->getAllSales();
    ui->tbwid_sales_2->setRowCount(cnt);
    for(int i=0;i<lSales.size();i++){
        ui->tbwid_sales_2->setItem(i,0,new QTableWidgetItem(lSales[i].id));
        ui->tbwid_sales_2->setItem(i,1,new QTableWidgetItem(lSales[i].name));
        ui->tbwid_sales_2->setItem(i,2,new QTableWidgetItem(lSales[i].manufacturer));
        ui->tbwid_sales_2->setItem(i,3,new QTableWidgetItem(QString::number(lSales[i].price)));
        ui->tbwid_sales_2->setItem(i,4,new QTableWidgetItem(QString::number(lSales[i].number)));
        ui->tbwid_sales_2->setItem(i,5,new QTableWidgetItem(lSales[i].date));
    }
}


void Salesman::on_btn_product_add_clicked()
{
    m_dlgAddProduct.setType(true);
    m_dlgAddProduct.exec();
    updateProductTable();
}


void Salesman::on_btn_product_modify_clicked()
{
    ProductInfo info;
    int i=ui->tbwid_product_2->currentRow();
    if(i>=0){
        info.id=ui->tbwid_product_2->item(i,0)->text();
        info.name=ui->tbwid_product_2->item(i,1)->text();
        info.manufacturer=ui->tbwid_product_2->item(i,2)->text();
        info.price=ui->tbwid_product_2->item(i,3)->text().toDouble();
        info.quantity=ui->tbwid_product_2->item(i,4)->text().toUInt();
        m_dlgAddProduct.setType(false,info);
        m_dlgAddProduct.exec();
        updateProductTable();
    }
}


void Salesman::on_btn_product_delete_clicked()
{
    int i=ui->tbwid_product_2->currentRow();
    if(i>=0){
        QString id=ui->tbwid_product_2->item(i,0)->text();
        m_ptrProductSql->delProduct(id);
        updateProductTable();
        QMessageBox::information(nullptr,"message","Delete successfully");
    }
}


void Salesman::on_btn_sales_search_clicked()
{
    ui->tbwid_sales_2->clear();
    QStringList l;
    ui->tbwid_sales_2->setColumnCount(6);
    l<<"Id"<<"Name"<<"Manufacturer"<<"Price"<<"Number"<<"Date";
    ui->tbwid_sales_2->setHorizontalHeaderLabels(l);
    ui->tbwid_sales_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_sales_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrSalesSql->getSalesCnt();
    QList<SalesInfo>lSales=m_ptrSalesSql->getAllSales();
    ui->tbwid_sales_2->setRowCount(cnt);
    int index=0;
    QString strFilter=ui->le_sales->text();

    for(int i=0;i<lSales.size();i++){
        if(!lSales[i].id.contains(strFilter)&&!(lSales[i].date==strFilter)) continue;
        ui->tbwid_sales_2->setItem(index,0,new QTableWidgetItem(lSales[i].id));
        ui->tbwid_sales_2->setItem(index,1,new QTableWidgetItem(lSales[i].name));
        ui->tbwid_sales_2->setItem(index,2,new QTableWidgetItem(lSales[i].manufacturer));
        ui->tbwid_sales_2->setItem(index,3,new QTableWidgetItem(QString::number(lSales[i].price)));
        ui->tbwid_sales_2->setItem(index,4,new QTableWidgetItem(QString::number(lSales[i].number)));
        ui->tbwid_sales_2->setItem(index,5,new QTableWidgetItem(lSales[i].date));
        index++;
    }
}


void Salesman::on_btn_sales_add_clicked()
{
    m_dlgAddSales.exec();
    updateSalesTable();
    updateProductTable();
}

