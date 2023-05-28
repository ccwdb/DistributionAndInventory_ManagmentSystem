#include "dlg_addsalesman.h"
#include "ui_dlg_addsalesman.h"
#include"salesmansql.h"
#include<QMessageBox>
Dlg_AddSalesman::Dlg_AddSalesman(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_AddSalesman)
{
    ui->setupUi(this);
}

Dlg_AddSalesman::~Dlg_AddSalesman()
{
    delete ui;
}

void Dlg_AddSalesman::setType(bool isAdd, SalesmanInfo info)
{
    m_isAdd=isAdd;
    m_info=info;
    ui->le_number->setText(info.number);
    ui->le_password->setText(info.password);
    ui->le_name->setText(info.name);
    ui->sb_age->setValue(info.age);
    ui->le_sex->setText(info.sex);
    ui->le_phone->setText(info.phone);
}

void Dlg_AddSalesman::on_btn_save_clicked()
{
    auto ptr=salesmanSql::getInstance();
    m_info.number=ui->le_number->text();
    m_info.password=ui->le_password->text();
    m_info.name=ui->le_name->text();
    m_info.age=ui->sb_age->text().toUInt();
    m_info.sex=ui->le_sex->text();
    m_info.phone=ui->le_phone->text();
    if(m_isAdd){
        ptr->addSalesman(m_info);
        QMessageBox::information(nullptr,"message","add successfully!");
    }
    else{
        ptr->updateSalesmanInfo(m_info);
        QMessageBox::information(nullptr,"message","modify successfully!");
    }
}


void Dlg_AddSalesman::on_btn_cancel_clicked()
{
    this->hide();
}

