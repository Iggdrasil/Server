#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include "NetParams.h"



class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{

public:
	typedef boost::shared_ptr<tcp_connection> pointer;
	
private:
	
    boost::asio::ip::tcp::socket socket_;

    explicit tcp_connection(boost::asio::io_service& io_service);

    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_read(const boost::system::error_code& e, size_t len);

	std::array<char, NET_PARAMS::NetworkBufferSize> recv_buffer;

public:

    static pointer create(boost::asio::io_service& ioserv);

    boost::asio::ip::tcp::socket& socket();

    void start_listen();

};

