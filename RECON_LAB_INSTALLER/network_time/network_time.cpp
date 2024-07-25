#include "network_time.h"

network_time::network_time(QObject *parent) :
    QObject(parent)
{

    test_performed = false;
    current_time_numeric_qint64 = 0;
    network_failure = true;
    time_date  = QString();




    // connect_to_nist_serv();



    //---------------- used 25 july 2015 to 29 -jul 2015 -----------//
    //    wget_prc = new QProcess(this);
    //    connect(wget_prc,SIGNAL(finished(int)),this,SLOT(slot_wget_finished(int)));
    //    run_wget();
    //----------------------------------------------------------------//



    // getSocialNetwork(); //used before 25 july 2015

}


void network_time::slot_connected()
{

}

void network_time::slot_timer()
{
    m_timer->stop();

    test_performed = true;
    network_failure = true;
    current_time_numeric_qint64 = 0;

}


bool network_time::nw_value()
{
    return network_failure;
}

qint64 network_time::return_string()
{
    return current_time_numeric_qint64;
}


bool network_time::pub_get_internet_connectivity_status()
{
    getSocialNetwork();

    int count = 0;

    while(!is_test_performed())
    {
        count++;
        if(count % 50 == 0)
        {
            QCoreApplication::processEvents();
            count = 0;
        }
    }

    return nw_value();
}


void network_time::getSocialNetwork() {

    network_failure = true;
    test_performed = false;
    current_time_numeric_qint64 = 0;

    QNetworkRequest request;
    //request.setUrl(QUrl("https://nist.time.gov/actualtime.cgi?lzbc=siqm9b"));
    //     request.setUrl(QUrl("http://www.sumuri.com"));
    //    request.setUrl(QUrl("http://www.forensodigital.com/sumuri/demo.php"));
    //     request.setUrl(QUrl("http://www.sumuri.com/timecheck.php"));
    request.setUrl(QUrl("https://sumuri.com/time/"));

    m_networkManager = new QNetworkAccessManager(this);
    QNetworkReply *reply = m_networkManager->get(request);

    connect(reply, SIGNAL(finished()),this, SLOT(onRequestCompleted()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(network_error(QNetworkReply::NetworkError)));


    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));
//    m_timer->setInterval(30000);
    m_timer->setInterval(50000);
    m_timer->start();

    // before 29-oct -2015

    //    QNetworkRequest request;
    //    request.setUrl(QUrl("http://www.earthtools.org/timezone/0/0"));
    //    // request.setUrl(QUrl("http://www.sumuri.com/timecheck.php"));

    //    m_networkManager = new QNetworkAccessManager(this);
    //    QNetworkReply *reply = m_networkManager->get(request);

    //    connect(reply, SIGNAL(finished()),this, SLOT(onRequestCompleted()));
    //    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(network_error(QNetworkReply::NetworkError)));

    return;
}


bool network_time::is_test_performed()
{
    return test_performed;
}

void network_time::onRequestCompleted()
{

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    current_time_numeric_qint64 = 0;
    //    QByteArray data;

    //    while(reply->bytesAvailable())
    //    {
    //        data = reply->readLine();
    //    }



    //    QString all_data = QString::fromLocal8Bit(data);

    ////    all_data = "sumuri=1719120365=";

    //    if(!all_data.contains("sumuri="))
    //    {
    //        test_performed = true;
    //        network_failure = true;
    //        return;
    //    }

    //    QStringList m_list = all_data.split("=");

    //    if(m_list.size() < 2)
    //    {
    //        test_performed = true;
    //        network_failure = false;
    //        return;
    //    }
    //    QString m_epch = m_list.at(1);


    // added on July 16 2024
    //    if (!reply) {
    //        return;
    //    }

    //    if (reply->error() != QNetworkReply::NoError) {
    //        qCritical() << "Network error:" << reply->errorString();
    //        reply->deleteLater();
    //        return;
    //    }

    QString m_epch;
    QByteArray data = reply->readAll();
    QString all_data = QString::fromUtf8(data);

    QString startMarker = "sumuri=";
    QString endMarker = "=";

    if(!all_data.contains("sumuri="))
    {
        test_performed = true;
        network_failure = true;
        return;
    }

    int startIndex = data.indexOf(startMarker);
    if (startIndex != -1)
    {
        startIndex += startMarker.length();  // Move past the 'sumuri=' part
        int endIndex = data.indexOf(endMarker, startIndex);
        if (endIndex != -1)
        {
            m_epch = data.mid(startIndex, endIndex - startIndex);
//            qDebug() << "Extracted epoch value " << m_epch;
        }
        else
        {
//            qDebug() << "End marker not found.";
        }
    }
    else
    {
//        qDebug() << "Start marker not found.";
    }


    current_time_numeric_qint64 = m_epch.toLongLong();
//    qDebug() << "Extracted epoch value " << current_time_numeric_qint64;

    m_timer->stop();

    // 1525132800   GMT: Tuesday, May 1, 2018 12:00:00 AM
    // 1735689599   GMT: Tuesday, December 31, 2024 11:59:59 PM

    if(current_time_numeric_qint64 < 1525132800 || current_time_numeric_qint64 > 1735689599)
    {
        test_performed = true;
        network_failure = true;
        current_time_numeric_qint64 = 0;
    }
    else
    {
        test_performed = true;
        network_failure = false;

    }

    return;

    // before - Mar-12-2019 Mj from Singapore

    //    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    //    current_epoch = 0;
    //    QByteArray data;

    //    while(reply->bytesAvailable())
    //    {
    //        data = reply->readLine();
    //    }


    //    data.remove(0, 17);
    //    data.chop(35);

    //    current_epoch = data.toLongLong();

    //    m_timer->stop();

    //    // 1530403200   Sunday, July 1, 2018 12:00:00 AM
    //    // 1561939200   Monday, July 1, 2019 12:00:00 AM

    //    if(current_epoch < 1530403200 || current_epoch > 1561939200)
    //    {
    //        test_performed = true;
    //        network_failure = true;
    //        current_epoch = 0;
    //    }
    //    else
    //    {
    //        test_performed = true;
    //        network_failure = false;

    //    }



    //    return;



    // before 29-oct-2015

    //    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    //    bool str_found = false;
    //    test_performed = true;



    //    while(reply->bytesAvailable())
    //    {
    //        QByteArray data = reply->readLine();

    //        if(data.contains("utctime"))
    //        {
    //            time_date = data;
    //            time_date.remove("<utctime>");
    //            time_date.remove("</utctime>");

    //            str_found = true;

    //            break;
    //        }
    //    }

    //    if(!str_found)
    //    {

    //        current_epoch = 0;
    //        return;
    //    }
    //    time_date = time_date.trimmed();

    //    QStringList list = time_date.split("-");

    //    QStringList list2 = list.at(2).split(" ");

    //    QString str = list.at(0) + "-" + list.at(1) + "-" + list2.at(0);

    //    QDate mdate;
    //    mdate = QDate::fromString(str,"yyyy-MM-dd");


    //    QTime mtime;
    //    mtime.setHMS(0,0,0);

    //    QDateTime mdatetime;
    //    mdatetime.setTimeSpec(Qt::UTC);
    //    mdatetime.setDate(mdate);
    //    mdatetime.setTime(mtime);


    //    network_failure = false;

    //    current_epoch = mdatetime.toTime_t();
    //    return;
}

void network_time::network_error(QNetworkReply::NetworkError)
{
    m_timer->stop();


    current_time_numeric_qint64 = 0;
    test_performed = true;
    network_failure = true;

    return;
}










void network_time::run_wget()
{

    QFile file("./timecheck.php");
    file.remove();


    QStringList arg;
    arg << "http://www.sumuri.com/timecheck.php";


    //wget_prc->start("./wget",arg);


}

void network_time::slot_wget_finished(int)
{
    test_performed = true;
    network_failure = true;
    current_time_numeric_qint64 = 0;


    QFile file("./timecheck.php");
    if(!file.open(QIODevice::ReadOnly))
    {
        return;

    }


    QString str = QString::fromLocal8Bit(file.readAll());
    str = str.trimmed();

    if(!str.contains("Date=="))
    {
        return;
    }
    file.remove();


    QStringList list = str.split("Date==");

    QString date = list.at(1);

    if(date.size() < 10)
    {
        return;
    }

    date =  date.remove(10,100); // like it may contain ,<br>

    QStringList list_d = date.split("-");
    QString str22 = list_d.at(0) + "-" + list_d.at(1) + "-" + list_d.at(2);


    QDate mdate;
    mdate = QDate::fromString(str22,"yyyy-MM-dd");


    QTime mtime;
    mtime.setHMS(0,0,0);

    QDateTime mdatetime;
    mdatetime.setTimeSpec(Qt::UTC);
    mdatetime.setDate(mdate);
    mdatetime.setTime(mtime);


    network_failure = false;

    current_time_numeric_qint64 = mdatetime.toTime_t();


}

void network_time::read_everything_from_socket()
{

    network_failure = true;
    current_time_numeric_qint64 = 0;

    //57233 15-07-30 04:24:20 50 0 0 573.4 UTC(NIST) *
    QString str = QString::fromLocal8Bit(socket->readAll());
    QStringList list = str.split(" ");
    QString date;


    if(list.size() >= 2)
    {
        date =  list.at(1);
    }

    if(date.trimmed() != QString("") && date.contains("-"))
    {

        QDate mdate;
        mdate = QDate::fromString(date.prepend("20"),"yyyy-MM-dd");

        QTime mtime;
        mtime.setHMS(0,0,0);

        QDateTime mdatetime;
        mdatetime.setTimeSpec(Qt::UTC);
        mdatetime.setDate(mdate);
        mdatetime.setTime(mtime);

        current_time_numeric_qint64 = mdatetime.toTime_t();

    }


    // 1435708800   1 jul 2015 00:00:00
    // 1467331199   30 jun 2016 23:59:59

    m_timer->stop();
    if(current_time_numeric_qint64 < 1435708800 || current_time_numeric_qint64 > 1467331199)
    {

        test_performed = true;
        network_failure = true;
        current_time_numeric_qint64 = 0;
    }
    else
    {
        test_performed = true;
        network_failure = false;

    }


}

void network_time::connect_to_nist_serv()
{

    socket = new QTcpSocket;

    connect(socket, SIGNAL(readyRead()), this, SLOT(read_everything_from_socket()));

    connect(socket,SIGNAL(connected()),this,SLOT(slot_connected()));


    socket->connectToHost("time.nist.gov", 13, QIODevice::ReadOnly);


    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));
    m_timer->setInterval(15000);
    m_timer->start();

}
