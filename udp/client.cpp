/*
 * client.cpp
 *
 *  Created on: 12 feb. 2020
 *      Author: Mattias Larsson Sköld
 */


#include <asio.hpp>
#include <iostream>
#include <string>

using namespace std;
using asio::ip::udp;

int main(int argc, char **argv) {
	try {
		asio::io_service service;

		udp::resolver resolver(service);
		auto query = udp::resolver::query(udp::v4(), "localhost",
				to_string(4568));
		auto endpoint = *resolver.resolve(query); // Just select the first endpoint

		auto socket = udp::socket(service);
		socket.open(udp::v4());

		socket.send_to(asio::buffer("hej"s), endpoint);

		udp::endpoint senderEndpoint;
		std::array<char, 128> buffer;
		auto len = socket.receive_from(asio::buffer(buffer), senderEndpoint);
		cout << "got message from " << senderEndpoint.address().to_string();
		cout << ":" << to_string(senderEndpoint.port()) << endl;
		cout.write(buffer.data(), len);
		cout << endl;
	}
	catch (std::exception &e) {
		cerr << e.what() << endl;
	}
}



