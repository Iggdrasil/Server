#include "stdafx.h"
#include "TMessage.h"

void TMessageQueue::enqueue(TMessage* msg)
{
	_messageQueue.push(msg);
}

TMessage* TMessageQueue::dequeue()
{
	return _messageQueue.pop();
}

std::array<char, NET_PARAMS::NetworkBufferSize>::const_iterator TMessage::getBufferBegin()
{
	return _tcpConnPtr->getBufferBegin();
}

size_t TMessage::getCurrentSize()
{
	return _tcpConnPtr->getCurrentBufferLen();
}
