#include "system_password_asker.h"
#include "ui_system_password_asker.h"

system_password_asker::system_password_asker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::system_password_asker)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    QString m_ver = recon_static_functions::get_app_version() + recon_static_functions::get_app_build_modified();
    ui->label_version->setText(m_ver);


    ui->lineEdit_pwd->setAttribute(Qt::WA_MacShowFocusRect,false);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);


    //    recon_helper_standard_obj = new recon_helper_standard(this);
    recon_helper_process_obj = new recon_helper_process(this);

    QPixmap button_open("../icons/signs/eye_open.png");
    QIcon icon;
    icon.addPixmap(button_open, QIcon::Normal, QIcon::Off);

    ui->pushButton_show_hide_password->setIcon(icon);

    setWindowTitle("System Password");
    ui->lineEdit_pwd->setPlaceholderText("Type password");
    ui->label_message->setText(recon_static_functions::get_app_name() + " require admin password to run some of its components.");
}

system_password_asker::~system_password_asker()
{
    delete ui;
}

void system_password_asker::closeEvent(QCloseEvent *)
{
    emit signal_system_password_asker_workdone(false, "");

}

void system_password_asker::pub_set_window_modality()
{
    setWindowModality(Qt::WindowModal);

}

void system_password_asker::pub_set_essentials()
{
    ui->label_status->clear();
    // ui->lineEdit_pwd->clear();
}

void system_password_asker::pub_set_label_msg(QString text)
{
    ui->label_message->setText(text);
}

void system_password_asker::on_pushButton_cancel_clicked()
{
    emit signal_system_password_asker_workdone(false, "");
}

void system_password_asker::on_pushButton_ok_clicked()
{
    bool pwd_status = is_system_pwd_accurate(ui->lineEdit_pwd->text(), Q_FUNC_INFO);

    if(!pwd_status)
    {
        QPalette palette = ui->label_status->palette();
        palette.setColor(ui->label_status->foregroundRole(),QColor(Qt::red));
        ui->label_status->setPalette(palette);

        ui->label_status->setText("<b>Invalid Password.</b>");

        return;
    }


    QString m_password = ui->lineEdit_pwd->text();

    emit signal_system_password_asker_workdone(true, m_password);

}



void system_password_asker::on_pushButton_show_hide_password_clicked(bool checked)
{
    if(checked)
    {
        QPixmap button_open("../icons/signs/eye_close.png");
        QIcon icon;
        icon.addPixmap(button_open, QIcon::Normal, QIcon::Off);
        ui->pushButton_show_hide_password->setIcon(icon);
        ui->lineEdit_pwd->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        QPixmap button_open("../icons/signs/eye_open.png");
        QIcon icon;
        icon.addPixmap(button_open, QIcon::Normal, QIcon::Off);
        ui->pushButton_show_hide_password->setIcon(icon);

        ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    }

}

void system_password_asker::on_lineEdit_pwd_textChanged(const QString &arg1)
{
    ui->label_status->clear();

}


bool system_password_asker::is_system_pwd_accurate(QString m_pwd_orgl, QString caller_func)
{
    recon_static_functions::app_debug(recon_static_functions::prepare_callerfun(caller_func) + " start " , Q_FUNC_INFO);

    bool mvalue = false;
    QStringList args;
    args << "-u" << QString(getenv("USER")).trimmed() << "-P" << m_pwd_orgl << "." << "-delete" << "/Users/xvhfjdhvig8fer7kewho8476rhjfhef8gfyz";
    QString pwd_status = recon_helper_process_obj->run_command_with_arguments("dscl", args, Q_FUNC_INFO);

    if(pwd_status.contains("delete: Invalid Path"))
    {
        mvalue = true;
    }

    recon_static_functions::app_debug(recon_static_functions::prepare_callerfun(caller_func) + " end " , Q_FUNC_INFO);

    return mvalue;
}


void system_password_asker::on_lineEdit_pwd_returnPressed()
{
    on_pushButton_ok_clicked();
}
