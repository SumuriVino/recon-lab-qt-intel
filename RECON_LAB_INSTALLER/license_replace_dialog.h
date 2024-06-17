#ifndef LICENSE_REPLACE_DIALOG_H
#define LICENSE_REPLACE_DIALOG_H

#include <QDialog>
#include <QtCore>

namespace Ui {
class license_replace_dialog;
}

class license_replace_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit license_replace_dialog(QWidget *parent = nullptr);
    ~license_replace_dialog();

    void pub_set_window_title(QString title_str);
    void closeEvent(QCloseEvent *event);
signals:
    void signal_license_replace_dialog_okay_clicked(bool lic_rep_status, bool dialog_close_status);

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::license_replace_dialog *ui;
};

#endif // LICENSE_REPLACE_DIALOG_H
