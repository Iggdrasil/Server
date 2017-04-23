#pragma once
#include <boost\thread\mutex.hpp>
#include <queue>

template<typename T> class safeQueue
{

	boost::mutex _mutex;
protected:
	std::queue<T> _q;
public:


	
	safeQueue(){}

	~safeQueue(){}

	void push(T val)
	{
		boost::mutex::scoped_lock lock(_mutex);
		_q.push(val);
	};

	T pop()
	{
		boost::mutex::scoped_lock lock(_mutex);
		T val;
		std::swap(val, _q.front());
		_q.pop();
		return val;
	};

	bool empty()
	{
		boost::mutex::scoped_lock lock(_mutex);
		return _q.empty();
	}
	
};

