#ifndef RECON_STATIC_FUNCTIONS_H
#define RECON_STATIC_FUNCTIONS_H

#include <QtCore>
#include <QDateTimeEdit>
#include <QtSql/QtSql>
#include <QApplication>

#include <QMenu>
#include <set>


#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "header_global_variables.h"
#include "header_global_enum.h"


class recon_static_functions : public QWidget
{

public:
    explicit recon_static_functions(QWidget *parent = 0);


    static void app_debug(QString data, QString caller_func);
    static void debug_intensive(QString data, QString caller_func);
    static void debug_conditional(QString data, QString caller_func);


    static QString prepare_callerfun(QString data);

    static QString get_app_build_regular();
    static QString get_app_build_modified();
    static QString get_app_version();

    static QString get_app_name();

    static void do_directory_blank_completely(QString dir_path, QString caller_func);

    static bool check_path_removable(QString dir_path, QString caller_func);
    static bool remove_safely_blank_dir_OR_file(QString path, QString caller_func);

private:


};


#endif
