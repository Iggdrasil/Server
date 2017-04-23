#pragma once
#include "tcp_connection.h"
#include "TProcessor.h"


// ��������� ���������
class TMessage
{
	
protected:
	// ��� ���������� �� ������ ���� ����������� ���������
	tcp_connection::pointer _tcpConnPtr;

	TProcessor::pProcessor _packProcessor;

public:
	TMessage(){}

	virtual ~TMessage(){}

	virtual void setProcessor(TProcessor::pProcessor) = 0;
	virtual TProcessor::pProcessor getProcessor() = 0;
	virtual void setTcpConnection(tcp_connection::pointer) = 0;
	virtual tcp_connection::pointer getTcpConnection() = 0;

	virtual void getBuffer(std::array<char, NET_PARAMS::NetworkBufferSize>&) const = 0;

};

