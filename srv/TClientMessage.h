#pragma once
#include "TMessage.h"
class TClientMessage :
	public TMessage
{


public:
	TClientMessage(tcp_connection::pointer tcpConn);
	~TClientMessage();

	void setProcessor(TProcessor::pProcessor proc);
	TProcessor::pProcessor getProcessor();
	void setTcpConnection(tcp_connection::pointer tcpConn);
	tcp_connection::pointer getTcpConnection();

	void getBuffer(std::array<char, NET_PARAMS::NetworkBufferSize>& buf) const;
	size_t getBufferLen() const;

};

