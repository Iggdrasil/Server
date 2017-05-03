#include "stdafx.h"
#include "TProxyProcessor.h"
#include "NetParams.h"
#include <iostream>
#include <ostream>
#include "tcp_client.h"

using std::cout; 
using std::endl;

void ProxyProcessor::makeHeader(const HttpRequest& head, std::string& _request)
{	

	std::stringstream request_stream;
	request_stream << head.method << " /" /*<< head.uri */<< " HTTP/" << head.http_version_major << "." << head.http_version_minor << "\r\n";

	for each (HttpHeader var in head.headers)
	{
		if (!var.name.compare("Proxy-Connection"))
		{
			continue;
		}
		request_stream << var.name << ": " << var.value << "\r\n";
	}
	request_stream << "Connection: Keep-Alive\r\n\r\n";
	_request = request_stream.str();
	return;

}

void ProxyProcessor::makeBody(TMessage * msg, std::string& _request)
{
	std::stringstream request_stream;
	request_stream << std::string(msg->getBufferBegin() + msg->_httpRequest.header_len, msg->getBufferBegin() + msg->getCurrentSize());
	_request += request_stream.str();
	return;
}

bool ProxyProcessor::getValueByName(const HttpRequest & head, const std::string & name, std::string & value)
{
	for each (HttpHeader var in head.headers)
	{
		if (!var.name.compare("Host"))
		{
			value = var.value;
			return true;
		}
	}
	return false;
}

ProxyProcessor::ProxyProcessor(boost::asio::io_service& serv)
	:_serv(serv)
{
}


ProxyProcessor::~ProxyProcessor()
{
}

bool ProxyProcessor::Process(TMessage* msg)
{
	cout << msg->_httpRequest.method<<" "<<msg->_httpRequest.uri << endl;
	std::string buf;
	makeHeader(msg->_httpRequest, buf);
	if (msg->getCurrentSize() > msg->_httpRequest.header_len)
	{
		// Надо добавить содержимое
		makeBody(msg, buf);
	}
	std::string server;
	if (getValueByName(msg->_httpRequest, "Host", server))
	{
		if (server.compare("www.liveinternet.ru"))
		{
			return true;
		}
		// TODO думать об асинхронности
		//tcp_client cli(_serv, server, buf);

		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << buf;
		try
		{
			boost::asio::ip::tcp::resolver resolver(_serv);
			boost::asio::ip::tcp::resolver::query query(server, "http");
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

			boost::asio::ip::tcp::socket socket(_serv);
			boost::asio::connect(socket, endpoint_iterator);
			boost::asio::write(socket, request);

			boost::asio::streambuf response;
			boost::asio::read_until(socket, response, "\r\n");
			

			// Check that response is OK.
			std::istream response_stream(&response);
			std::string http_version;
			response_stream >> http_version;
			unsigned int status_code;
			response_stream >> status_code;
			std::string status_message;
			std::getline(response_stream, status_message);
			if (!response_stream || http_version.substr(0, 5) != "HTTP/")
			{
				std::cout << "Invalid response\n";
				return 1;
			}
			if (status_code != 200)
			{
				std::cout << "Response returned with status code " << status_code << "\n";
				return 1;
			}

			// Read the response headers, which are terminated by a blank line.
			boost::asio::read_until(socket, response, "\r\n\r\n");

			// Process the response headers.
			std::string header;
			while (std::getline(response_stream, header) && header != "\r")
				std::cout << header << "\n";
			std::cout << "\n";

			// Write whatever content we already have to output.
			if (response.size() > 0)
				std::cout << &response;

			// Read until EOF, writing data to output as we go.
			boost::system::error_code error;
			while (boost::asio::read(socket, response,
				boost::asio::transfer_at_least(1), error))
				std::cout << &response;
			if (error != boost::asio::error::eof)
				throw boost::system::system_error(error);
		}
		catch (std::exception& e)
		{
			std::cout << "Exception: " << e.what() << "\n";
		}



	}



	return true;
}
