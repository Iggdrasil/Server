#pragma once
#include <boost\serialization\singleton.hpp>
#include <boost\asio.hpp>
#include "SafeQueue.h"
#include "TProxyProcessor.h"
#include "TClientMessage.h"


class router_service : public safeQueue<TClientMessage>, boost::serialization::singleton<router_service>
{
	boost::asio::io_service& _srv;

	safeQueue<TClientMessage> _pendingRequests;

	TProcessor::pProcessor _proxyProc;

	PACKET_PARAMS::PACKET_TYPE checkType(const TClientMessage& msg);

	void Init();
public:
	router_service(boost::asio::io_service& srv);
	~router_service();

	void svc();
};

