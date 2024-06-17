#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T09:24:28
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RECON_LAB_INSTALLER
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    lab_installer.cpp \
    license_replace_dialog.cpp \
        main.cpp \
        mainwindow.cpp \
    requirement_window/requirement_window.cpp \
    network_time/network_time.cpp \
    package_installer/package_installer.cpp \
    package_shifter/package_shifter.cpp \
    recon_generic_functions/recon_helper_process.cpp \
    recon_generic_functions/recon_helper_standard.cpp \
    recon_generic_functions/recon_static_functions.cpp \
    recon_generic_functions/recon_static_print_debug.cpp \
    system_password_asker/system_password_asker.cpp \
    zipper/JlCompress.cpp \
    zipper/qioapi.cpp \
    zipper/quaadler32.cpp \
    zipper/quacrc32.cpp \
    zipper/quagzipfile.cpp \
    zipper/quaziodevice.cpp \
    zipper/quazip.cpp \
    zipper/quazipdir.cpp \
    zipper/quazipfile.cpp \
    zipper/quazipfileinfo.cpp \
    zipper/quazipnewinfo.cpp \
    zipper/unzip.c \
    zipper/zip.c

HEADERS += \
    header_global_enum.h \
    header_global_variables.h \
    lab_installer.h \
    license_replace_dialog.h \
        mainwindow.h \
    requirement_window/requirement_window.h \
    network_time/network_time.h \
    package_installer/package_installer.h \
    package_shifter/package_shifter.h \
    recon_generic_functions/recon_helper_process.h \
    recon_generic_functions/recon_helper_standard.h \
    recon_generic_functions/recon_static_functions.h \
    system_password_asker/system_password_asker.h \
    zipper/JlCompress.h \
    zipper/ioapi.h \
    zipper/minizip_crypt.h \
    zipper/quaadler32.h \
    zipper/quachecksum32.h \
    zipper/quacrc32.h \
    zipper/quagzipfile.h \
    zipper/quaziodevice.h \
    zipper/quazip.h \
    zipper/quazip_global.h \
    zipper/quazipdir.h \
    zipper/quazipfile.h \
    zipper/quazipfileinfo.h \
    zipper/quazipnewinfo.h \
    zipper/unzip.h \
    zipper/zip.h

FORMS += \
    lab_installer.ui \
    license_replace_dialog.ui \
        mainwindow.ui \
    requirement_window/requirement_window.ui \
    package_installer/package_installer.ui \
    package_shifter/package_shifter.ui \
    system_password_asker/system_password_asker.ui


LIBS += -lz


