#include "ConnectedClient.h"
#include "IServerMedium.h"

#include "Utility/PropertyItem.h"
#include "NetworkUtility/NetworkUtility.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

ConnectedClient::ConnectedClient(uint64_t uniqueId, QTcpSocket*& clientSocket)
    : mUniqueId{uniqueId}
    , mClientSocket{ clientSocket }
{

}

ConnectedClient::~ConnectedClient()
{
    mClientSocket = nullptr;
}

QTcpSocket* ConnectedClient::getUnderlyingSocket()
{
	return mClientSocket;
}

uint64_t ConnectedClient::getClientId()
{
	return mUniqueId;
}

bool ConnectedClient::isActive()
{
	return mClientSocket->isOpen();
}

void ConnectedClient::getClientInformation(std::vector<PropertyItem>& clientInfo)
{
	if (mClientSocket->state() == QAbstractSocket::ConnectedState)
	{
		clientInfo.clear();

		// fill peer data
		clientInfo.push_back(PropertyItem{ cParameter_PeerName, mClientSocket->peerName() });
        clientInfo.push_back(PropertyItem{ cParameter_PeerAddress,
                                           NetworkUtility::getIpv4Address(mClientSocket->peerAddress().toString()) });
		clientInfo.push_back(PropertyItem{ cParameter_PeerPort, mClientSocket->peerPort() });
	}
}

int64_t ConnectedClient::readData(int64_t maxByteCount, int8_t* data)
{
	int64_t size{ -1 };
	
	if (mClientSocket->isOpen())
		size = mClientSocket->read(reinterpret_cast<char*>(data), maxByteCount);

	return size;
}

QByteArray ConnectedClient::readData(int64_t maxByteCount)
{
	return mClientSocket->read(maxByteCount);
}

int64_t ConnectedClient::writeData(const int8_t* data, int64_t maxSize)
{
	if (nullptr != data)
		return mClientSocket->write(reinterpret_cast<const char*>(data), maxSize);
	else
		return -1;
}

int64_t ConnectedClient::writeData(const int8_t* data)
{
	if (nullptr != data)
		return mClientSocket->write(reinterpret_cast<const char*>(data));
	else
		return -1;
}

void ConnectedClient::disconnect()
{
	if (mClientSocket->isOpen())
		mClientSocket->disconnectFromHost();
}

int64_t ConnectedClient::availableDataSize()
{
	int64_t size = 0;
	
	if (mClientSocket->isOpen())
		size = mClientSocket->bytesAvailable();
	
	return size;
}
