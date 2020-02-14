/*
 * server.cpp
 *
 *  Created on: 14 feb. 2020
 *      Author: Mattias Larsson Sköld
 */

#include <asio.hpp>

#include <iostream>
#include <array>

using namespace std;
using asio::ip::udp;

int main(int argc, char **argv) {
	try {
		asio::io_service service;

		udp::socket socket(service, udp::endpoint(udp::v4(), 4568));

		while (true) {
			std::array<char, 16> buffer;
			udp::endpoint remoteEndpoint;
			asio::error_code error;
			auto size = socket.receive_from(asio::buffer(buffer), remoteEndpoint, 0, error);

			if (error && error != asio::error::message_size){
				throw asio::system_error(error);
			}

			cout << "got message from " << remoteEndpoint.address().to_string();
			cout << ":" << to_string(remoteEndpoint.port()) << endl;
			cout << "received message:" << endl;
			cout.write(buffer.data(), size);
			cout << endl;

			string message = "hello from server";

			socket.send_to(asio::buffer(message), remoteEndpoint, 0, error);
		}

	} catch (exception& e) {
		cerr << e.what() << endl;
	}
}

