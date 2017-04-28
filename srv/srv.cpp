// srv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <boost\thread.hpp>
#include <boost\bind.hpp>
#include "tcp_server.h"
#include "router_service.h"

int _tmain(int argc, _TCHAR* argv[])
{

    try
    {
        boost::asio::io_service io_service;

		router_service rc(io_service);
		boost::thread thr(boost::bind(&router_service::svc, &rc));

        tcp_server server(io_service);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

