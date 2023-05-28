#include "page_login.h"
#include "ui_page_login.h"

#include <QMessageBox>
Page_Login::Page_Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_Login)
{
    ui->setupUi(this);
    auto f=[&](){
        mAdministrator.show();
    };
    connect(this,&Page_Login::sendAdminLoginSuccess,&mAdministrator,f);

    auto g=[&](){
        mSalesman.show();
    };
    connect(this,&Page_Login::sendSalesManLoginSuccess,&mSalesman,g);
}

Page_Login::~Page_Login()
{
    delete ui;
}


void Page_Login::on_btn_exit_clicked()
{
    //exit
    exit(0);
}


void Page_Login::on_btn_login_clicked()
{
    QString id=ui->le_id->text();
    QString password=ui->le_password->text();
    if(ui->isAdmin->isChecked()){
        if(id=="admin"&&password=="admin")
            emit sendAdminLoginSuccess();
        else
            QMessageBox::information(nullptr,"Infomation","Id or Password Incorrect!");
    }
    else{
        auto ptr=salesmanSql::getInstance();
        QString password=ui->le_password->text();
        if(ptr->isExitNumber(id)&&ptr->getPasswordByNumber(id)==password)
            emit sendSalesManLoginSuccess();
        else
            QMessageBox::information(nullptr,"Infomation","Id or Password Incorrect!");
    }

}

