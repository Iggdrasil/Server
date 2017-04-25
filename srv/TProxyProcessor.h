#pragma once
#include "TProcessor.h"
class ProxyProcessor :
	public TProcessor
{
public:
	ProxyProcessor();
	virtual ~ProxyProcessor();
	bool Process(TMessage* msg);
};

