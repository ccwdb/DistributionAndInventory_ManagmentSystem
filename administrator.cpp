#include "administrator.h"
#include "ui_administrator.h"
#include<QEvent>
#include<QFile>
#include<qDebug>
#include<QMessageBox>
#include<QInputDialog>
#include <QDate>
#include <algorithm>
Administrator::Administrator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Administrator),
    m_ptrSalesmanSql(nullptr)
{
    ui->setupUi(this);
    ui->admin_stackwidget->setCurrentIndex(0);
    m_ptrSalesmanSql=salesmanSql::getInstance(); //point to an instance of salesmanSql
    updateTable();
    m_ptrProductSql=productSql::getInstance();
    updateProductTable();
    m_ptrSalesSql=salesSql::getInstance();
    updateSalesTable();

}

Administrator::~Administrator()
{
    delete ui;
}


void Administrator::on_pushButton_2_clicked()
{
    exit(0);
}


void Administrator::on_btn_salesman_clicked()
{
    ui->admin_stackwidget->setCurrentIndex(0);
}


void Administrator::on_btn_product_clicked()
{
    ui->admin_stackwidget->setCurrentIndex(1);
}



void Administrator::on_btn_sales_clicked()
{
    ui->admin_stackwidget->setCurrentIndex(2);
}


void Administrator::on_btn_add_clicked()
{
    m_dlgAddSalesman.setType(true);
    m_dlgAddSalesman.exec();
    updateTable();
}

void Administrator::updateTable()
{
    ui->tbwid_salesman->clear();
    QStringList l;
    ui->tbwid_salesman->setColumnCount(7);
    l<<"Id"<<"Number"<<"Password"<<"Name"<<"Age"<<"Sex"<<"Phone";
    ui->tbwid_salesman->setHorizontalHeaderLabels(l);
    ui->tbwid_salesman->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_salesman->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrSalesmanSql->getSalesmanCnt();
    QList<SalesmanInfo>lSalesman=m_ptrSalesmanSql->getAllSalesman();
    ui->tbwid_salesman->setRowCount(cnt);
    qDebug()<<"lSalesman.size() == "<<lSalesman.size();
    for(int i=0;i<lSalesman.size();i++){
        ui->tbwid_salesman->setItem(i,0,new QTableWidgetItem(QString::number(lSalesman[i].id)));
        ui->tbwid_salesman->setItem(i,1,new QTableWidgetItem(lSalesman[i].number));
        ui->tbwid_salesman->setItem(i,2,new QTableWidgetItem(lSalesman[i].password));
        ui->tbwid_salesman->setItem(i,3,new QTableWidgetItem(lSalesman[i].name));
        ui->tbwid_salesman->setItem(i,4,new QTableWidgetItem(QString::number(lSalesman[i].age)));
        ui->tbwid_salesman->setItem(i,5,new QTableWidgetItem(lSalesman[i].sex));
        ui->tbwid_salesman->setItem(i,6,new QTableWidgetItem(lSalesman[i].phone));
    }
}

void Administrator::updateProductTable()
{
    ui->tbwid_product->clear();
    QStringList l;
    ui->tbwid_product->setColumnCount(5);
    l<<"Id"<<"Name"<<"Manufacturer"<<"Price"<<"Quantity";
    ui->tbwid_product->setHorizontalHeaderLabels(l);
    ui->tbwid_product->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_product->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrProductSql->getProductCnt();
    QList<ProductInfo>lProduct=m_ptrProductSql->getProduct();
    ui->tbwid_product->setRowCount(cnt);
    for (int i = 0; i < lProduct.size(); i++) {
        ui->tbwid_product->setItem(i, 0, new QTableWidgetItem(lProduct[i].id));
        ui->tbwid_product->setItem(i, 1, new QTableWidgetItem(lProduct[i].name));
        ui->tbwid_product->setItem(i, 2, new QTableWidgetItem(lProduct[i].manufacturer));
        ui->tbwid_product->setItem(i, 3, new QTableWidgetItem(QString::number(lProduct[i].price)));
        ui->tbwid_product->setItem(i, 4, new QTableWidgetItem(QString::number(lProduct[i].quantity)));
    }
}

void Administrator::updateSalesTable()
{
    ui->tbwid_sales->clear();
    QStringList l;
    ui->tbwid_sales->setColumnCount(6);
    l<<"Id"<<"Name"<<"Manufacturer"<<"price"<<"number"<<"date";
    ui->tbwid_sales->setHorizontalHeaderLabels(l);
    ui->tbwid_sales->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_sales->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrSalesSql->getSalesCnt();
    QList<SalesInfo>lSales=m_ptrSalesSql->getAllSales();
    ui->tbwid_sales->setRowCount(cnt);
    for(int i=0;i<lSales.size();i++){
        ui->tbwid_sales->setItem(i,0,new QTableWidgetItem(lSales[i].id));
        ui->tbwid_sales->setItem(i,1,new QTableWidgetItem(lSales[i].name));
        ui->tbwid_sales->setItem(i,2,new QTableWidgetItem(lSales[i].manufacturer));
        ui->tbwid_sales->setItem(i,3,new QTableWidgetItem(QString::number(lSales[i].price)));
        ui->tbwid_sales->setItem(i,4,new QTableWidgetItem(QString::number(lSales[i].number)));
        ui->tbwid_sales->setItem(i,5,new QTableWidgetItem(lSales[i].date));
    }
}


void Administrator::on_btn_delete_clicked()
{
    int i=ui->tbwid_salesman->currentRow();
    if(i>=0){
        int id=ui->tbwid_salesman->item(i,0)->text().toUInt();
        qDebug()<<"id= "<<id;
        m_ptrSalesmanSql->delSalesman(id);
        updateTable();
        QMessageBox::information(nullptr,"message","Delete successfully");
        updateTable();
    }
}


void Administrator::on_btn_modify_clicked()
{
    SalesmanInfo info;
    int i=ui->tbwid_salesman->currentRow();
    if(i>=0){
        info.id=ui->tbwid_salesman->item(i,0)->text().toUInt();
        info.number=ui->tbwid_salesman->item(i,1)->text();
        info.password=ui->tbwid_salesman->item(i,2)->text();
        info.name=ui->tbwid_salesman->item(i,3)->text();
        info.age=ui->tbwid_salesman->item(i,4)->text().toUInt();
        info.sex=ui->tbwid_salesman->item(i,5)->text();
        info.phone=ui->tbwid_salesman->item(i,6)->text();
        m_dlgAddSalesman.setType(false,info);
        m_dlgAddSalesman.exec();
        updateTable();
    }
}


void Administrator::on_btn_search_clicked()
{
    ui->tbwid_salesman->clear();
    QStringList l;
    ui->tbwid_salesman->setColumnCount(7);
    l<<"Id"<<"Number"<<"Password"<<"Name"<<"Age"<<"Sex"<<"Phone";
    ui->tbwid_salesman->setHorizontalHeaderLabels(l);
    ui->tbwid_salesman->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_salesman->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrSalesmanSql->getSalesmanCnt();
    QList<SalesmanInfo>lSalesman=m_ptrSalesmanSql->getAllSalesman();
    ui->tbwid_salesman->setRowCount(cnt);

    QString strFilter = ui->le_search->text();

    int index=0;
    for(int i=0;i<lSalesman.size();i++){
        if(!lSalesman[i].name.contains(strFilter)) continue;
        ui->tbwid_salesman->setItem(index,0,new QTableWidgetItem(QString::number(lSalesman[i].id)));
        ui->tbwid_salesman->setItem(index,1,new QTableWidgetItem(lSalesman[i].number));
        ui->tbwid_salesman->setItem(index,2,new QTableWidgetItem(lSalesman[i].password));
        ui->tbwid_salesman->setItem(index,3,new QTableWidgetItem(lSalesman[i].name));
        ui->tbwid_salesman->setItem(index,4,new QTableWidgetItem(QString::number(lSalesman[i].age)));
        ui->tbwid_salesman->setItem(index,5,new QTableWidgetItem(lSalesman[i].sex));
        ui->tbwid_salesman->setItem(index,6,new QTableWidgetItem(lSalesman[i].phone));
        index++;
    }
}


void Administrator::on_btn_product_search_clicked()
{
    ui->tbwid_product->clear();
    QStringList l;
    ui->tbwid_product->setColumnCount(5);
    l<<"Id"<<"Name"<<"Manufacturer"<<"Price"<<"Quantity";
    ui->tbwid_product->setHorizontalHeaderLabels(l);
    ui->tbwid_product->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_product->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrProductSql->getProductCnt();
    QList<ProductInfo>lProduct=m_ptrProductSql->getProduct();
    ui->tbwid_product->setRowCount(cnt);
    int index=0;
    QString strFilter=ui->le_product->text();
    for(int i=0;i<lProduct.size();i++){
        if(!lProduct[i].name.contains(strFilter)&&!(strFilter==lProduct[i].name+"+"+lProduct[i].manufacturer)&&!lProduct[i].id.contains(strFilter)) continue;
        ui->tbwid_product->setItem(index,0,new QTableWidgetItem(lProduct[i].id));
        ui->tbwid_product->setItem(index,1,new QTableWidgetItem(lProduct[i].name));
        ui->tbwid_product->setItem(index,2,new QTableWidgetItem(lProduct[i].manufacturer));
        ui->tbwid_product->setItem(index,3,new QTableWidgetItem(QString::number(lProduct[i].price)));
        ui->tbwid_product->setItem(index,4,new QTableWidgetItem(QString::number(lProduct[i].quantity)));
        index++;
    }
}


void Administrator::on_btn_product_add_clicked()
{

    m_dlgAddProduct.setType(true);
    m_dlgAddProduct.exec();
    updateProductTable();
}


void Administrator::on_btn_product_modify_clicked()
{
    ProductInfo info;
    int i=ui->tbwid_product->currentRow();
    if(i>=0){
        info.id=ui->tbwid_product->item(i,0)->text();
        info.name=ui->tbwid_product->item(i,1)->text();
        info.manufacturer=ui->tbwid_product->item(i,2)->text();
        info.price=ui->tbwid_product->item(i,3)->text().toDouble();
        info.quantity=ui->tbwid_product->item(i,4)->text().toUInt();
        m_dlgAddProduct.setType(false,info);
        m_dlgAddProduct.exec();
        updateProductTable();
    }
}


void Administrator::on_btn_sales_search_clicked()
{
    ui->tbwid_sales->clear();
    QStringList l;
    ui->tbwid_sales->setColumnCount(6);
    l<<"Id"<<"Name"<<"Manufacturer"<<"Price"<<"Number"<<"Date";
    ui->tbwid_sales->setHorizontalHeaderLabels(l);
    ui->tbwid_sales->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_sales->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto cnt=m_ptrSalesSql->getSalesCnt();
    QList<SalesInfo>lSales=m_ptrSalesSql->getAllSales();
    ui->tbwid_sales->setRowCount(cnt);
    int index=0;
    QString strFilter=ui->le_sales->text();
    for(int i=0;i<lSales.size();i++){
        if(!lSales[i].name.contains(strFilter)&&!(lSales[i].date==strFilter)&&!lSales[i].id.contains(strFilter)) continue;
        ui->tbwid_sales->setItem(index,0,new QTableWidgetItem(lSales[i].id));
        ui->tbwid_sales->setItem(index,1,new QTableWidgetItem(lSales[i].name));
        ui->tbwid_sales->setItem(index,2,new QTableWidgetItem(lSales[i].manufacturer));
        ui->tbwid_sales->setItem(index,3,new QTableWidgetItem(QString::number(lSales[i].price)));
        ui->tbwid_sales->setItem(index,4,new QTableWidgetItem(QString::number(lSales[i].number)));
        ui->tbwid_sales->setItem(index,5,new QTableWidgetItem(lSales[i].date));
        index++;
    }
}

void Administrator::on_btn_sales_add_clicked()
{
    m_dlgAddSales.exec();
    updateSalesTable();
    updateProductTable();
}

void Administrator::on_btn_product_delete_clicked()
{
    int i=ui->tbwid_product->currentRow();
    if(i>=0){
        QString id=ui->tbwid_product->item(i,0)->text();
        m_ptrProductSql->delProduct(id);
        updateProductTable();
        QMessageBox::information(nullptr,"message","Delete successfully");
    }
}


void Administrator::on_btn_filter_clicked()
{
    ui->tbwid_sales->clear();
    QDate beginDate=ui->de_begin->date();
    QDate endDate=ui->de_end->date();
    auto ptr=salesSql::getInstance();
    QList<SalesInfo>lSales=ptr->filterSalesByDate(beginDate.toString("yyyy-MM-dd"),endDate.toString("yyyy-MM-dd"));

    QStringList l;
    ui->tbwid_sales->setColumnCount(6);
    l<<"Id"<<"Name"<<"Manufacturer"<<"Price"<<"Number"<<"Date";
    ui->tbwid_sales->setHorizontalHeaderLabels(l);
    ui->tbwid_sales->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_sales->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tbwid_sales->setRowCount(lSales.size());
    int index=0;
    for(int i=0;i<lSales.size();i++){
        ui->tbwid_sales->setItem(index,0,new QTableWidgetItem(lSales[i].id));
        ui->tbwid_sales->setItem(index,1,new QTableWidgetItem(lSales[i].name));
        ui->tbwid_sales->setItem(index,2,new QTableWidgetItem(lSales[i].manufacturer));
        ui->tbwid_sales->setItem(index,3,new QTableWidgetItem(QString::number(lSales[i].price)));
        ui->tbwid_sales->setItem(index,4,new QTableWidgetItem(QString::number(lSales[i].number)));
        ui->tbwid_sales->setItem(index,5,new QTableWidgetItem(lSales[i].date));
        index++;
    }
}

bool compareById(const SalesInfo &a, const SalesInfo &b) {
    return a.id < b.id;
}
bool compareByIncome(const SalesInfo &a, const SalesInfo &b) {
    return a.price > b.price;
}

void Administrator::on_btn_statistics_clicked()
{
    ui->tbwid_sales->clear();
    QDate beginDate=ui->de_begin->date();
    QDate endDate=ui->de_end->date();
    auto ptr=salesSql::getInstance();
    QList<SalesInfo>lSales=ptr->filterSalesByDate(beginDate.toString("yyyy-MM-dd"),endDate.toString("yyyy-MM-dd"));

    std::sort(lSales.begin(),lSales.end(),compareById);
    int begin=0;
    int mSize=lSales.size();
    lSales[0].price*=lSales[0].number;

    for(int i=1;i<mSize;i++){
        if(lSales[i].id!=lSales[begin].id){
            begin=i;
            lSales[begin].price*=lSales[begin].number;
        }
        else{
            lSales[begin].price+=lSales[i].price*lSales[i].number;
            lSales[begin].number+=lSales[i].number;
            lSales.removeAt(i);
            --i;
            --mSize;

        }
    }
    qDebug()<<lSales.size();
    std::sort(lSales.begin(),lSales.end(),compareByIncome);

    QStringList l;
    ui->tbwid_sales->setColumnCount(5);
    l<<"Id"<<"Name"<<"Manufacturer"<<"TotalNumber"<<"TotalIncome";
    ui->tbwid_sales->setHorizontalHeaderLabels(l);
    ui->tbwid_sales->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwid_sales->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tbwid_sales->setRowCount(lSales.size());
    int index=0;
    for(int i=0;i<lSales.size();i++){
        ui->tbwid_sales->setItem(index,0,new QTableWidgetItem(lSales[i].id));
        ui->tbwid_sales->setItem(index,1,new QTableWidgetItem(lSales[i].name));
        ui->tbwid_sales->setItem(index,2,new QTableWidgetItem(lSales[i].manufacturer));
        ui->tbwid_sales->setItem(index,3,new QTableWidgetItem(QString::number(lSales[i].number)));
        ui->tbwid_sales->setItem(index,4,new QTableWidgetItem(QString::number(lSales[i].price)));
        index++;
    }
}

