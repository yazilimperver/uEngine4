#include "TCPClient.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

TCPClient::TCPClient()
	: mTcpSocket{this}
{
	QObject::connect(&mTcpSocket, &QTcpSocket::connected, this, &TCPClient::clientConnected);
	QObject::connect(&mTcpSocket, &QTcpSocket::disconnected, this, &TCPClient::clientDisconnected);
	QObject::connect(&mTcpSocket, &QIODevice::readyRead, this, &TCPClient::dataArrived);

	QObject::connect(&mTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorOccurred(QAbstractSocket::SocketError)));
}

void TCPClient::assignParameters(const ParameterSet& parameters)
{
	mParameters = parameters;
}

bool TCPClient::initialize()
{
	mIsInitialized = false;

	// 0) Check the list of parameters to see if required parameters are provided
    if (true == mParameters.hasParameter(cParameter_HostAddress) ||
		true == mParameters.hasParameter(cParameter_HostPort))
	{
		mIsInitialized = true;

		// If so check if we required to bind given port and address
		std::string localHost{ "127.0.0.1" };
        uint16_t portNo{ 15000 };

		bool hasLocalPort = mParameters.hasParameter(cParameter_LocalPort);
		bool hasLocalAddress = mParameters.hasParameter(cParameter_LocalAddress);

		if (false == hasLocalAddress && true == hasLocalPort)
		{
            mParameters.getParameterValue<uint16_t >(cParameter_LocalPort, portNo);
			mIsInitialized = mTcpSocket.bind(portNo);
		}
		else if (true == hasLocalAddress && true == hasLocalPort)
		{
            mParameters.getParameterValue<uint16_t>(cParameter_LocalPort, portNo);
			mParameters.getParameterValue<std::string>(cParameter_LocalAddress, localHost);
			mIsInitialized = mTcpSocket.bind(QHostAddress(localHost.c_str()), portNo);
		}
		else
		{
			// Random port is used
			mIsInitialized = mTcpSocket.bind();

			// Store local port
            mParameters.updateParameterValue(cParameter_LocalPort, static_cast<uint16_t>(mTcpSocket.localPort()));
		}
	}	

	return mIsInitialized;
}

void TCPClient::finalize()
{
	// Close socket if not already
	if (true == this->isConnected())
		mTcpSocket.disconnectFromHost();
}

bool TCPClient::isInitialized()
{
	return mIsInitialized;
}

bool TCPClient::isActive()
{
	return this->isConnected();
}

int64_t TCPClient::readData(int64_t maxByteCount, int8_t* data)
{
	if (nullptr != data)
		return mTcpSocket.read(reinterpret_cast<char*>(data), maxByteCount);
	else
		return -1;
}

QByteArray TCPClient::readData(int64_t maxByteCount)
{
	return mTcpSocket.read(maxByteCount);
}

int64_t TCPClient::writeData(const int8_t* data, int64_t maxSize)
{
	if (nullptr != data)
		return mTcpSocket.write(reinterpret_cast<const char*>(data), maxSize);
	else
		return -1;
}

int64_t TCPClient::writeData(const int8_t* data)
{
	if (nullptr != data)
		return mTcpSocket.write(reinterpret_cast<const char*>(data));
	else
		return -1;
}

int64_t TCPClient::writeData(const QByteArray& data)
{
	return mTcpSocket.write(data);
}

void TCPClient::connect()
{
	if (true == this->isConnected())
		mTcpSocket.disconnectFromHost();

    uint16_t destPort { 0 };
	std::string destAddr;

    if (true == mParameters.getParameterValue<uint16_t>(cParameter_HostPort, destPort)
		&&
		true == mParameters.getParameterValue<std::string>(cParameter_HostAddress, destAddr))
		mTcpSocket.connectToHost(destAddr.c_str(), destPort);
}

void TCPClient::disconnect()
{
	if (true == this->isConnected())
	{
		mTcpSocket.close();
	}
}

bool TCPClient::isConnected()
{
	return mTcpSocket.state() == QTcpSocket::ConnectedState;
}

void TCPClient::getPeerInformation(std::vector<PropertyItem>& peerInfo)
{
	if (true == this->isConnected())
	{
		peerInfo.clear();

		// fill peer data
		peerInfo.push_back(PropertyItem{ IClientMedium::cParameter_PeerName, mTcpSocket.peerName() });
		peerInfo.push_back(PropertyItem{ IClientMedium::cParameter_PeerAddress, mTcpSocket.peerAddress() });
		peerInfo.push_back(PropertyItem{ IClientMedium::cParameter_PeerPort, mTcpSocket.peerPort() });
	}
}

int64_t TCPClient::availableDataSize()
{
	return mTcpSocket.bytesAvailable();
}

void TCPClient::clientConnected()
{
    qDebug() << "[QTCPClient] Client is connected!" << '\n';

	emit connected();
}

void TCPClient::clientDisconnected()
{
    qDebug() << "[QTCPClient] Client is disconnected!" << '\n';

	emit disconnected();
}

void TCPClient::dataArrived()
{
    qDebug() << "[QTCPClient] Data ready for read!" << '\n';

	emit dataReadyToRead();
}

void TCPClient::errorOccurred(QAbstractSocket::SocketError socketError)
{
	switch (socketError) 
	{
	case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "[QTCPClient] Error: Remote host is closed!" << '\n';
		break;
	case QAbstractSocket::HostNotFoundError:
        qDebug() << "[QTCPClient] Error: The host was not found.Please check the host name and port settings." << '\n';
		break;
	case QAbstractSocket::ConnectionRefusedError:

        qDebug() << "[QTCPClient] Error: The connection was refused by the peer. Make sure the server is running, and check that the host name and port settings are correct." << '\n';
		break;
	default:
        qDebug() << "[QTCPClient] Error: " << mTcpSocket.errorString().data() << '\n';
	}
	
	emit socketErrorOccurred(static_cast<int32_t>(socketError));
}
