#pragma once
#include "TProcessor.h"
class ProxyProcessor :
	public TProcessor
{
	void makeHeader(const HttpRequest& head, std::string& _request);
	void makeBody(TMessage* msg, std::string& _request);

	boost::asio::io_service& _serv;

	bool getValueByName(const HttpRequest& head, const std::string& name, std::string& value);

public:
	ProxyProcessor(boost::asio::io_service& serv);
	virtual ~ProxyProcessor();
	bool Process(TMessage* msg);
};

