#include "stdafx.h"
#include "router_service.h"
#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "request.h"

using std::cout;
using std::endl;

router_service::router_service(boost::asio::io_service& srv)
	:_srv(srv)//,	_proxyProc(new ProxyProcessor())
{
}


router_service::~router_service()
{
}

void HeaderParser(const std::string& str, std::string& host, std::string& port)
{
	size_t sep = str.find("\r\n\r\n");
	if (sep == std::string::npos)
	{
		return;
	}

	std::string head = str.substr(0, sep);
	std::string _URL;
	std::string _HOST;
	while (!head.empty())
	{
		size_t sepEnd = head.find("\r\n");
		if (sepEnd == std::string::npos)
		{
			break;
		}

		if (_URL.empty())
		{
			size_t start = head.substr(0, sepEnd).find("http");
			size_t ed = head.substr(0, sepEnd).find("HTTP") - 5;
			if((ed > start) && (ed != std::string::npos) && (start != std::string::npos))
			{
				_URL = head.substr(start, ed);
			}
			
		}

		size_t sep = head.substr(0, sepEnd).find(":");
		if (!head.substr(0, sep).compare("Host"))
		{
			_HOST = head.substr(sep + 2, sepEnd - sep - 2);
		}

		head.erase(0, sepEnd + 2);
	}
	sep = _HOST.find(":");
	if (sep != std::string::npos)
	{
		port = _HOST.substr(sep + 1);
	}
	else
	{
		port = "80";
	}
	host = _HOST;
}


PACKET_PARAMS::PACKET_TYPE router_service::checkType(const TClientMessage& msg)
{
	

/*
	std::array<char, NET_PARAMS::NetworkBufferSize> recvBuffer;
	msg.getBuffer(recvBuffer);
	size_t len = msg.getBufferLen();

	//const std::array<char, NET_PARAMS::NetworkBufferSize>& recvBuffer

	// для определения типа смотрим первую строку данных
	// Проверим, что данные вообще есть
	if (recvBuffer.empty() || len == 0)
	{
		return PACKET_PARAMS::UNKNOWN;
	}
	std::string buf;
	buf.assign(recvBuffer.begin(), recvBuffer.begin() + len);

	const std::string rnrn("\r\n\r\n");
	const std::string HTTP("HTTP");

	std::string::const_iterator it1, it2 = std::search(buf.begin(),
		buf.end(),
		rnrn.begin(),
		rnrn.end());

	if (buf.end() != it2)
	{
		it1 = std::search(buf.begin(),
			it2,
			HTTP.begin(),
			HTTP.end());
		if (buf.end() != it1)
		{
			return PACKET_PARAMS::RQ_PROXY;
		}
	}
*/	
	return PACKET_PARAMS::UNKNOWN;
}

void router_service::Init()
{

}


void router_service::svc()
{
	Init();

	while (true)
	{
		while (!_q.empty())
		{
/*
			std::string hst, prt;
			HeaderParser(_q.front().first, hst, prt);
			boost::asio::ip::tcp::resolver::query qr(hst, prt);
			if (!hst.empty())
			{
				boost::asio::ip::tcp::resolver rs(_srv);
				boost::asio::ip::tcp::resolver::iterator ep_it = rs.resolve(qr);
				boost::asio::ip::tcp::resolver::iterator end;
				boost::asio::ip::tcp::socket socket(_srv);
				boost::system::error_code error = boost::asio::error::host_not_found;
				while (error && ep_it != end)
				{
					socket.close();
					socket.connect(*ep_it++, error);
				}
				if (error)
				{
					throw boost::system::system_error(error);
				}
				//size_t len = _q.front().first.length();
				boost::asio::write(socket, boost::asio::buffer(_q.front().first), error);
				if (error) {
					std::cout << "send failed: " << error.message() << std::endl;
				}
				else {
					std::cout << "send correct!" << std::endl;
				}

				boost::asio::streambuf receive_buffer;
				boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);

				if (error && error != boost::asio::error::eof) {
					std::cout << "receive failed: " << error.message() << std::endl;
				}
				else {
					const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
					std::cout << data << std::endl;
				}
			}
*/
			/*
			if (_q.front().getType() == PACKET_PARAMS::UNKNOWN)
			{
				_q.front().setPacketType(checkType(_q.front()));
			}

			if (_q.front().getType() == PACKET_PARAMS::RQ_PROXY)
			{
				_q.front().setProcessor(TClientMessage::pPackProcessor(_proxyProc));
				_pendingRequests.push(_q.front());
			}
			*/
			//std::vector<char> msg;
			//_q.front().getMessage(msg);
			//cout << &msg[0] << endl;
			request req;
			std::array<char, NET_PARAMS::NetworkBufferSize> buf;
			_q.front().getBuffer(buf);
			rparser.parse(req, buf.begin(), buf.begin() + _q.front().getBufferLen());
			_q.pop();
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
	}
}
