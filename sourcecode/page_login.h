#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include"salesman.h"
#include"administrator.h"
namespace Ui {
class Page_Login;
}

class Page_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Page_Login(QWidget *parent = nullptr);
    ~Page_Login();

private slots:
    void on_btn_exit_clicked();
    void on_btn_login_clicked();

signals:
    void sendAdminLoginSuccess();
    void sendSalesManLoginSuccess();
private:
    Ui::Page_Login *ui;
    Salesman mSalesman;
    Administrator mAdministrator;
};

#endif // PAGE_LOGIN_H
