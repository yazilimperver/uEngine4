#pragma once

#include "IPeerMedium.h"
#include <QUdpSocket>
#include "Utility/ParameterSet.h"

/*! @brief	A UDP Peer. */
class UDPPeer
    : public QObject, public IPeerMedium
{
    Q_OBJECT
public:
    UDPPeer();
    void assignParameters(const ParameterSet &parameters) override;
	bool initialize() override;
    void finalize() override;
    bool isInitialized() override;
    bool isHostSet() override;
    bool isActive() override;
    int64_t availableDataSize() override;
    int64_t readData(int64_t maxByteCount, int8_t *data, QString *address, uint16_t *port) override;
    QByteArray readData(int64_t maxByteCount, QString *address, uint16_t *port) override;
    int64_t writeData(const QByteArray& data, const QString& address, uint16_t& port) override;
    int64_t writeData(const int8_t *data, int64_t maxSize) override;
    int64_t writeData(const QByteArray &data) override;
    QString getHostData();

/*! @brief	Connected this object */
signals:

    /*!
     * @brief	The signal is emitted when any kind of error is occurred
     *
     * @param	errorCode	The occurred error code.
     */
    void socketErrorOccurred(int32_t errorCode);

    /*! @brief	There is data that need to be processed */
    void dataReadyToRead();

private slots:
    void dataArrived();
    void errorOccurred(QAbstractSocket::SocketError socketError);

protected:

    /*! @brief	Initialization statuses */
    bool mIsListenInitialized{ false };

    /*! @brief	Underlying UDP socket */
    QUdpSocket mUdpSocket;

    /*!
     * @brief	The parameters that will be used for socket creation/bind and connection to target
     * 			host Note that QT dynamic properties can also be used for this purpose
     */
    ParameterSet mParameters;

    /*! @brief	For UDP case we will keep host data as member for quick reference */
    bool mIsHostSet{false};

	/*! @brief	Host address that will be used for consequtive socket calls */
    QHostAddress mHostAddress;

	/*! @brief	Host port for connection */
	uint16_t mHostPort{0};
};

