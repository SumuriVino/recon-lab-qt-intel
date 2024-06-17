#ifndef PACKAGE_INSTALLER_H
#define PACKAGE_INSTALLER_H

#include <QWidget>
#include <QtCore>
#include <QProcess>
#include "network_time/network_time.h"
#include "recon_generic_functions/recon_static_functions.h"
#include "recon_generic_functions/recon_helper_process.h"
#include "requirement_window/requirement_window.h"

namespace Ui {
class package_installer;
}

class package_installer : public QWidget
{
    Q_OBJECT

public:
    explicit package_installer(QWidget *parent = nullptr);
    ~package_installer();

    void closeEvent(QCloseEvent *event);

    void pub_check_package_status();
    void pub_set_requirement_window_obj(requirement_window *requirement_window_object);

signals:
    void signal_installation_workdone(int m_status);

private slots:
    void on_pushButton_install_clicked();
    void on_pushButton_skip_clicked();

private:
    Ui::package_installer *ui;

    bool check_intial_packages_status();
    bool check_python_packages_installation_required();

    QStringList non_installed_package_command_list;

    bool bool_window_close = false;

    network_time *network_time_obj;

    QString python3_path;
    QString xcode_build_path;

    recon_helper_process *recon_helper_process_obj;

    bool check_internet_connectivity();
    bool get_necessary_package_installation_status(QString python3_path, QString xcode_build_path, QString java_path, QString macfuse_path);
    QString java_path;
    QStringList missing_packages_name_list;
    QStringList missing_packages_installation_instruction_list;
    requirement_window *requirement_window_obj;
    QString macfuse_path;

};

#endif
