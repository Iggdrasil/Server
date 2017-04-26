#pragma once
#include <boost\asio.hpp>
#include <string>

class tcp_client
{
	boost::asio::ip::tcp::resolver resolver_;
	boost::asio::ip::tcp::socket socket_;

public:
	tcp_client(boost::asio::io_service& io_service, const std::string& server, const std::string& path);
	~tcp_client();
};

