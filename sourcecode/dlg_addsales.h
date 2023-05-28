#ifndef DLG_ADDSALES_H
#define DLG_ADDSALES_H

#include "salessql.h"

#include <QDialog>
namespace Ui {
class Dlg_AddSales;
}

class Dlg_AddSales : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_AddSales(QWidget *parent = nullptr);
    ~Dlg_AddSales();
private slots:
    void on_btn_save_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::Dlg_AddSales *ui;
    SalesInfo m_info;
};

#endif // DLG_ADDSALES_H
