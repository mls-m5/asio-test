
#include <iostream>
#include <asio.hpp>
#include <string>
#include <array>

using namespace std;

// Client
// Based on https://www.boost.org/doc/libs/1_72_0/doc/html/boost_asio/tutorial/tutdaytime1/src.html
int main(int argc, char **argv) {
	try {
		string adress = "localhost";

		asio::io_service service;
		asio::ip::tcp::resolver resolver(service);
		asio::ip::tcp::resolver::query query(adress, to_string(9532));
		auto endpoints = resolver.resolve(query);

		asio::ip::tcp::socket socket(service);
		asio::connect(socket, endpoints);

		while (true) {
			std::array<char, 128> buffer;
			asio::error_code error;
			auto len = socket.read_some(asio::buffer(buffer), error);

			if (error == asio::error::eof) {
				break;
			}
			else if (error) {
				throw asio::system_error(error);
			}

			cout.write(buffer.data(), len);
		}
	}
	catch(exception &e) {
		cerr << e.what() << endl;
	}
}

