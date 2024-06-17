#ifndef RECON_HELPER_STANDARD_H
#define RECON_HELPER_STANDARD_H

#include <QWidget>
#include "recon_static_functions.h"

#include "recon_generic_functions/recon_helper_process.h"

class recon_helper_standard : public QObject
{
    Q_OBJECT

public:
    recon_helper_standard(QObject *parent = 0);
    ~recon_helper_standard();


    void copy_directory_by_cp(QString module_dir_path, QString dest_dir_path, QString caller_func);

    bool copy_directory_by_read(QString received_source_path, QString received_dest_path, QString caller_func);

    void sudo_copy_directory_by_cp(QString module_dir_path, QString dest_dir_path, QString caller_func);

signals:

private slots:

private:

    recon_helper_process *recon_helper_process_obj;
};

#endif
