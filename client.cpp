#include <string>

#include <iostream>
#include "sharedData.h"
#include <zmq.hpp>



int main()
{
	zmq::context_t context{2};

	zmq::socket_t socket{context, zmq::socket_type::req};
	socket.connect("tcp://localhost:5555");

	std::string data{"Hello"};

	std::cout << "SEnding hello " << std::endl;
	socket.send(zmq::buffer(data), zmq::send_flags::none);

	zmq::message_t message;

	socket.recv(message);

	std::cout << message.size() << std::endl;

	return 0;
}
