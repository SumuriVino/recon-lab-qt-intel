#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

#include "system_password_asker/system_password_asker.h"
#include "package_installer/package_installer.h"
#include "lab_installer.h"
#include "package_shifter/package_shifter.h"
#include "requirement_window/requirement_window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slot_system_password_asker_workdone(bool status, QString password);
    void slot_package_installer_workdone(int m_status);
    void slot_requirement_window_workdone(int m_status);
    void slot_package_shifter_workdone(int status);


private:
    Ui::MainWindow *ui;

    system_password_asker *system_password_asker_obj;

    package_installer *package_installer_obj;

    lab_installer *lab_installer_obj;

    package_shifter *package_shifter_obj;
    requirement_window *requirement_window_obj;
};

#endif // MAINWINDOW_H
