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

tcp_connection::pointer tcp_connection::create(boost::asio::io_service& ioserv, boost::function<void (pointer)> addToQueueCallback)
{
    return pointer(new tcp_connection(ioserv, addToQueueCallback));
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

void tcp_connection::getBuffer(std::array<char, NET_PARAMS::NetworkBufferSize>& buf)
{
	buf = recv_buffer;
}

size_t tcp_connection::getBufferLen()
{
	return data_received_len;
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
				data_received_len += len;
				// Буфер 8кб, может ли быть такое, что данных пришло больше? То есть,
				// Мы тут вызвали коллбэк, положили в очередь запрос, а он не полный.
				// В другом потоке началась обработка и тут внезапно приходит очередной запрос
				_addToQueueCallback(shared_from_this());
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

tcp_connection::tcp_connection(boost::asio::io_service& io_service, boost::function<void(pointer)> addToQueueCallback)
    : socket_(io_service), _addToQueueCallback(addToQueueCallback), data_received_len(0)
{

}


/*
TClientMessage::TClientMessage(std::array<char, NET_PARAMS::NetworkBufferSize>& buf, tcp_connection::pointer cPtr)
	:packetId(0)
{
	_tcpConnPtr = cPtr;
	_recvBuffer = buf;
	++packetId;
	_packetStatus = PACKET_STATUS::UNKNOWN;
	_packetStatus = PACKET_STATUS::UNKNOWN;
}

TClientMessage::~TClientMessage()
{

}

PACKET_PARAMS::PACKET_TYPE TClientMessage::getType()
{
	return _packType;
}

void TClientMessage::setProcessor(pPackProcessor proc)
{
	_processor = proc;
}

const std::array<char, NET_PARAMS::NetworkBufferSize>* TClientMessage::getBuffer() const
{
	return &_recvBuffer;
}

void TClientMessage::setPacketType(PACKET_PARAMS::PACKET_TYPE packType)
{
	_packType = packType;
}
*/