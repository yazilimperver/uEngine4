#include "TCPServer.h"
#include "ConnectedClient.h"
#include "Utility/PropertyItem.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

TCPServer::TCPServer()
{
    mTCPServer = new QTcpServer();
	mIsInitialized = false;
}

void TCPServer::assignParameters(const ParameterSet& parameters)
{
	mParameters = parameters;
}

bool TCPServer::initialize()
{
	if (false == mIsInitialized)
	{
		qDebug() << "[QTCPServer] Initialization is started!";

		// 0) Check first of all pending connection parameter is provided
		if (true == mParameters.hasParameter(cIServerMedium_Parameter_MaxPendingConnections))
		{
			int32_t maxPendingConnections{ 0 };
			mParameters.getParameterValue<int32_t>(cIServerMedium_Parameter_MaxPendingConnections, maxPendingConnections);

			mTCPServer->setMaxPendingConnections(maxPendingConnections);
		}

		// 1) Check the list of parameters to see if required parameters are provided
		bool hasLocalPort = mParameters.hasParameter(cIServerMedium_Parameter_LocalPort);
		bool hasLocalAddress = mParameters.hasParameter(cIServerMedium_Parameter_LocalAddress);

		if (false == hasLocalAddress && true == hasLocalPort)
		{
			mIsInitialized = true;
			mParameters.getParameterValue<uint16_t>(cIServerMedium_Parameter_LocalPort, mListeningPort);
		}
		else if (true == hasLocalAddress && true == hasLocalPort)
		{
			mIsInitialized = true;
			mParameters.getParameterValue<uint16_t>(cIServerMedium_Parameter_LocalPort, mListeningPort);
			mParameters.getParameterValue<std::string>(cIServerMedium_Parameter_LocalAddress, mLocalAddress);
		}
		else
		{
			qDebug() << "[QTCPServer] Did you pass comm parameters to TCP Server!";
		}


		// Server signal slots
		connect(mTCPServer, &QTcpServer::newConnection, this, &TCPServer::newConnection);
		connect(mTCPServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(acceptErrorOccurred(QAbstractSocket::SocketError)));

		if (false == mIsInitialized)
			qDebug() << "[QTCPServer] Initialization is failed!";
		else
			qDebug() << "[QTCPServer] Initialization is successful!";
	}
	else
	{
		qDebug() << "[QTCPServer] Already initialized!";
	}

	return mIsInitialized;
}

void TCPServer::finalize()
{
	// Close socket if not already
    if (mTCPServer->isListening())
	{
        mTCPServer->disconnect();
        mTCPServer->close();
	}
}

bool TCPServer::isInitialized()
{
	return mIsInitialized;
}

void TCPServer::startListening()
{
	if ((true == mIsInitialized) && (false == mTCPServer->isListening()))
	{
		if (false == mTCPServer->listen(QHostAddress::Any, mListeningPort))
		{
			qDebug() << "[QTCPServer] Listen initiation failed!!";
		}
		else
		{
			qDebug() << "[QTCPServer] Server started to listen port: " << mListeningPort;
		}
	}
	else
		qDebug() << "[QTCPServer] Already listening!";
}

void TCPServer::stopListening()
{
    if (mTCPServer->isListening())
	{
		// disconnect each client
		for (auto& client : mClientMapping)
		{
			// inform listeners
			emit clientDisconnected(client.first);

			// disconnect all slots
			client.second->getUnderlyingSocket()->disconnect();

			// disconnect
			client.second->disconnect();

			// remove client
			delete client.second;
		}

		mClientIdMapping.clear();
		mClientMapping.clear();

        mTCPServer->disconnect();
        mTCPServer->close();
	}
}

bool TCPServer::isListening()
{
    return mTCPServer->isListening();
}

void TCPServer::disconnectClient(uint64_t clientId)
{
	if (auto itr = mClientMapping.find(clientId); itr != mClientMapping.end())
	{
		// disconnect all slots
		itr->second->getUnderlyingSocket()->disconnect();

		// disconnect from client
		itr->second->disconnect();

		this->removeClient(clientId);
	}
}

bool TCPServer::isConnected(uint64_t clientId)
{
	bool isConnected{ false };
	
	if (auto itr = mClientMapping.find(clientId); itr != mClientMapping.end())
		isConnected = itr->second->isActive();

	return isConnected;
}

void TCPServer::getClientInformation(uint64_t clientId, std::vector<PropertyItem>& clientInfo)
{
	if (auto itr = mClientMapping.find(clientId); itr != mClientMapping.end())
		itr->second->getClientInformation(clientInfo);
}

IConnectedClient* TCPServer::getConnectedClientInterface(uint64_t clientId)
{
	IConnectedClient* result{ nullptr };

	if (auto itr = mClientMapping.find(clientId); itr != mClientMapping.end())
		result = itr->second;

	return result;
}

void TCPServer::getConnectedClientList(std::vector<uint64_t>& clientIdList)
{
	clientIdList.clear();

	for (auto& [clientId, connectedClient] : mClientMapping)
		clientIdList.push_back(clientId);
}

void TCPServer::newConnection()
{
	// Traverse all new pending connections
    while (mTCPServer->hasPendingConnections())
	{
        auto newConn = mTCPServer->nextPendingConnection();

        emit newClient();

        uint64_t currentId = mClientSeedId;
        qDebug() << "[QTCPServer] A new client <Id:" << currentId << "> is connected!";

		mClientIdMapping[newConn] = currentId;
		mClientMapping[currentId] = new ConnectedClient(currentId, newConn);

		// add new signal/slot for newly connected client
		connect(newConn, &QIODevice::readyRead, [=] {clientDataReadyToRead(currentId); });
		connect(newConn, &QAbstractSocket::disconnected, [=] {clientDisconnectedSlot(currentId); });
        connect(newConn, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
                this, &TCPServer::socketErrorOccurred);

		mClientSeedId++;

		// Inform listeners
        emit newTCPClientConnected(currentId);
	}
}

void TCPServer::clientDisconnectedSlot(uint64_t clientId)
{
	// inform listeners
	emit clientDisconnected(clientId);
	
	if (mClientMapping.size() > 0)
	{
		// disconnect all slots
		mClientMapping[clientId]->getUnderlyingSocket()->disconnect();

		// remove corresponding entries
		this->removeClient(clientId);
	}
}

void TCPServer::removeClient(uint64_t clientId)
{
	if (auto clientIdItr = mClientMapping.find(clientId); clientIdItr != mClientMapping.end())
	{
		ConnectedClient* connClientInst = mClientMapping[clientId];

		// remove client id mapping item
		mClientIdMapping.erase(connClientInst->getUnderlyingSocket());
		
		delete mClientMapping[clientId];
		mClientMapping.erase(clientId);
	}
}

void TCPServer::socketErrorOccurred(QAbstractSocket::SocketError socketError)
{
	QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

	if (nullptr != socket)
	{
		if (auto clientIdItr = mClientIdMapping.find(socket); clientIdItr != mClientIdMapping.end())
		{
			uint64_t clientId = clientIdItr->second;

			switch (socketError)
			{
			case QAbstractSocket::RemoteHostClosedError:
			{
                qDebug() << "[QTCPServer] Client with given ID: " << clientId << " is disconnected!";
			}
			break;
			default:
                qDebug() << "[QTCPServer] Client Error: " << socket->errorString().data();
			}

			emit clientErrorOccurred(clientId, static_cast<int32_t>(socketError));
		}
		else
            qDebug() << "[QTCPServer] Given client not found in currently connected client list!";
	}
}

void TCPServer::acceptErrorOccurred(QAbstractSocket::SocketError socketError)
{
    qDebug() << "[QTCPServer] Server Accept Error!Error Code: " << socketError << " Error Str: " << mTCPServer->errorString().data();
}
