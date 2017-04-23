#include "stdafx.h"
#include "TClientMessage.h"


TClientMessage::TClientMessage(tcp_connection::pointer tcpConn)
{
	_tcpConnPtr = tcpConn;
}

void TClientMessage::setProcessor(TProcessor::pProcessor proc)
{
	_packProcessor = proc;
}

TProcessor::pProcessor TClientMessage::getProcessor()
{
	return _packProcessor;
}

void TClientMessage::setTcpConnection(tcp_connection::pointer tcpConn)
{
	_tcpConnPtr = tcpConn;
}

tcp_connection::pointer TClientMessage::getTcpConnection()
{
	return _tcpConnPtr;
}

void TClientMessage::getBuffer(std::array<char, NET_PARAMS::NetworkBufferSize>& buf) const
{
	_tcpConnPtr->getBuffer(buf);
}

size_t TClientMessage::getBufferLen() const
{
	return _tcpConnPtr->getBufferLen();
}


TClientMessage::~TClientMessage()
{
}
