#pragma once
#include <boost/asio.hpp>
#include "tcp_connection.h"
#include "TClientMessage.h"
#include "SafeQueue.h"

class tcp_server
{

private:
    boost::asio::ip::tcp::acceptor _acceptor;

	safeQueue<TClientMessage>* _messageQueue;

	void addToQueue(tcp_connection::pointer tcpConn);

public:
    tcp_server(boost::asio::io_service& ioserv, safeQueue<TClientMessage>* que);
    ~tcp_server();

    void start_accept();
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);
};

