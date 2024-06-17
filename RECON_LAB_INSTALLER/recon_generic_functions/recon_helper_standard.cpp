#include "recon_helper_standard.h"

recon_helper_standard::recon_helper_standard(QObject *parent)
{
    recon_static_functions::app_debug("start", Q_FUNC_INFO);

    recon_helper_process_obj = new recon_helper_process(this);

    recon_static_functions::app_debug("end", Q_FUNC_INFO);

}

recon_helper_standard::~recon_helper_standard()
{

}

void recon_helper_standard::copy_directory_by_cp(QString module_dir_path, QString dest_dir_path, QString caller_func)
{
    recon_static_functions::app_debug(recon_static_functions::prepare_callerfun(caller_func) + "Start",Q_FUNC_INFO);

    //Note: it will also overwrite existing files at destination

    QDir dir(module_dir_path);
    if(!dir.exists())
        return;

    QString command = "cp";

    QStringList args;
    args << "-rf" << QString(module_dir_path + "/") << dest_dir_path;

    recon_helper_process_obj->run_command_with_arguments(command, args, Q_FUNC_INFO);

    recon_static_functions::app_debug(recon_static_functions::prepare_callerfun(caller_func) + "End",Q_FUNC_INFO);

}

void recon_helper_standard::sudo_copy_directory_by_cp(QString module_dir_path, QString dest_dir_path, QString caller_func)
{
    recon_static_functions::app_debug(recon_static_functions::prepare_callerfun(caller_func) + "Start",Q_FUNC_INFO);

    //Note: it will also overwrite existing files at destination

    QDir dir(module_dir_path);
    if(!dir.exists())
        return;

    QString system_password = "123";
    QString command = "echo '" + system_password + "' | sudo -S cp -rf " + module_dir_path  + "/ " + dest_dir_path;

    recon_helper_process_obj->run_command_by_shell(command, Q_FUNC_INFO);

    recon_static_functions::app_debug(recon_static_functions::prepare_callerfun(caller_func) + "End",Q_FUNC_INFO);

}

bool recon_helper_standard::copy_directory_by_read(QString received_source_path,QString received_dest_path, QString caller_func)
{
    recon_static_functions::debug_intensive(recon_static_functions::prepare_callerfun(caller_func) + " Start " , Q_FUNC_INFO);

    received_source_path = received_source_path.trimmed();
    received_dest_path   = received_dest_path.trimmed();

    if(received_source_path.isEmpty() || received_dest_path.isEmpty() || received_source_path == QString("/"))
        return false;

    QDir source_dir(received_source_path);


    if(!source_dir.exists())
        return false;


    QDir dest_dir(received_dest_path);

    if(!dest_dir.exists())
    {
        dest_dir.mkpath(received_dest_path);
    }

    QStringList files = source_dir.entryList(QDir::Files | QDir::Hidden | QDir::System);

    for(int i = 0; i< files.count(); i++)
    {
        if(i % 10 == 0)
            QCoreApplication::processEvents();

        QFileInfo info;
        QString src_name = received_source_path + "/" + files[i];
        QString dest_name = received_dest_path + "/" + files[i];
        info.setFile(src_name);

        QFile source_file(src_name);
        QFile dest_file(dest_name);
        if(source_file.exists())
        {
            if(!source_file.open(QIODevice::ReadOnly))
            {
                recon_static_functions::app_debug(recon_static_functions::prepare_callerfun(caller_func) + " -- source_file.open  ----FAILED---" + src_name,Q_FUNC_INFO);
                recon_static_functions::app_debug(source_file.errorString(),Q_FUNC_INFO);
                continue;
            }
            if(!dest_file.open(QIODevice::WriteOnly))
            {
                recon_static_functions::app_debug(recon_static_functions::prepare_callerfun(caller_func) + " -- dest_file.open  ----FAILED---" + dest_name,Q_FUNC_INFO);
                recon_static_functions::app_debug(dest_file.errorString(),Q_FUNC_INFO);
                source_file.close();
                continue;

            }


            while(1)
            {
                // QCoreApplication::processEvents();
                QCoreApplication::processEvents();

                QByteArray dar = source_file.read(102400);
                if(dar.size() <= 0)
                {
                    break;
                }

                dest_file.write(dar);

            }

            source_file.close();
            dest_file.close();

        }
    }

    files.clear();
    files = source_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

    for(int i = 0; i< files.count(); i++)
    {
        QCoreApplication::processEvents();

        QString src_name = received_source_path + "/" + files[i];
        QString dest_name = received_dest_path + "/" + files[i];
        copy_directory_by_read(src_name, dest_name, caller_func);
    }

    recon_static_functions::debug_intensive(recon_static_functions::prepare_callerfun(caller_func) + " end " , Q_FUNC_INFO);

    return true;
}

