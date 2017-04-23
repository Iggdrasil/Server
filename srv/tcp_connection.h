#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include "NetParams.h"
#include "SafeQueue.h"
//#include "TClientMessage.h"

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{

public:
	typedef boost::shared_ptr<tcp_connection> pointer;
	
private:
	boost::function<void(pointer)> _addToQueueCallback;

    boost::asio::ip::tcp::socket socket_;

    explicit tcp_connection(boost::asio::io_service& io_service, boost::function<void(pointer)> addToQueueCallback);

    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_read(const boost::system::error_code& e, size_t len);

	std::array<char, NET_PARAMS::NetworkBufferSize> recv_buffer;
	size_t data_received_len;

public:

    static pointer create(boost::asio::io_service& ioserv, boost::function<void(pointer)> addToQueueCallback);
    boost::asio::ip::tcp::socket& socket();
    void start_listen();

	void getBuffer(std::array<char, NET_PARAMS::NetworkBufferSize>& buf);
	size_t getBufferLen();
};

