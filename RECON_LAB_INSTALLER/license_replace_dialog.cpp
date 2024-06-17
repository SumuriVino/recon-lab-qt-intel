#include "license_replace_dialog.h"
#include "ui_license_replace_dialog.h"

license_replace_dialog::license_replace_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::license_replace_dialog)
{
    ui->setupUi(this);
}

license_replace_dialog::~license_replace_dialog()
{
    delete ui;
}

void license_replace_dialog::closeEvent(QCloseEvent *event)
{
    on_pushButton_ok_clicked();
}

void license_replace_dialog::pub_set_window_title(QString title_str)
{
    setWindowTitle(title_str);
}

void license_replace_dialog::on_pushButton_ok_clicked()
{
    hide();
    emit signal_license_replace_dialog_okay_clicked(ui->checkBox_replace_license->isChecked(), true);
}
