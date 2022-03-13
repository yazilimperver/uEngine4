/**
 * \file    ConnectedClient.h
 * \date    2019/06/07
 * \author  yazilimperver
 * \brief   
 * Copyright © 2019, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include "IConnectedClient.h"

class QTcpSocket;

class ConnectedClient
	: public IConnectedClient
{
public:
	/// <summary>
	/// The constructor that takes underlying socket
	/// </summary>
	/// <param name="uniqueId">The unique id that will be used to identify this sockets</param>
	/// <param name="clientSocket">The socket that this interface manage</param>
    ConnectedClient(uint64_t uniqueId, QTcpSocket*& clientSocket);

	/// <summary>
	/// Returns the underlying socket
	/// </summary>
	/// <returns>Underlying socket</returns>
	QTcpSocket* getUnderlyingSocket();

	/// <summary>
	/// Returns the unique id associated with this client
	/// </summary>
	/// <returns>-1 if no socket associated ow unique id</returns>
    virtual uint64_t getClientId() override;

	/// <summary>
	/// Is this client still connected
	/// </summary>
	/// <returns>The client socket connection status</returns>
	virtual bool isActive() override;

	/// <summary>
	/// Return the information related with this client (address, port, name)
	/// </summary>
	/// <param name="clientInfo">The list of parameters</param>
	virtual void getClientInformation(std::vector<PropertyItem>& clientInfo) override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="maxByteCount"></param>
	/// <param name="data"></param>
	/// <returns></returns>
    virtual int64_t  readData(int64_t maxByteCount, int8_t* data) override;
    virtual QByteArray readData(int64_t maxByteCount) override;
    virtual int64_t writeData(const int8_t* data, int64_t maxSize) override;
    virtual int64_t writeData(const int8_t* data) override;
	virtual void disconnect() override;

	/// <summary>
	/// Available data size
	/// </summary>
	/// <returns>@returns	An int64_t.</returns>
    virtual int64_t availableDataSize() override;

    virtual ~ConnectedClient();
protected:
	/// <summary>
	/// The unique identifier
	/// </summary>
    uint64_t mUniqueId{ 0 };

	/// <summary>
	/// Underlying socket
	/// </summary>
	QTcpSocket* mClientSocket{ nullptr };
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
