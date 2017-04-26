#include "stdafx.h"
#include "tcp_client.h"

tcp_client::tcp_client(boost::asio::io_service& io_service, const std::string& server, const std::string& path)
	:resolver_(io_service), socket_(io_service)
{

}

tcp_client::~tcp_client()
{
}
