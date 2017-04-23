#pragma once
#include <boost\shared_ptr.hpp>

using boost::shared_ptr;

class TMessage;

// ��������� ����� ����������
class TProcessor
{
public:
	typedef shared_ptr<TProcessor> pProcessor;

	TProcessor(){}

	virtual ~TProcessor(){}

	virtual void Process(TMessage*) = 0;
};

