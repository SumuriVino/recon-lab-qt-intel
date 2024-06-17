#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString window_title = recon_static_functions::get_app_name() + " - " + recon_static_functions::get_app_version() + recon_static_functions::get_app_build_modified();

    setWindowTitle(window_title);

    system_password_asker_obj = new system_password_asker();
    connect(system_password_asker_obj, SIGNAL(signal_system_password_asker_workdone(bool, QString)), this, SLOT(slot_system_password_asker_workdone(bool, QString)));

    package_shifter_obj = new package_shifter();
    connect(package_shifter_obj, SIGNAL(signal_shifter_workdone(int)), this, SLOT(slot_package_shifter_workdone(int)));

    requirement_window_obj = new requirement_window();
    connect(requirement_window_obj, SIGNAL(signal_installation_workdone(int)), this, SLOT(slot_requirement_window_workdone(int)));

    package_installer_obj = new package_installer();
    connect(package_installer_obj, SIGNAL(signal_installation_workdone(int)), this, SLOT(slot_package_installer_workdone(int)));

    package_installer_obj->pub_set_requirement_window_obj(requirement_window_obj);

    lab_installer_obj = new lab_installer(this);

    setCentralWidget(lab_installer_obj);

    system_password_asker_obj->show();


}

MainWindow::~MainWindow()
{
    if(system_password_asker_obj != nullptr)
        delete system_password_asker_obj;

    if(package_shifter_obj != nullptr)
        delete package_shifter_obj;

    if(package_installer_obj != nullptr)
        delete package_installer_obj;

    if(requirement_window_obj != nullptr)
        delete requirement_window_obj;

    recon_static_functions::do_directory_blank_completely(global_variable_private_var_tmp_Dir_Path_Parent_QString, Q_FUNC_INFO);

    delete ui;
}


void MainWindow::slot_system_password_asker_workdone(bool status, QString password)
{
    recon_static_functions::app_debug("Start ", Q_FUNC_INFO);

    system_password_asker_obj->hide();

    if(status)
    {
        package_shifter_obj->show();
        package_shifter_obj->pub_update_module_files(password);
    }
    else
        QApplication::exit(0);

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);
}

void MainWindow::slot_package_shifter_workdone(int status)
{
    recon_static_functions::app_debug("Start ", Q_FUNC_INFO);

    package_shifter_obj->hide();

    if(status == enum_global_package_shifter_0_window_close)
    {
        QApplication::exit(0);
    }
    else if(status == enum_global_package_shifter_1_complete)
    {
        package_installer_obj->show();
        package_installer_obj->pub_check_package_status();
    }
    else
    {
        QCoreApplication::exit(0);
    }

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

}

void MainWindow::slot_package_installer_workdone(int m_status)
{
    recon_static_functions::app_debug("Start ", Q_FUNC_INFO);

    package_installer_obj->hide();

    if(m_status == enum_global_package_installer_0_window_close)
    {
        QApplication::exit(0);
    }
    else if(m_status == enum_global_package_installer_1_xcode_python_java_not_installed)
    {
        requirement_window_obj->show();
    }
    else if(m_status == enum_global_package_installer_2_skip || m_status == enum_global_package_installer_3_continue)
    {
        show();
    }
    else
        QApplication::exit(0);

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

}

void MainWindow::slot_requirement_window_workdone(int m_status)
{
    recon_static_functions::app_debug("Start ", Q_FUNC_INFO);


    if(m_status == enum_global_requirement_window_0_okay)
    {
        QApplication::exit(0);

    }
    else
        QApplication::exit(0);

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

}
