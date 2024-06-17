#include "recon_static_functions.h"
#include <QApplication>
#include <QtCore>
#include <QtGui>



recon_static_functions::recon_static_functions(QWidget *parent)
{
    Q_UNUSED(parent)
}

QString recon_static_functions::get_app_version()
{
    /* Always give main version in 3 numeric digit like 1.1.1
     * Always give main version in ascending order (1.1.2 OR 2.0.0) comparatively last given version(1.1.1)
     * Mean 112 > 111  OR 200 > 111
    */

    return QString("1.6.2");

}

QString recon_static_functions::get_app_build_modified()
{
    //QString str = " (" + get_app_build_regular() + ") - TestDebugBuild";
      QString str = " (" + get_app_build_regular() + ") - Intel";


//    QString str = " (" + get_app_build_regular() + ")";
    return str;

}

QString recon_static_functions::get_app_build_regular()
{
    // [A1 to A9]
    // [Z1 to Z9]

    // T - For Test Build [T1,T2....]
    // D - For Department [D1,D2....]

    return "B1";

}

QString recon_static_functions::get_app_name()
{
    return QString("RECON LAB INSTALLER");
}

QString recon_static_functions::prepare_callerfun(QString data)
{
    QString tmp_func_name = data;
    data = data.trimmed();
    data.remove(data.indexOf("(",0),data.size());
    data = data.trimmed();
    data.remove(0,data.lastIndexOf(" "));
    data = data.trimmed();
    data.remove("*");
    data = data.trimmed();

    if(data.contains("(") || data.contains(" "))
        data = tmp_func_name;

    return "{{CallerFunc = " + data + "}}";
}


void recon_static_functions::do_directory_blank_completely(QString dir_path, QString caller_func)
{
    Q_UNUSED(caller_func)

    if(!check_path_removable(dir_path, Q_FUNC_INFO))
        return;


    QDir dir(dir_path);
    if (dir.exists())
    {
        // Must use QDir::NoDotAndDotDot otherwise removeRecursively() will remove input dir also
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Hidden  | QDir::AllDirs | QDir::Files))
        {
            if(info.isDir())
            {

                recon_static_functions::do_directory_blank_completely(info.filePath(), Q_FUNC_INFO);
                recon_static_functions::remove_safely_blank_dir_OR_file(info.filePath(), Q_FUNC_INFO);
            }
            else
            {
                QFile::remove(info.filePath());
            }
        }
    }
}

bool recon_static_functions::check_path_removable(QString dir_path, QString caller_func)
{
    /*
     *  This check ensures that root or users directory will not be deleted.
     */

    if(dir_path.trimmed().isEmpty() || dir_path.trimmed() == QString("/"))
        return false;

    if(dir_path.startsWith(global_variable_private_var_tmp_Dir_Path_Parent_QString))
    {
        return true;
    }
    else if(dir_path.startsWith(global_variable_private_var_tmp_Dir_Path_Case_QString))
    {
        return true;
    }
    //    else if(dir_path.startsWith(global_narad_muni_class_obj->get_field(MACRO_NARAD_RECON_Library_Home_Dir_Path_QString).toString()))
    //    {
    //        return true;
    //    }

    return false;
}

bool recon_static_functions::remove_safely_blank_dir_OR_file(QString path, QString caller_func)
{

    if(!check_path_removable(path, Q_FUNC_INFO))
        return false;


    QFileInfo info(path);
    if(!info.exists())
    {
        (prepare_callerfun(caller_func) + " do not take tension return FALSE file does not exist : " + info.filePath(),Q_FUNC_INFO);
        return false;
    }

    if(info.isDir())
    {
        QDir dir(info.filePath());
        if(dir.count()<3)
        {
            // The directory must be empty for rmdir() to succeed
            return dir.rmdir(info.filePath());
        }
    }
    else
    {
        return QFile::remove(info.filePath());
    }

    return false;
}
