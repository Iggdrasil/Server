#pragma once
#include <boost\serialization\singleton.hpp>
#include <boost\asio.hpp>
#include "SafeQueue.h"
#include "TProxyProcessor.h"
#include "TClientMessage.h"
#include "request_parser.h"

class router_service : public safeQueue<TClientMessage>, boost::serialization::singleton<router_service>
{
	boost::asio::io_service& _srv;

	// ������� � ���������, ���������� ������
	safeQueue<TClientMessage> _pendingRequests;

	// ���������� �������� ������
	//TProcessor::pProcessor _proxyProc;
	ProxyProcessor _proxyProc;

	// ������ ��������� HTTP
	// TODO ���������� ��� ��������� �� ����������� �����,
	// ���� ����� ���� ����������� ������
	request_parser rparser;

	// ������ ��������� � ���������� ����� ��������� ���� ������������ ��� ��������� ���������
	bool preprocess(TClientMessage* msg);

public:
	router_service(boost::asio::io_service& srv);
	~router_service();

	void svc();
};

