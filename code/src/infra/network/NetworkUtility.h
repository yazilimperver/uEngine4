/*!
 * @file	NetworkUtility.h.
 * @date	12.01.2021
 * @author	Yazilimperver
 * @brief	
 * @remark	Copyright (c) 2021, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once
#include <QObject>
#include <QString>

#include <QNetworkAccessManager>

/*!
 * @class	NetworkUtility
 *
 * @brief	Ag alt yapisi ile ilgili temel bir tak�m servisler sunan s�n�ft�r.
 */
class NetworkUtility
        : public QObject
{
    Q_OBJECT
public:
    /*! @brief	Default constructor */
    NetworkUtility();
    
    /*! @brief	Destructor */
    ~NetworkUtility();

    /*!
     * @brief	�zerinde ko�an bilgisayar�n internet taraf�na a��lan IP adresini d�ner
     *
     * @returns	D�� IP adresi
     */
    QString getExternalIPAddress();

    /*!
     * @brief	�zerinde ko�ulan bilgisayar�n yerel IP adresini d�ner
     *
     * @returns	The local IP address.
     */
    QString getLocalIPAddress();

    /*!
     * @brief	Haberle�me cihazlar�n�n listesini d�n
     *
     * @returns	The device list.
     */
    QVector<QString> getDeviceList();

    /*!
     * @brief	Girdi olarak verilen IPv6 adresini IPv4 adresine d�n��t�r�r
     *
     * @param 	ipv6Address	The IPv6 address.
     *
     * @returns	The IPv4 address.
     */
    static QString getIpv4Address(const QString ipv6Address);
signals:
    void publicIpAddressObtained(QString ipAddress);

private slots:
    void gotReply(QNetworkReply* networkReply);

private:
    /*! @brief	Yerel IP adresi */
    QString mPublicIP;

    /*! @brief	Gerekli bilgiler i�in kullan�lacak s�n�f */
    QNetworkAccessManager* mManager;
	
    /*! @brief	Cihaz adresleri */
    QVector<QString> mDeviceAddresses;
};
