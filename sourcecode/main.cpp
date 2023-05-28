#include"page_login.h"
#include<qDebug>
#include <QApplication>
#include"salesmansql.h"
#include"productsql.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Page_Login mLogin;
    mLogin.show();
    return a.exec();
}
