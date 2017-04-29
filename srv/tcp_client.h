#pragma once
#include <boost\asio.hpp>
#include <string>

class tcp_client
{
	boost::asio::ip::tcp::resolver _resolver;
	boost::asio::ip::tcp::socket _socket;

	boost::asio::streambuf _request;
	boost::asio::streambuf _response;

public:
	tcp_client(boost::asio::io_service& io_service, const std::string& server, std::string& buf);
	~tcp_client();

private:
	void handle_resolve(const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	void handle_connect(const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	void handle_write_request(const boost::system::error_code& err);

	void handle_read_status_line(const boost::system::error_code& err);

	void handle_read_headers(const boost::system::error_code& err);

	void handle_read_content(const boost::system::error_code& err);
};

