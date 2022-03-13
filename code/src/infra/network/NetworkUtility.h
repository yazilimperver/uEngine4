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
 * @brief	Ag alt yapisi ile ilgili temel bir takým servisler sunan sýnýftýr.
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
     * @brief	Üzerinde koþan bilgisayarýn internet tarafýna açýlan IP adresini döner
     *
     * @returns	Dýþ IP adresi
     */
    QString getExternalIPAddress();

    /*!
     * @brief	Üzerinde koþulan bilgisayarýn yerel IP adresini döner
     *
     * @returns	The local IP address.
     */
    QString getLocalIPAddress();

    /*!
     * @brief	Haberleþme cihazlarýnýn listesini dön
     *
     * @returns	The device list.
     */
    QVector<QString> getDeviceList();

    /*!
     * @brief	Girdi olarak verilen IPv6 adresini IPv4 adresine dönüþtürür
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

    /*! @brief	Gerekli bilgiler için kullanýlacak sýnýf */
    QNetworkAccessManager* mManager;
	
    /*! @brief	Cihaz adresleri */
    QVector<QString> mDeviceAddresses;
};
