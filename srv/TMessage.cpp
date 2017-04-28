#include "stdafx.h"
#include "TMessage.h"

void TMessageQueue::enqueue(TMessage msg)
{
	_messageQueue.push(msg);
}

TMessage TMessageQueue::dequeue()
{
	return _messageQueue.pop();
}
