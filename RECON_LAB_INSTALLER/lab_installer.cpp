#include "lab_installer.h"
#include "ui_lab_installer.h"

lab_installer::lab_installer(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::lab_installer)
{
    ui->setupUi(this);

    QPixmap pix("../Resources/sumuri_with_lab_logo.png");

    ui->label_logo->setPixmap(pix);

    proc = new QProcess(this);

    connect(proc, SIGNAL(finished(int)), this, SLOT(slot_proc_finished(int)));

    license_file_backup_path = QString(getenv("HOME")) + "/.recon_lab_license";

    license_file_app_bundle_macos_path = QString("/Applications/RECON_LAB.app/Contents/MacOS/license");

    license_file_recon_library_path = QString(getenv("HOME")) + "/Library/RECON_LAB/license";

    file_dialog_obj.setOption(QFileDialog::DontUseNativeDialog);
    QList<QUrl> drives;
    drives << QUrl::fromLocalFile(QDir("/Volumes/").absolutePath());
    drives << QUrl::fromLocalFile(QDir("/").absolutePath());
    drives << QUrl::fromLocalFile(QDir(getenv("HOME")).absolutePath());
    drives << QUrl::fromLocalFile(QDir(getenv("HOME") + QString("/Downloads")).absolutePath());
    drives << QUrl::fromLocalFile(QDir(getenv("HOME") + QString("/Desktop")).absolutePath());
    drives << QUrl::fromLocalFile(QDir(getenv("HOME") + QString("/Documents")).absolutePath());
    file_dialog_obj.setSidebarUrls(drives);
    file_dialog_obj.setDirectory(getenv("HOME"));

    bool_license_replace_status = false;
    bool_license_replace_dialog_close = false;
    license_replace_dialog_obj = new license_replace_dialog(this);
    license_replace_dialog_obj->pub_set_window_title("");

    recon_helper_process_obj = new recon_helper_process(this);

    connect(license_replace_dialog_obj, SIGNAL(signal_license_replace_dialog_okay_clicked(bool, bool)), this, SLOT(slot_license_replace_dialog_okay_clicked(bool, bool)));


}

lab_installer::~lab_installer()
{
    delete ui;
}


void lab_installer::slot_proc_finished(int)
{
    bool_proc_finished = true;
}


void lab_installer::on_pushButton_install_clicked()
{

    //=======================================================//
    bool_license_replace_status = false;
    bool_license_replace_dialog_close = false;

    license_replace_dialog_obj->show();

    int tmp_count = 0;
    while(1)
    {
        tmp_count++;
        if(tmp_count % 250 == 0)
        {
            tmp_count = 0;
            QCoreApplication::processEvents();
        }

        if(bool_license_replace_dialog_close)
            break;
    }

    if(bool_license_replace_status)
    {
        bool bool_copy_status = copy_new_license_file();
        if(!bool_copy_status)
            return;
    }
    //=======================================================//

    QString license_file_path = license_file_recon_library_path;
    if(!QFileInfo(license_file_path).exists())
        license_file_path = license_file_app_bundle_macos_path;

    QFile lic_file(license_file_path);
    QFile back_file(license_file_backup_path);
    back_file.remove();

    lic_file.copy(license_file_backup_path);

    enable_widgets(false);
    delete_previous_copy_of_recon_lab();

    copy_new_recon_lab();

    QFile restore_file(license_file_backup_path);
    restore_file.copy(license_file_recon_library_path);

    ui->label_status->setText("Done!!!");
    enable_widgets(true);


}

void lab_installer::delete_previous_copy_of_recon_lab()
{

    ui->label_status->setText("Removing previous version...");
    QStringList args;

    args << "-rf";
    args << "/Applications/RECON_LAB.app";

    recon_helper_process_obj->run_command_with_arguments("rm", args, Q_FUNC_INFO);

    ui->label_status->setText("Removing previous version...Done!");

}

void lab_installer::copy_new_recon_lab()
{
    ui->label_status->setText("Installing...");

    QStringList args;

    args << "-rf";
    args << "/Applications/RECON_LAB.app" << "/Applications/__MACOSX/";

    recon_helper_process_obj->run_command_with_arguments("rm", args, Q_FUNC_INFO);

    ///==============================================================================///
    args.clear();
    args << "-u";
    args << "../Resources/RECON_LAB.zip";
    args << "-d";
    args << "/Applications/";

    recon_helper_process_obj->run_command_with_arguments("unzip", args, Q_FUNC_INFO);

    ///==============================================================================///



    ///==============================================================================///
    //    QString dest_file_path = QString("/Applications/");
    //    QString zip_file_path = QString("../Resources/RECON_LAB.zip");

    //    JlCompress::extractDir(zip_file_path ,dest_file_path);

    //    QProcess::execute("rm -rf /Applications/__MACOSX/");
    ///==============================================================================///


    args.clear();

    args << "-cr";
    args << "/Applications/RECON_LAB.app";

    recon_helper_process_obj->run_command_with_arguments("xattr", args, Q_FUNC_INFO);

    ///==============================================================================///

    args.clear();
    args << "-rf" << "/Applications/__MACOSX/";

    recon_helper_process_obj->run_command_with_arguments("rm", args, Q_FUNC_INFO);

    ui->label_status->setText("Installation Complete!");


}

void lab_installer::delete_recon_library()
{
    QString home_dir = getenv(("HOME"));

    QString recon_lab_library_path = home_dir + "/Library/RECON_LAB";

    ui->label_status->setText("Removing RECON LAB library data...");
    QStringList args;

    args << "-rf";
    args << recon_lab_library_path;

    recon_helper_process_obj->run_command_with_arguments("rm", args, Q_FUNC_INFO);

    ui->label_status->setText("Removing RECON LAB library data...Done!");

}

void lab_installer::enable_widgets(bool status)
{
    ui->pushButton_clean_install->setEnabled(status);
    ui->pushButton_install->setEnabled(status);
    ui->pushButton_uninstall->setEnabled(status);
}

void lab_installer::on_pushButton_clean_install_clicked()
{
    enable_widgets(false);

    delete_recon_library();
    delete_previous_copy_of_recon_lab();
    copy_new_recon_lab();

    ui->label_status->setText("Done!!!");
    enable_widgets(true);

}

void lab_installer::on_pushButton_uninstall_clicked()
{
    enable_widgets(false);

    delete_recon_library();
    delete_previous_copy_of_recon_lab();
    ui->label_status->setText("Done!!!");
    enable_widgets(true);

}

void lab_installer::slot_license_replace_dialog_okay_clicked(bool bool_lic_rep_status, bool bool_lic_dialog_close_status)
{
    bool_license_replace_status = bool_lic_rep_status;
    bool_license_replace_dialog_close = bool_lic_dialog_close_status;

}

bool lab_installer::copy_new_license_file()
{
    QString new_lic_file_path;
    file_dialog_obj.setFileMode(QFileDialog::AnyFile);
    if(file_dialog_obj.exec())
    {
        QStringList selected_files = file_dialog_obj.selectedFiles();

        if(selected_files.size() > 0)
        {
            new_lic_file_path = selected_files.at(0);
        }
    }
    new_lic_file_path = new_lic_file_path.trimmed();


    if(new_lic_file_path.isEmpty())
        return false;

    if(QFileInfo(new_lic_file_path).fileName() != QString("license"))
        return false;


    QString dest_lic_file_path = license_file_recon_library_path;


    if(QFileInfo(dest_lic_file_path).exists())
        QFile::remove(dest_lic_file_path);


    bool copy_status = QFile::copy(new_lic_file_path, dest_lic_file_path);

    return  copy_status;
}

