#include "stdafx.h"
#include "router_service.h"
#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "TMessage.h"
#include "HttpRequest.h"

using std::cout;
using std::endl;

bool router_service::Preprocess(TMessage * msg)
{
	boost::tribool res;
	boost::tie(res, boost::tuples::ignore) = _httpHParser.parse(msg->_httpRequest, msg->getBufferBegin(), msg->getBufferBegin() + msg->getCurrentSize());
	if (res)
	{
		msg->setProcessor(&_proxyProcessor);
		return true;
	}
	return false;
}

router_service::router_service(boost::asio::io_service& srv)
	:_srv(srv), _proxyProcessor(srv)
{

}


router_service::~router_service()
{
}



void router_service::svc()
{

	while (true)
	{
		// Обработка очереди ожидающих


		// Обработка очереди входящих
		while (!_messageQueue.empty())
		{
			// Извлекаем сообщение из очереди
			TMessage* msg = _messageQueue.pop();
			if (!Preprocess(msg))
			{
				// TODO подумать надо ли удалять сообщение тут
				continue;
			}

			msg->getProcessor()->Process(msg);
			
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
	}
}
