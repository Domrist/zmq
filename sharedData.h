#include <string>
#include <vector>

struct Student
{
        std::string firstName;
        std::string lastName;
        std::string bornDate;
}; 


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
