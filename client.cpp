#include <string>

#include <iostream>
#include "sharedData.h"
#include <zmq.hpp>

std::vector<Student> studentCollection;


std::vector<std::string> fromStringToArr(std::string a_string, char delimeter)
{
	std::stringstream ss(a_string);
        std::vector<std::string> tmpParseData;
	std::string tmpString;
        
	while(std::getline(ss, tmpString, delimeter))
        {
        	tmpParseData.push_back(tmpString);
        }
        return tmpParseData;

}


void parseAndAddStudentToCollection(std::string a_data)
{
	auto p = fromStringToArr(a_data, '|');
	studentCollection.push_back({p[0], p[1], p[2]});
}

void showStudents()
{
	for(const Student & s : studentCollection)
	{
		std::cout << s.firstName << "\t" << s.lastName << "\t" << s.bornDate << std::endl;
	}
}


void parseData(std::string a_preparsedData)
{
	auto preparsedData = fromStringToArr(a_preparsedData, '#');
	for(std::string data : preparsedData)
	{
		parseAndAddStudentToCollection(data);
	}
}

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

 	std::string preparsedData = std::string(static_cast<char *>(message.data()),message.size());

	parseData(preparsedData);
	showStudents();

	return 0;
}
