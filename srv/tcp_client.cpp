#include "stdafx.h"
#include "tcp_client.h"
#include <boost\bind.hpp>
#include <iostream>

tcp_client::tcp_client(boost::asio::io_service& io_service, const std::string& server, std::string& buf)
	:_resolver(io_service), _socket(io_service)
{
	std::ostream request_stream(&_request);
	request_stream << buf;
	boost::asio::ip::tcp::resolver::query query(server, "http");
	_resolver.async_resolve(query,
		boost::bind(&tcp_client::handle_resolve, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::iterator));

}

tcp_client::~tcp_client()
{
}

void tcp_client::handle_resolve(const boost::system::error_code & err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	if (!err)
	{
		boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
		_socket.async_connect(endpoint,
			boost::bind(&tcp_client::handle_connect, this,
				boost::asio::placeholders::error, ++endpoint_iterator));
	}
	else
	{
		std::cout << "Error: " << err.message() << "\n";
	}
}

void tcp_client::handle_connect(const boost::system::error_code & err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	if (!err)
	{
		boost::asio::async_write(_socket, _request,
			boost::bind(&tcp_client::handle_write_request, this,
				boost::asio::placeholders::error));
	}
	else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
	{
		_socket.close();
		boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
		_socket.async_connect(endpoint,
			boost::bind(&tcp_client::handle_connect, this,
				boost::asio::placeholders::error, ++endpoint_iterator));
	}
	else
	{
		std::cout << "Error: " << err.message() << "\n";
	}
}

void tcp_client::handle_write_request(const boost::system::error_code & err)
{
	if (!err)
	{
		boost::asio::async_read_until(_socket, _response, "\r\n",
			boost::bind(&tcp_client::handle_read_status_line, this,
				boost::asio::placeholders::error));
	}
	else
	{
		std::cout << "Error: " << err.message() << "\n";
	}
}

void tcp_client::handle_read_status_line(const boost::system::error_code & err)
{
	if (!err)
	{
		std::istream response_stream(&_response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			std::cout << "Invalid response\n";
			return;
		}
		if (status_code != 200)
		{
			std::cout << "Response returned with status code ";
			std::cout << status_code << "\n";
			return;
		}

		boost::asio::async_read_until(_socket, _response, "\r\n\r\n",
			boost::bind(&tcp_client::handle_read_headers, this,
				boost::asio::placeholders::error));
	}
	else
	{
		std::cout << "Error: " << err << "\n";
	}
}

void tcp_client::handle_read_headers(const boost::system::error_code & err)
{
	if (!err)
	{
		std::istream response_stream(&_response);
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
			std::cout << header << "\n";
		std::cout << "\n";

		if (_response.size() > 0)
			std::cout << &_response;

		boost::asio::async_read(_socket, _response,
			boost::asio::transfer_at_least(1),
			boost::bind(&tcp_client::handle_read_content, this,
				boost::asio::placeholders::error));
	}
	else
	{
		std::cout << "Error: " << err << "\n";
	}
}

void tcp_client::handle_read_content(const boost::system::error_code & err)
{
	if (!err)
	{
		std::cout << &_response;
		boost::asio::async_read(_socket, _response,
			boost::asio::transfer_at_least(1),
			boost::bind(&tcp_client::handle_read_content, this,
				boost::asio::placeholders::error));
	}
	else if (err != boost::asio::error::eof)
	{
		std::cout << "Error: " << err << "\n";
	}
}
