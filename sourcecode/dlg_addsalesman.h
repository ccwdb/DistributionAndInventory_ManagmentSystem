#ifndef DLG_ADDSALESMAN_H
#define DLG_ADDSALESMAN_H

#include "salesmansql.h"

#include <QDialog>

namespace Ui {
class Dlg_AddSalesman;
}

class Dlg_AddSalesman : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_AddSalesman(QWidget *parent = nullptr);
    ~Dlg_AddSalesman();
    void setType(bool isAdd,SalesmanInfo info={});
private slots:
    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::Dlg_AddSalesman *ui;
    bool m_isAdd;
    int m_id;
    SalesmanInfo m_info;
};

#endif // DLG_ADDSALESMAN_H
