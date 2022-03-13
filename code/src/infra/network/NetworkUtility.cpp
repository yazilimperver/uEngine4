#include "NetworkUtility.h"
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QTcpSocket>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>

NetworkUtility::NetworkUtility()
{
    mManager = new QNetworkAccessManager(this);
    connect(mManager,SIGNAL(finished(QNetworkReply*)),SLOT(gotReply(QNetworkReply*)));
    mManager->get(QNetworkRequest(QUrl("http://api.ipify.org?format=json")));

    /*
    qDebug() << "Device information:";

    for(auto interface: QNetworkInterface::allInterfaces())
        qDebug() << interface.name() << interface.hardwareAddress();

    for(auto interface:  QNetworkInterface::allInterfaces())
    {
        if(interface.name() == QLatin1String("wlan0"))
        {
            // do something with 'interface.hardwareAddress()'

            break;
        }
    }*/


    // Check if we can obtain a mac address non loop back
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
        {
            if(netInterface.hardwareAddress()!= "")
                mDeviceAddresses.append("<" + netInterface.name()+ "> " + netInterface.hardwareAddress());
        }
    }
}

NetworkUtility::~NetworkUtility()
{
    if(mManager)
        delete mManager;
}

void NetworkUtility::gotReply(QNetworkReply* networkReply)
{
    networkReply->deleteLater();

    if(networkReply->error() != QNetworkReply::NoError)
    {
        //failure
        qDebug() << "error: " << networkReply->error();
    }
    else
    {
        // parse the json reply to extract the IP address
        mPublicIP = QHostAddress(QJsonDocument::fromJson(networkReply->readAll()).object().value("ip").toString()).toString();
        qDebug() << "external ip: " << mPublicIP;

        emit publicIpAddressObtained(mPublicIP);
    }
}

QString NetworkUtility::getExternalIPAddress()
{
    return mPublicIP;
}

QString NetworkUtility::getLocalIPAddress()
{
    QString result;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);

    for (const QHostAddress &address: QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {
            result = address.toString();
            break;
        }
    }

    return result;
}

QVector<QString> NetworkUtility::getDeviceList()
{
    return mDeviceAddresses;
}

QString NetworkUtility::getIpv4Address(const QString ipv6Address)
{
    QString ip4String;
    QHostAddress ip6Address(ipv6Address);
    bool conversionOK = false;

    QHostAddress ip4Address(ip6Address.toIPv4Address(&conversionOK));
    if (conversionOK)
        ip4String = ip4Address.toString();
    else
        ip4String = ipv6Address;

    return ip4String;
}

