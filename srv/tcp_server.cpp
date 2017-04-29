#include "stdafx.h"
#include <boost/bind.hpp>
#include "tcp_server.h"

tcp_server::~tcp_server()
{
}


// ��� �������� ������� ��������� ��� ����� �������, ������� �� ��������
tcp_server::tcp_server(boost::asio::io_service& ioserv, TMessageQueue* que)
    :_acceptor(ioserv, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4399)), _messageQueue(que)
{
    start_accept();
}


void tcp_server::start_accept()
{

	// ������� ����� ����������. ������ ���������� �������� ��������� �� �������, ��� ����� ��������� ���������
    tcp_connection::pointer newConnection = tcp_connection::create(_acceptor.get_io_service(), _messageQueue);

	// �������� �����
    _acceptor.async_accept(newConnection->socket(),
        boost::bind(&tcp_server::handle_accept, this, newConnection, boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error)
{
	// ���������� � ������ �������� �������
    if (!error)
    {
		// ���� ��� ������, �� �������� ��������� 
		new_connection->start_listen();
    }

    start_accept();
}