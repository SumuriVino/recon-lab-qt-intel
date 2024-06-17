#include "recon_static_functions.h"

void recon_static_functions::app_debug(QString data, QString caller_func)
{

    if(!global_variable_debug_mode_status_bool)
        return;

    if(!global_variable_debug_type_general_bool)
        return;


    if(caller_func.trimmed().isEmpty())
    {
        caller_func = "FUNCTION INFO IS EMPTY ---FAILED--- debug!!!";
    }
    else
    {
        QString tmp_func_name = caller_func;
        caller_func = caller_func.trimmed();
        caller_func.remove(caller_func.indexOf("(",0),caller_func.size());
        caller_func = caller_func.trimmed();
        caller_func.remove(0,caller_func.lastIndexOf(" "));
        caller_func = caller_func.trimmed();
        caller_func.remove("*");
        caller_func = caller_func.trimmed();

        if(caller_func.contains("(") || caller_func.contains(" "))
            caller_func = tmp_func_name;
    }

    QString date_time = QDateTime::currentDateTime().toString("yyyy-MMM-ddThh-mm-ss.zzz");

    QString fnl_data = "[" + get_app_name() + "][" + date_time + "][Normal Debug]" + "["+ caller_func + "]:-- " +  data;


    if(global_variable_debug_print_on_terminal_bool)
    {
        //================When quoting is disabled, escape characters will not be printed on terminal like \n , \t=============//
        //================\n will be treated as a next line instead of just a text=============================================//
        qDebug().noquote() <<  fnl_data;
    }


    if(global_variable_debug_print_in_file_bool)
    {
//        QString log_file_data = "[" + get_app_name() + "-" + get_app_version() + get_app_build_modified().trimmed() + "] [" + date_time + "][Normal Debug]" + "["+ caller_func + "]:-- " +  data;
//        fnl_data = log_file_data;

//        if(global_variable_debug_encryption_status_bool)
//        {
//            QString encrypted_data = recon_static_functions::encrypt_string(fnl_data , Q_FUNC_INFO);
//            debug_file_regular_ptr.write(encrypted_data.toLocal8Bit() , encrypted_data.toLocal8Bit().size());
//            debug_file_regular_ptr.write(MACRO_GLOBAL_COMMON_RECON_AND_ARTIFACT_Splitter_3_Brackets);
//        }
//        else
//        {
//            debug_file_regular_ptr.write(fnl_data.toLocal8Bit() , fnl_data.toLocal8Bit().size());
//            debug_file_regular_ptr.write("\n");
//        }


//        debug_file_regular_ptr.flush();
    }


}

void recon_static_functions::debug_intensive(QString data, QString caller_func)
{

    if(!global_variable_debug_mode_status_bool)
        return;

    if(!global_variable_debug_type_intensive_bool)
        return;

    if(caller_func.trimmed().isEmpty())
    {
        caller_func = "FUNCTION INFO IS EMPTY ---FAILED--- debug!!!";
    }
    else
    {
        QString tmp_func_name = caller_func;
        caller_func = caller_func.trimmed();
        caller_func.remove(caller_func.indexOf("(",0),caller_func.size());
        caller_func = caller_func.trimmed();
        caller_func.remove(0,caller_func.lastIndexOf(" "));
        caller_func = caller_func.trimmed();
        caller_func.remove("*");
        caller_func = caller_func.trimmed();

        if(caller_func.contains("(") || caller_func.contains(" "))
            caller_func = tmp_func_name;
    }

    QString date_time = QDateTime::currentDateTime().toString("yyyy-MMM-ddThh-mm-ss");

    QString fnl_data = "[" + get_app_name() + "][" + date_time + "][Intensive Debug]" + "["+ caller_func + "]:-- " +  data;

    if(global_variable_debug_print_on_terminal_bool)
    {
        //================When quoting is disabled, escape characters will not be printed on terminal like \n , \t=============//
        //================\n will be treated as a next line instead of just a text=============================================//
        qDebug().noquote() <<  fnl_data;
    }


    if(global_variable_debug_print_in_file_bool)
    {

//        QString log_file_data = "[" + get_app_name() + "-" + get_app_version() + get_app_build_modified().trimmed() + "] [" + date_time + "][Intensive Debug]" + "["+ caller_func + "]:-- " +  data;
//        fnl_data = log_file_data;

//        if(global_variable_debug_encryption_status_bool)
//        {
//            QString encrypted_data = recon_static_functions::encrypt_string(fnl_data , Q_FUNC_INFO);
//            debug_file_regular_ptr.write(encrypted_data.toLocal8Bit() , encrypted_data.toLocal8Bit().size());
//            debug_file_regular_ptr.write(MACRO_GLOBAL_COMMON_RECON_AND_ARTIFACT_Splitter_3_Brackets);
//        }
//        else
//        {
//            debug_file_regular_ptr.write(fnl_data.toLocal8Bit() , fnl_data.toLocal8Bit().size());
//            debug_file_regular_ptr.write("\n");
//        }

//        debug_file_regular_ptr.flush();
    }

}

void recon_static_functions::debug_conditional(QString data, QString caller_func)
{

    if(!global_variable_debug_mode_status_bool)
        return;

    if(!global_variable_debug_type_conditional_bool)
        return;


    if(caller_func.trimmed().isEmpty())
    {
        caller_func = "FUNCTION INFO IS EMPTY ---FAILED--- debug!!!";
    }
    else
    {
        QString tmp_func_name = caller_func;
        caller_func = caller_func.trimmed();
        caller_func.remove(caller_func.indexOf("(",0),caller_func.size());
        caller_func = caller_func.trimmed();
        caller_func.remove(0,caller_func.lastIndexOf(" "));
        caller_func = caller_func.trimmed();
        caller_func.remove("*");
        caller_func = caller_func.trimmed();

        if(caller_func.contains("(") || caller_func.contains(" "))
            caller_func = tmp_func_name;
    }

    QString date_time = QDateTime::currentDateTime().toString("yyyy-MMM-ddThh-mm-ss");

    QString fnl_data = "[" + get_app_name() + "][" + date_time + "][Conditional Debug]" + "["+ caller_func + "]:-- " +  data;

    if(global_variable_debug_print_on_terminal_bool)
    {
        //================When quoting is disabled, escape characters will not be printed on terminal like \n , \t=============//
        //================\n will be treated as a next line instead of just a text=============================================//
        qDebug().noquote() <<  fnl_data;
    }

    if(global_variable_debug_print_in_file_bool)
    {
//        QString log_file_data = "[" + get_app_name() + "-" + get_app_version() + get_app_build_modified().trimmed() + "] [" + date_time + "][Conditional Debug]" + "["+ caller_func + "]:-- " +  data;
//        fnl_data = log_file_data;

//        if(global_variable_debug_encryption_status_bool)
//        {
//            QString encrypted_data = recon_static_functions::encrypt_string(fnl_data , Q_FUNC_INFO);
//            debug_file_regular_ptr.write(encrypted_data.toLocal8Bit() , encrypted_data.toLocal8Bit().size());
//            debug_file_regular_ptr.write(MACRO_GLOBAL_COMMON_RECON_AND_ARTIFACT_Splitter_3_Brackets);
//        }
//        else
//        {
//            debug_file_regular_ptr.write(fnl_data.toLocal8Bit() , fnl_data.toLocal8Bit().size());
//            debug_file_regular_ptr.write("\n");
//        }

//        debug_file_regular_ptr.flush();
    }

}

