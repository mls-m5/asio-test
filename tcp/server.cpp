/*
 * server.cpp
 *
 *  Created on: 11 feb. 2020
 *      Author: Mattias Larsson Sköld
 */

#include <iostream>
#include <asio.hpp>

using namespace std;
using asio::ip::tcp;

// Server
// Based on https://www.boost.org/doc/libs/1_72_0/doc/html/boost_asio/tutorial/tutdaytime2/src.html
int main(int argc, char **argv) {
	try {
		asio::io_service service;

		tcp::acceptor acceptor(service,
				tcp::endpoint(tcp::v4(), 9532));


		while(true) {
			tcp::socket socket(service);
			acceptor.accept(socket);

			asio::error_code error;
			write(socket, asio::buffer("hej"), error);
		}

	}
	catch(exception &e) {
		cerr << e.what() << endl;
	}
}



