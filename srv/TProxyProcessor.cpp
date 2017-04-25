#include "stdafx.h"
#include "TProxyProcessor.h"
#include "NetParams.h"
#include "TClientMessage.h"


ProxyProcessor::ProxyProcessor()
{
}


ProxyProcessor::~ProxyProcessor()
{
}

bool ProxyProcessor::Process(TMessage* msg)
{
	//std::array<char, NET_PARAMS::NetworkBufferSize> buff;
	//msg->getBuffer(buff);
	//dynamic_cast<TClientMessage*>(msg)

	return true;
}
