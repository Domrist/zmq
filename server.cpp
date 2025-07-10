#include <zmq.hpp>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>
#include "sharedData.h"
#include <sstream>

using namespace std;



std::vector<Student> students;
std::vector<std::vector<std::string>> parsedCollection;


void readStudentsFile(const std::string & a_filePath)
{
	ifstream file(a_filePath);
	std::string tmpLine;
	std::cout << "READ FILE " << a_filePath << std::endl;
	
	while(getline(file, tmpLine))
	{
		stringstream ss(tmpLine);
		
		std::vector<std::string> tmpParseData;
		std::string tmpString;
		while(std::getline(ss, tmpString, ' '))
		{
			std::cout << tmpString << std::endl;
			tmpParseData.push_back(tmpString);
		}
		parsedCollection.push_back(tmpParseData);
	}
	file.close();
}


void writeParsedDataToCollection()
{
	for(std::vector<string> & tmpParsedStudentData : parsedCollection)
	{
		Student tmpStudent{
			tmpParsedStudentData[1],
			tmpParsedStudentData[2],
			tmpParsedStudentData[3]

		};

		students.push_back(tmpStudent);
	}
}


int main()
{
	const string endpoint = "tcp://*:5555";
	
	std::cout << "START SERVER" << std::endl;

	std::string firstFilePath("stud1.txt");
	std::string secondFilePath("stud2.txt");

	readStudentsFile(firstFilePath);
	readStudentsFile(secondFilePath);
	
	writeParsedDataToCollection();

	for(int i = 0; i < students.size(); ++i)
	{
		std::cout << students[i].firstName
		       	<< "\t" << students[i].lastName << std::endl;
	}

	zmq::context_t context{1};
	zmq::socket_t socket{context, zmq::socket_type::rep};
	socket.bind(endpoint);

	const std::string data{"world"};

	for(;;)
	{
		zmq::message_t request;

		socket.recv(request, zmq::recv_flags::none);
		std::cout << "Received " << request.to_string() << std::endl;

		std::this_thread::sleep_for(1s);

		std::cout << "Sending back " << sizeof(students) << std::endl;

		/*{
			std::ostringstream stream;
			stream.write(reinterpret_cast<char *>(&students), sizeof(students));
			zmq::message_t mst(stream.str().c_str(), stream.str().length());
		}*/

		std::this_thread::sleep_for(1s);

		for(auto & studentData : students)
		{
			
			zmq::message_t message;
			/*message.rebuild(studentData.firstName+"|"+
					studentData.lastName+"|"+
					studentData.bornDate);*/

			socket.send(message, zmq::send_flags::none);
			std::this_thread::sleep_for(1s);
		}
	}

	return 0;
}
