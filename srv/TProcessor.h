#pragma once
#include <boost\shared_ptr.hpp>
#include "TMessage.h"

using boost::shared_ptr;


// ��������� ����� ����������
class TProcessor
{
	
public:
	typedef shared_ptr<TProcessor> pProcessor;

	TProcessor(){}

	virtual ~TProcessor(){}

	virtual bool Process(TMessage*) = 0;
};

