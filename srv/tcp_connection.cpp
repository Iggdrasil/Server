#include "stdafx.h"
#include "tcp_connection.h"
#include <boost/bind.hpp>
#include <iostream>
#include <boost\function.hpp>


std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

tcp_connection::pointer tcp_connection::create(boost::asio::io_service& ioserv)
{
    return pointer(new tcp_connection(ioserv));
}

boost::asio::ip::tcp::socket& tcp_connection::socket()
{
    return socket_;
}

void tcp_connection::start_listen()
{
	// Начинаем читать входящее сообщение
	socket_.async_receive(boost::asio::buffer(recv_buffer), 
		boost::bind(&tcp_connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}



void tcp_connection::handle_write(const boost::system::error_code&, size_t)
{

}

void tcp_connection::handle_read(const boost::system::error_code& err, size_t len)
{
    // Проверяем, что нет ошибок
	if (!err)
	{
		try 
		{
			if(!recv_buffer.empty())
			{
				
				
			}
		}
		catch (std::exception ex) 
		{
			std::cout << ex.what() << std::endl;
		}
		catch (...) 
		{
			std::cout << "Unknown error while parsing  message" << std::endl;
		}
	}
    else if ( (boost::asio::error::eof == err) ||
        (boost::asio::error::connection_reset == err) )
    {
        std::cout << "Disconnect " << std::endl;
        return;
    }
	else 
	{
		std::cout << "handle_receive: error: " << err.message() << std::endl;
        return;
	}

	start_listen();

}

tcp_connection::tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
{

}

