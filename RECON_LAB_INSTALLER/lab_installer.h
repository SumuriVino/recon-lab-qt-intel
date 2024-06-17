#ifndef LAB_INSTALLER_H
#define LAB_INSTALLER_H

#include <QFrame>
#include <QtCore>
#include <QFileDialog>
#include "license_replace_dialog.h"
#include "zipper/JlCompress.h"
#include "recon_generic_functions/recon_helper_process.h"

namespace Ui {
class lab_installer;
}

class lab_installer : public QFrame
{
    Q_OBJECT

public:
    explicit lab_installer(QWidget *parent = nullptr);
    ~lab_installer();

signals:

private slots:
    void on_pushButton_install_clicked();

    void slot_proc_finished(int);
    void on_pushButton_clean_install_clicked();

    void on_pushButton_uninstall_clicked();

    void slot_license_replace_dialog_okay_clicked(bool bool_lic_rep_status, bool bool_lic_dialog_close_status);

private:
    Ui::lab_installer *ui;

    QProcess *proc;

    bool bool_proc_finished;

    void delete_previous_copy_of_recon_lab();

    void copy_new_recon_lab();

    void delete_recon_library();

    void enable_widgets(bool);

    void backup_license_file();

    void restore_license_file();

    QString license_file_backup_path;

    QString license_file_app_bundle_macos_path;

    QString license_file_recon_library_path;

    license_replace_dialog *license_replace_dialog_obj;
    QFileDialog file_dialog_obj;

    bool bool_license_replace_status;
    bool bool_license_replace_dialog_close;
    bool copy_new_license_file();

    recon_helper_process *recon_helper_process_obj;
};

#endif // LAB_INSTALLER_H
