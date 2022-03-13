#include "UDPPeer.h"
#include "NetworkUtility/NetworkUtility.h"

UDPPeer::UDPPeer()
    : mUdpSocket{this}
{
    QObject::connect(&mUdpSocket, &QIODevice::readyRead, this, &UDPPeer::dataArrived);
    QObject::connect(&mUdpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorOccurred(QAbstractSocket::SocketError)));
}

void UDPPeer::assignParameters(const ParameterSet &parameters)
{
    mParameters = parameters;
}

bool UDPPeer::initialize()
{
	// First of all check host settings
	bool hasHostPort = mParameters.hasParameter(cParameter_HostPort);
	bool hasHostAddress = mParameters.hasParameter(cParameter_HostAddress);
	
	if (true == hasHostAddress)
	{
		std::string hostAddress;
		mParameters.getParameterValue<std::string>(cParameter_HostAddress, hostAddress);
		mHostAddress = QHostAddress(QString(hostAddress.c_str()));

		qDebug() << "[UDPPeer] Host Address: " << hostAddress.c_str();
	}

	if (true == hasHostPort)
	{
		mParameters.getParameterValue<uint16_t>(cParameter_HostPort, mHostPort);

		qDebug() << "[UDPPeer] Host Port: " << mHostPort;
	}

	if (true == hasHostPort &&
		true == hasHostAddress)
	{
		mIsHostSet = true;
	}

	// already binded so first close than rebind
	if (true == mIsListenInitialized)
	{
		mUdpSocket.close();
		mIsListenInitialized = false;
	}

	// Check the list of parameters to see if required parameters are provided
	if (true == mParameters.hasParameter(cParameter_LocalPort))
	{
		mIsListenInitialized = true;

		// If so check if we required to bind given port and address
		uint16_t portNo{ 15000 };

		mParameters.getParameterValue<uint16_t>(cParameter_LocalPort, portNo);
		mIsListenInitialized = mUdpSocket.bind(QHostAddress::Any, portNo);

		qDebug() << "[UDPPeer] Local port: " << portNo;
	}

	// We are expecting UDP connection to initialize at least for one role
	return (mIsListenInitialized || mIsHostSet);
}

void UDPPeer::finalize()
{
    // Close socket if not already
    mUdpSocket.close();
}

bool UDPPeer::isInitialized()
{
    // We are expecting UDP connection to initialize at least for one role
    return (mIsListenInitialized || mIsHostSet);
}

bool UDPPeer::isHostSet()
{
    return mIsHostSet;
}

bool UDPPeer::isActive()
{
    return mUdpSocket.isOpen();
}

int64_t UDPPeer::availableDataSize()
{
    return mUdpSocket.bytesAvailable();
}

int64_t UDPPeer::readData(int64_t maxByteCount, int8_t* data, QString* address, uint16_t* port)
{
    QHostAddress sender;
    int64_t size = -1;

    if (nullptr != data &&
        nullptr != address &&
        nullptr != port)
        size = mUdpSocket.readDatagram(reinterpret_cast<char*>(data), maxByteCount, &sender, port);

    *address = NetworkUtility::getIpv4Address(sender.toString());

    return size;
}

QByteArray UDPPeer::readData(int64_t maxByteCount, QString* address, uint16_t* port)
{
    QByteArray buffer;
    buffer.resize(mUdpSocket.pendingDatagramSize());

    QHostAddress sender;

    if (nullptr != address &&
        nullptr != port)
        mUdpSocket.readDatagram(buffer.data(), maxByteCount, &sender, port);

    *address = NetworkUtility::getIpv4Address(sender.toString());

    return buffer;
}

int64_t UDPPeer::writeData(const QByteArray& data, const QString& address, uint16_t& port)
{
    // Here we need to check if a destination host is already set or not if so use it if not return error
    return mUdpSocket.writeDatagram(data, QHostAddress{ address }, port);
}

int64_t UDPPeer::writeData(const int8_t* data, int64_t maxSize)
{
    // Here we need to check if a destination host is already set or not if so use it if not return error
    if (nullptr != data && true == mIsHostSet)
        return mUdpSocket.writeDatagram(reinterpret_cast<const char*>(data), maxSize, mHostAddress, mHostPort);
    else
        return -1;
}

int64_t UDPPeer::writeData(const QByteArray& data)
{
    // Here we need to check if a destination host is already set or not if so use it if not return error
    if (true == mIsHostSet)
        return mUdpSocket.writeDatagram(data, mHostAddress, mHostPort);
    else
        return -1;
}

QString UDPPeer::getHostData()
{
    return QString(mHostAddress.toString() + ":" + QString::number(mHostPort));
}

void UDPPeer::dataArrived()
{
    emit dataReadyToRead();
}

void UDPPeer::errorOccurred(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "[QUDPPeer] Error: Remote host is closed!";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "[QUDPPeer] Error: The host was not found.Please check the host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        // Bu hatayi UDP soket icin goz ardi edecegiz
        //qDebug() << "[QUDPPeer] Error: The connection was refused by the peer. Make sure the server is running, and check that the host name and port settings are correct.";
        return;
    default:
        qDebug() << "[QUDPPeer] Error: " << mUdpSocket.errorString().data();
    }

    emit socketErrorOccurred(static_cast<int32_t>(socketError));

}