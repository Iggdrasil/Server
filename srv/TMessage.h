#pragma once
#include "tcp_connection.h"
#include "TProcessor.h"


// Интерфейс сообщения
class TMessage
{
	
protected:
	// без соединения не можеть быть клиентского сообщения
	tcp_connection::pointer _tcpConnPtr;

	TProcessor* _packProcessor;

public:
	TMessage() {}

	virtual ~TMessage() {};

	virtual void setProcessor(TProcessor* prc) = 0;
	virtual TProcessor* getProcessor() = 0;
	virtual void setTcpConnection(tcp_connection::pointer) = 0;
	virtual tcp_connection::pointer getTcpConnection() = 0;

	virtual void getBuffer(std::array<char, NET_PARAMS::NetworkBufferSize>&) const = 0;

};

