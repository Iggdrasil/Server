#pragma once
#include <boost/asio.hpp>
#include "tcp_connection.h"
#include "TMessage.h"

class tcp_server
{

private:
    boost::asio::ip::tcp::acceptor _acceptor;

	TMessageQueue* _messageQueue;

public:
    tcp_server(boost::asio::io_service& ioserv, TMessageQueue* que);
    ~tcp_server();

    void start_accept();
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);
};

