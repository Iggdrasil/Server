#pragma once
#include <boost\serialization\singleton.hpp>
#include <boost\asio.hpp>
#include "TMessage.h"

class router_service : public TMessageQueue, boost::serialization::singleton<router_service>
{
	boost::asio::io_service& _srv;

	// Очередь с запросами, ожидающими ответа
	safeQueue<TMessage> _pendingRequests;

	
public:
	router_service(boost::asio::io_service& srv);
	~router_service();

	void svc();
};

