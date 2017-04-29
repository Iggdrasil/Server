#pragma once
#include <boost\serialization\singleton.hpp>
#include <boost\asio.hpp>
#include "TMessage.h"
#include "HttpHeaderParser.h"
#include "TProxyProcessor.h"


class router_service : public TMessageQueue, boost::serialization::singleton<router_service>
{
	boost::asio::io_service& _srv;

	// Очередь с запросами, ожидающими ответа
	TMessageQueue _pendingRequests;

	HttpHeaderParser _httpHParser;

	ProxyProcessor _proxyProcessor;
	
private:

	// Определяем тип сообщения и устанавливаем процессор
	bool Preprocess(TMessage* msg);

public:
	router_service(boost::asio::io_service& srv);
	~router_service();

	void svc();
};

