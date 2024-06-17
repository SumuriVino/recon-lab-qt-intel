#ifndef PACKAGE_SHIFTER_H
#define PACKAGE_SHIFTER_H

#include <QWidget>

#include <QtCore>

#include "recon_generic_functions/recon_helper_process.h"
#include "recon_generic_functions/recon_helper_standard.h"


namespace Ui {
class package_shifter;
}

class package_shifter : public QWidget
{
    Q_OBJECT

public:
    explicit package_shifter(QWidget *parent = nullptr);
    ~package_shifter();

    void pub_update_module_files(QString password);

    void closeEvent(QCloseEvent *event);

signals:
    void signal_shifter_workdone(int m_status);

private:
    Ui::package_shifter *ui;

    recon_helper_process *recon_helper_process_obj;

    QString system_password;

    void skin_tone_detection();

    recon_helper_standard *recon_helper_standard_obj;

    bool bool_close_window = false;
};

#endif // PACKAGE_SHIFTER_H
