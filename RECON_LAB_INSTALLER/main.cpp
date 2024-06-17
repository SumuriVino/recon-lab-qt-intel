#include "mainwindow.h"
#include <QApplication>
#include <QtCore>

bool global_variable_debug_mode_status_bool = false;
bool global_variable_debug_encryption_status_bool = false;
bool global_variable_debug_print_on_terminal_bool = false;
bool global_variable_debug_print_in_file_bool = false;

bool global_variable_debug_type_general_bool = false;
bool global_variable_debug_type_conditional_bool = false;
bool global_variable_debug_type_intensive_bool = false;

const QString global_variable_private_var_tmp_Dir_Path_Parent_QString = QString("/private/var/tmp/RECON_LAB_Installer_") + getenv("USER") + ("/");
const QString global_variable_private_var_tmp_Dir_Path_Case_QString = global_variable_private_var_tmp_Dir_Path_Parent_QString + QString::number(QDateTime::currentSecsSinceEpoch()) + "/";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    global_variable_debug_mode_status_bool = false;
    global_variable_debug_print_on_terminal_bool = false;

    global_variable_debug_type_general_bool = false;
    global_variable_debug_type_conditional_bool = false;
    global_variable_debug_type_intensive_bool = false;

    recon_static_functions::do_directory_blank_completely(global_variable_private_var_tmp_Dir_Path_Parent_QString, Q_FUNC_INFO);
    QDir dir_tmp_usrname;
    dir_tmp_usrname.mkpath(QString(global_variable_private_var_tmp_Dir_Path_Case_QString));

    QDir dir;
    dir.setCurrent(QApplication::applicationDirPath());

    MainWindow w;
//    w.show();

    return a.exec();
}
