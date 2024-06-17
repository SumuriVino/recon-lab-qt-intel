#include "requirement_window.h"
#include "ui_requirement_window.h"

requirement_window::requirement_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::requirement_window)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    setWindowModality(Qt::WindowModality());
    setWindowTitle("RECON LAB - Dependency Missing");

    ui->pushButton_okay_dependency_missing->setText("Okay");
    ui->pushButton_okay_dependency_missing->setMaximumWidth(60);
    connect(ui->pushButton_okay_dependency_missing,SIGNAL(clicked(bool)),this,SLOT(slot_pushbutton_okay_clicked(bool)));
    ui->textBrowser_instructions_to_install->setOpenExternalLinks(true);


}


requirement_window::~requirement_window()
{
    delete ui;
}

void requirement_window::pub_set_messages(QString message)
{
    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    ui->label_message_dependency_missing->setText(message);

    ui->label_message_dependency_missing->setAlignment(Qt::AlignCenter);

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);
}

void requirement_window::pub_set_instructions(QString instructions)
{
    recon_static_functions::app_debug("Starts ", Q_FUNC_INFO);

    QString instruction_str = QString("<b>Instructions to install </b> <br> <br>" + instructions);

    ui->textBrowser_instructions_to_install->setText(instruction_str);

    recon_static_functions::app_debug("End ", Q_FUNC_INFO);
}


void requirement_window::slot_pushbutton_okay_clicked(bool click)
{
    emit signal_installation_workdone(enum_global_requirement_window_0_okay);
}


