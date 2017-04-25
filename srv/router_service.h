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

	// Очередь с запросами, ожидающими ответа
	safeQueue<TClientMessage> _pendingRequests;

	// Обработчик запросов прокси
	//TProcessor::pProcessor _proxyProc;
	ProxyProcessor _proxyProc;

	// Парсер заголовка HTTP
	// TODO переделать под указатель на абстрактный класс,
	// чтоб можно было настраивать парсер
	request_parser rparser;

	// Парсит заголовок и определяет какой процессор надо использовать для обработки сообщения
	bool preprocess(TClientMessage* msg);

public:
	router_service(boost::asio::io_service& srv);
	~router_service();

	void svc();
};

