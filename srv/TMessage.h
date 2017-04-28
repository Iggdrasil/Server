#pragma once
#include "SafeQueue.h"
#include "tcp_connection.h"

class TProcessor;

class TMessage
{
	
protected:

	tcp_connection::pointer _tcpConnPtr;

	TProcessor* _packProcessor;

public:
	TMessage() {}

	TMessage(tcp_connection::pointer tcpConn)
	{
		_tcpConnPtr = tcpConn;
	}

	~TMessage() {};

	void setProcessor(TProcessor* prc)
	{
		_packProcessor = prc;
	}

	TProcessor* getProcessor() 
	{
		return _packProcessor;
	}

	void setTcpConnection(tcp_connection::pointer tcpConn)
	{
		_tcpConnPtr = tcpConn;
	}

	tcp_connection::pointer getTcpConnection()
	{
		return _tcpConnPtr;
	}

};


class TMessageQueue
{
protected:
	safeQueue<TMessage> _messageQueue;

public:
	void enqueue(TMessage msg);
	TMessage dequeue();


};