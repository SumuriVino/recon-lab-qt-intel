#include "package_installer.h"
#include "ui_package_installer.h"

package_installer::package_installer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::package_installer)
{
    ui->setupUi(this);

    QString window_title = recon_static_functions::get_app_name() + " - " + recon_static_functions::get_app_version() + recon_static_functions::get_app_build_modified();

    setWindowTitle(window_title);

    ui->progressBar->hide();

    ui->pushButton_skip->setVisible(false);
    ui->pushButton_install->setVisible(false);

    ui->progressBar->setRange(0,0);

    xcode_build_path = QString("/usr/bin/xcodebuild");
    macfuse_path = QString("/Library/Filesystems/macfuse.fs/Contents/version.plist");
    java_path = QString("/usr/bin/java");

    recon_helper_process_obj = new recon_helper_process(this);

    python3_path = QString("/usr/local/bin/python3");

    QStringList args_list;
    args_list << QString("--version");
    QString python_cmd_output = recon_helper_process_obj->run_command_with_arguments(python3_path, args_list, Q_FUNC_INFO);

    if(!python_cmd_output.startsWith("Python 3.9"))
    {
        python3_path = QString("/Library/Frameworks/Python.framework/Versions/3.9/bin/python3");
    }


    network_time_obj = new network_time(this);

    missing_packages_name_list.clear();
    missing_packages_installation_instruction_list.clear();

}

package_installer::~package_installer()
{   
    delete ui;
}

void package_installer::closeEvent(QCloseEvent *event)
{
    bool_window_close = true;

    recon_helper_process_obj->pub_cancel_process();

    emit signal_installation_workdone(enum_global_package_installer_0_window_close);
}

bool package_installer::get_necessary_package_installation_status(QString python3_path, QString xcode_build_path, QString java_path, QString macfuse_path)
{
    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    missing_packages_name_list.clear();
    missing_packages_installation_instruction_list.clear();

    QString xcode_instructions_for_install_str = QString(0x00BB) + QString(" You can install Xcode from Mac App Store.");

    QString java_instructions_for_install_str = QString(0x00BB) + QString(" You can install Java from this link: "
                                                                          "<a href=\"https://www.java.com/en/download/manual.jsp\">https://www.java.com/en/download/manual.jsp</a>");

//    QString python_instructions_for_install_str = QString(0x00BB) + QString(" Download and install the latest version of Python3 (Version 3.9)"
//                                                                            " for macOS from this link: "
//                                                                            "<a href=\"https://www.python.org/downloads//\">https://www.python.org/downloads/</a>");

    QString python_instructions_for_install_str = QString(0x00BB) + QString(" Download and install the latest version of Python3 (Version 3.9)"
                                                                            " for macOS from this link: "
                                                                            "<a href=\"https://www.python.org/ftp/python/3.9.6/python-3.9.6-macosx10.9.pkg\">https://www.python.org/ftp/python/3.9.6/python-3.9.6-macosx10.9.pkg</a>");

    QString macfuse_instructions_for_install_str = QString(0x00BB) + QString(" You can install macFUSE from this link:"
                                                                             "<a href=\"https://osxfuse.github.io\">https://osxfuse.github.io</a>");


    ///Do not Change the positions of 'if' conditions in this function.

    QFile xcode_file(xcode_build_path);
    if(xcode_file.exists())
    {
        QStringList args_list;
        args_list << QString("-version");
        QString xcode_cmd_output = recon_helper_process_obj->run_command_with_arguments(xcode_build_path, args_list, Q_FUNC_INFO);

        if(!xcode_cmd_output.startsWith("Xcode "))
        {
            missing_packages_name_list << QString("Xcode");
            missing_packages_installation_instruction_list << xcode_instructions_for_install_str;
        }
    }
    else
    {
        missing_packages_name_list << QString("Xcode");
        missing_packages_installation_instruction_list << xcode_instructions_for_install_str;
    }




    QFile macfuse_file(macfuse_path);
    if(macfuse_file.exists())
    {
        QStringList args_list;
        args_list << QString("-c") << QString("print :'CFBundleVersion'") << macfuse_path;
        QString macfuse_cmd_output = recon_helper_process_obj->run_command_with_arguments("/usr/libexec/PlistBuddy", args_list, Q_FUNC_INFO);

        if(macfuse_cmd_output.contains("Does Not Exist" , Qt::CaseInsensitive)
                || macfuse_cmd_output.contains("Doesn't Exist" , Qt::CaseInsensitive)
                || macfuse_cmd_output.trimmed().isEmpty())
        {
            missing_packages_name_list << QString("macFUSE");
            missing_packages_installation_instruction_list << macfuse_instructions_for_install_str;
        }
    }
    else
    {
        missing_packages_name_list << QString("macFUSE");
        missing_packages_installation_instruction_list << macfuse_instructions_for_install_str;
    }




    QFile java_file(java_path);
    if(java_file.exists())
    {
        QStringList args_list;
        args_list << QString("-version");
        QString java_cmd_output = recon_helper_process_obj->run_command_with_arguments(java_path, args_list, Q_FUNC_INFO);

        if(!java_cmd_output.startsWith("java version") && !java_cmd_output.startsWith("openjdk version"))
        {
            missing_packages_name_list << QString("Java");
            missing_packages_installation_instruction_list << java_instructions_for_install_str;
        }
    }
    else
    {
        missing_packages_name_list << QString("Java");
        missing_packages_installation_instruction_list << java_instructions_for_install_str;
    }




    QFile python3_file(python3_path);

    if(python3_file.exists())
    {
        QStringList args_list;
        args_list << QString("--version");
        QString python_cmd_output = recon_helper_process_obj->run_command_with_arguments(python3_path, args_list, Q_FUNC_INFO);
        //        if(!python_cmd_output.startsWith("Python 3."))
        if(!python_cmd_output.startsWith("Python 3.9"))
        {
            missing_packages_name_list << QString("Python3");
            missing_packages_installation_instruction_list << python_instructions_for_install_str;
        }
    }
    else
    {
        missing_packages_name_list << QString("Python3");
        missing_packages_installation_instruction_list << python_instructions_for_install_str;
    }



    if(missing_packages_name_list.size() > 0)
    {
        return false;
    }

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

    return true;
}

void package_installer::pub_check_package_status()
{

    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    ui->label_message->setText("Please wait... Checking packages...");

    ui->progressBar->show();

    bool status = check_intial_packages_status();

    if(!status)
    {
        QString dependency_name;
        QString dependency_resolve_solution;

        dependency_name = missing_packages_name_list.join(",");
        dependency_resolve_solution = missing_packages_installation_instruction_list.join("<br>");



        QString text_message = QString("WARNING: RECON LAB has detected that you are missing [<b>" + dependency_name + "</b>]. <br>"
                                                                                                                       "This <b> add-on </b> is necessary for RECON LAB to properly run all of it's features and must be added "
                                                                                                                       "<br> manually.&nbsp;Please press <b> " + "'Okay'" + " </b> to end installation and install the <b> required dependency before continuing. </b> <br><br>");

        recon_helper_process_obj->pub_cancel_process();

        requirement_window_obj->pub_set_messages(text_message);
        requirement_window_obj->pub_set_instructions(dependency_resolve_solution);

        this->hide();
        emit signal_installation_workdone(enum_global_package_installer_1_xcode_python_java_not_installed);

        return;

    }

    status = check_python_packages_installation_required();

    if(status)
    {

        ui->label_message->setText("Recon Lab Installer needs to install missing packages.  Please click on 'Install' to continue.");
        ui->label_internet_warning->setText("*Internet connectivity required for installation.");
        ui->label_internet_warning->setStyleSheet("QLabel{color : red;}");
    }

    else
    {
        ui->label_message->setText("Packages checking done.  Please click on 'Continue'.");
        ui->pushButton_install->setText("Continue");
        ui->pushButton_skip->setVisible(false);
        ui->label_internet_warning->setText("");
    }

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

}

bool package_installer::check_intial_packages_status()
{

    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    bool status = get_necessary_package_installation_status(python3_path, xcode_build_path, java_path, macfuse_path);

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

    return status;

}

bool package_installer::check_python_packages_installation_required()
{
    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    QStringList packages_list;
    //    packages_list << "lz4" << "enum34" << "tensorflow" << "nudenet" << "filetype"
    //                  << "python-magic-bin" << "mime" << "mimelib" << "glob2" << "moviepy"
    //                  << "ffmpeg" << "opencv-python" << "pillow";

    packages_list << "lz4" << "enum34"  << "nudenet" << "filetype"
                  << "mime" << "mimelib" << "glob2" << "moviepy"
                  << "ffmpeg" << "opencv-python" << "pillow";

    bool bool_is_installation_required = false;

    non_installed_package_command_list.clear();

    for(int ii = 0; ii < packages_list.size(); ii++)
    {

        if(bool_window_close)
            break;

        QString package_name = packages_list.at(ii);

        //Note: Add Power(^) at the begining of the package to find package name start with a particular name.
        //Note: Add space at the end of the package name for found exact match in output.

        QString final_command = python3_path + " -m pip list | grep -i '^" + package_name + " '";

        QString pck_cmd_output = recon_helper_process_obj->run_command_by_shell(final_command, Q_FUNC_INFO);

        //Note:  Space after package name is used to get the exact match for a particular package.
        if(!pck_cmd_output.startsWith(QString(package_name + " "), Qt::CaseInsensitive))
        {
            bool_is_installation_required = true;

            //            if(package_name.contains("python-magic-bin"))
            //            {
            //                //Note: Grep command does not recognize python-magic-bin with version.
            //                //So, we are adding version in installation command.
            //                non_installed_package_command_list << python3_path + " -m pip install " + package_name + "==0.4.14";
            //            }
            //            else
            //            {
            //                non_installed_package_command_list << python3_path + " -m pip install " + package_name;
            //            }

            non_installed_package_command_list << python3_path + " -m pip install " + package_name;

        }

    }

    ui->progressBar->hide();

    ui->pushButton_install->setVisible(true);

    ui->pushButton_skip->setVisible(true);

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

    return bool_is_installation_required;

}

void package_installer::on_pushButton_install_clicked()
{

    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    if(ui->pushButton_install->text() == "Continue")
    {
        emit signal_installation_workdone(enum_global_package_installer_3_continue);
        return;
    }

    ui->pushButton_skip->setVisible(false);

    ui->label_message->setText("Please wait...");

    ui->progressBar->show();

    ui->pushButton_install->setDisabled(true);

    bool network_failure_status = check_internet_connectivity();

    if(network_failure_status)
    {
        ui->label_message->setText("Failed to install packages.  Please check your internet connectivity.");

        ui->pushButton_install->setDisabled(false);
        ui->pushButton_skip->setVisible(true);

        ui->progressBar->hide();
        return;
    }

    ui->label_message->setText("Packages installation starts...");

    bool bool_package_successfully_installed = false;

    for(int ii = 0; ii < non_installed_package_command_list.size(); ii++)
    {
        if(bool_window_close)
        {
            break;
        }

        QString pkg_cmd = non_installed_package_command_list.at(ii);

        QString msg_str = "Please wait... Packages installing " + QString::number(ii + 1) + "/" + QString::number(non_installed_package_command_list.size());

        ui->label_message->setText(msg_str);

        QString cmd_output = recon_helper_process_obj->run_command_by_shell(pkg_cmd, Q_FUNC_INFO);

        if(cmd_output.contains("Failed to establish a new connection"))
        {
            bool_package_successfully_installed = false;
            break;
        }
        else
            bool_package_successfully_installed = true;
    }

    if(!bool_package_successfully_installed)
    {
        ui->label_message->setText("Failed to install packages.  Please check your internet connectivity.");

        ui->pushButton_install->setDisabled(false);
        ui->pushButton_skip->setVisible(true);

        ui->progressBar->hide();
        return;
    }

    ui->progressBar->hide();

    ui->pushButton_install->setDisabled(false);

    ui->pushButton_install->setText(QString("Continue"));

    ui->label_internet_warning->setText("");
    ui->label_message->setText("Packages installation completed.  Please click on 'Continue'.");

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

}

bool package_installer::check_internet_connectivity()
{
    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    return network_time_obj->pub_get_internet_connectivity_status();

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

}

void package_installer::on_pushButton_skip_clicked()
{
    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    emit signal_installation_workdone(enum_global_package_installer_2_skip);

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);

}

void package_installer::pub_set_requirement_window_obj(requirement_window *requirement_window_object)
{
    requirement_window_obj = requirement_window_object;
}
