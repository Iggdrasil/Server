#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include "NetParams.h"

class TMessageQueue;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{

public:
	typedef boost::shared_ptr<tcp_connection> pointer;
	
private:
	TMessageQueue* _messageQueue;

    boost::asio::ip::tcp::socket socket_;

    explicit tcp_connection(boost::asio::io_service& io_service, TMessageQueue* que);

    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_read(const boost::system::error_code& e, size_t len);

	std::array<char, NET_PARAMS::NetworkBufferSize> _recvBuffer;

	size_t _currentBufferSize;

public:

	std::array<char, NET_PARAMS::NetworkBufferSize>::const_iterator getBufferBegin();

	size_t getCurrentBufferLen();

    static pointer create(boost::asio::io_service& ioserv, TMessageQueue* que);

    boost::asio::ip::tcp::socket& socket();

    void start_listen();
};

