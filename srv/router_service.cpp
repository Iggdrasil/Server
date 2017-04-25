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

bool router_service::preprocess(TClientMessage* msg)
{
	request req;
	std::array<char, NET_PARAMS::NetworkBufferSize> buf;
	msg->getBuffer(buf);
	boost::tribool res;
	boost::tie(res, boost::tuples::ignore) = rparser.parse(req, buf.begin(), buf.begin() + msg->getBufferLen());

	if ( !res )
	{
		return false;
	}
	msg->setProcessor(&_proxyProc);
	return true;
	

}

void router_service::svc()
{

	while (true)
	{
		while (!_q.empty())
		{
			TClientMessage* msg = &_q.front();
			if (preprocess(msg))
			{
				msg->getProcessor()->Process(msg);
			}
			
			_q.pop();
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
	}
}
