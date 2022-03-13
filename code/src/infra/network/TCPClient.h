#pragma once

#include "IClientMedium.h"
#include "Utility/ParameterSet.h"

#include <qtcpsocket.h>

/*! @brief	A qtcp client. */
class TCPClient
	: public QObject, public IClientMedium
{
	Q_OBJECT
public:

	/*! @brief	Constructor for TCP client */
	TCPClient();

	/*!
	 * @brief	Each communication medium configuration parameters should be passed via this API. The
	 * 			list of parameters are dictated/known by communication medium itself
	 *
	 * @param	parameters	The parameter mapping (name/value)
	 */
	virtual void assignParameters(const ParameterSet& parameters) override;

	/*!
	 * @brief	Perform initialization activities required for given medium (bind etc for client
	 * 			sockets)
	 *
	 * @returns	The result of initialization.
	 */
	virtual bool initialize() override;

	/*! @brief	Perform destruction and close activities required for given medium */
	virtual void finalize() override;

	/*!
	 * @brief	Is communication medium initialized properly
	 *
	 * @returns	Initialization status.
	 */
	virtual bool isInitialized() override;

	/*!
	 * @brief	Is communication medium ready for communication
	 *
	 * @returns	true => can be used for that purpose, false => not ready.
	 */
	virtual bool isActive() override;

	/*!
	 * @brief	Data APIs
	 *
	 * @param 		  	maxByteCount	Number of maximum bytes.
	 * @param [in,out]	data			If non-null, the data.
	 *
	 * @returns	The data.
	 */
	virtual int64_t readData(int64_t maxByteCount, int8_t* data) override;
	virtual QByteArray readData(int64_t maxByteCount) override;
	virtual int64_t writeData(const int8_t* data, int64_t maxSize) override;
	virtual int64_t writeData(const QByteArray& data) override;
	virtual int64_t writeData(const int8_t* data) override;

	/*!
	 * @brief	To connect given destination with respect to provided parameters The medium should be
	 * 			initialized beforehand
	 */
	virtual void connect() override;

	/*! @brief	Disconnect from destination */
	virtual void disconnect() override;

	/*!
	 * @brief	Is medium connected
	 *
	 * @returns	Connection status.
	 */
	virtual bool isConnected() override;

	/*!
	 * @brief	Returns the information about other end point
	 *
	 * @param [in,out]	peerInfo	End point information.
	 */
	virtual void getPeerInformation(std::vector<PropertyItem>& peerInfo) override;


	/*!
	 * @brief	Available data size
	 *
	 * @returns	An int64_t.
	 */
	virtual int64_t availableDataSize() override;

signals:
	/*! @brief	The signal is emitted when current client is connected */
	void connected();

	/*! @brief	The signal is emitted when current client is disconnected */
	void disconnected();

	/*!
	 * @brief	The signal is emitted when any kind of error is occurred
	 *
	 * @param	errorCode	The occurred error.
	 */
	void socketErrorOccurred(int32_t errorCode);

	/*! @brief	There is data that need to be processed */
	void dataReadyToRead();

private slots:
	void clientConnected();
	void clientDisconnected();
	void dataArrived();
	void errorOccurred(QAbstractSocket::SocketError socketError);
protected:

	/*! @brief	Initialization status */
	bool mIsInitialized{ false };

	/*! @brief	Underlying TCP client socket */
	QTcpSocket mTcpSocket;

	/*!
	 * @brief	The parameters that will be used for socket creation/bind and connection to target
	 * 			host Note that QT dynamic properties can also be used for this purpose
	 */
	ParameterSet mParameters;
};


/*
  Copyright (c) [2019][Yazilimperver <yazilimpervergs@gmail.com>]
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
