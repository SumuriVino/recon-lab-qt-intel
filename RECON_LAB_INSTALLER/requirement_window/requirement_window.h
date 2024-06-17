#ifndef requirement_window_H
#define requirement_window_H

#include <QtGui>
#include <QColorDialog>
#include "QtCore"
#include "QPushButton"
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QSpacerItem>

#include "recon_generic_functions/recon_static_functions.h"
#include "recon_generic_functions/recon_helper_process.h"

namespace Ui {
class requirement_window;
}

class requirement_window : public QWidget
{
    Q_OBJECT

public:
    explicit requirement_window(QWidget *parent = nullptr);
    ~requirement_window();

    void pub_set_messages(QString message);

    void pub_set_instructions(QString instructions);
signals:
    void signal_installation_workdone(int m_status);
private slots:

    void slot_pushbutton_okay_clicked(bool click);
private:
    Ui::requirement_window *ui;

};

#endif // requirement_window_H
