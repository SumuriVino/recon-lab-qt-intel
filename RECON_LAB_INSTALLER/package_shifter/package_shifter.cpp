#include "package_shifter.h"
#include "ui_package_shifter.h"

package_shifter::package_shifter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::package_shifter)
{
    ui->setupUi(this);

    QString window_title = recon_static_functions::get_app_name() + " - " + recon_static_functions::get_app_version() + recon_static_functions::get_app_build_modified();

    setWindowTitle(window_title);

    ui->progressBar->setRange(0,0);

    ui->pushButton_skip->setVisible(false);
    ui->pushButton_install->setVisible(false);

    ui->label_message->setText("Please wait... Checking packages...");

    recon_helper_process_obj = new recon_helper_process(this);
    recon_helper_standard_obj = new recon_helper_standard(this);
}

package_shifter::~package_shifter()
{
    delete ui;
}

void package_shifter::closeEvent(QCloseEvent *event)
{
    bool_close_window = true;
    recon_helper_process_obj->pub_cancel_process();

    emit signal_shifter_workdone(enum_global_package_shifter_0_window_close);
}

void package_shifter::pub_update_module_files(QString password)
{
    system_password = password;

    skin_tone_detection();

    if(bool_close_window)
        return;

    emit signal_shifter_workdone(enum_global_package_shifter_1_complete);

}

void package_shifter::skin_tone_detection()
{
    QString destination_location = global_variable_private_var_tmp_Dir_Path_Case_QString + QString::number(QDateTime::currentSecsSinceEpoch()) + "_ST/";

    QStringList args;
    args << "-u" << "../Resources/NudeNet.zip" << "-d" << destination_location;

    recon_helper_process_obj->run_command_with_arguments("unzip", args, Q_FUNC_INFO);

    QString source_dir_path = destination_location + "NudeNet";

    QDir sou_dir(source_dir_path);
    if(!sou_dir.exists())
        return;

    QString dest_dir_path = QDir::homePath() + "/.NudeNet";

    if(bool_close_window)
        return;

    recon_helper_standard_obj->copy_directory_by_cp(source_dir_path, dest_dir_path, Q_FUNC_INFO);

    QDir rem_dir(source_dir_path);

    rem_dir.removeRecursively();

}
