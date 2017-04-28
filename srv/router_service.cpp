#include "stdafx.h"
#include "router_service.h"
#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "request.h"

using std::cout;
using std::endl;

router_service::router_service(boost::asio::io_service& srv)
	:_srv(srv)
{
}


router_service::~router_service()
{
}



void router_service::svc()
{

	while (true)
	{
		while (!_messageQueue.empty())
		{
			
			_messageQueue.pop();
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
	}
}
