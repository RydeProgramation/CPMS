#include "iostream"

#include "Encodeur.hpp"
#include <bitset>


using namespace std;
using namespace Encodeur;
using namespace InternalFactory;

int main()
{
	string* str = new string("Hello World");
	Data test = Encode(str->c_str(), str->size());
	Data test2 = Decode(static_cast<const char*>(test.ptr), test.size);

	char* temp = new char[test2.size ];

	std::memcpy(temp, test2.ptr, test2.size);

	std::cout << temp << std::endl;

	delete[] temp;

	std::cin.ignore();

// 
// 
// 	// std::cout << std::bitset<64>((uint64_t)test.ptr) << std::endl;
// 
// 	std::cin.ignore();
// 	
// 	/////
// 
// 	for (uint64_t i = 0; i < 500000; i++) 
// 	{
// 		test = Encode(str->c_str(), str->size());
// 	}
// 
// 	char* Test = new char[test.size];
// 	std::memcpy(Test, test.ptr, test.size);
// 
// 	for (uint64_t i = 0; i < test.size; i++) {
// 		std::cout << Test[i];
// 	}
// 	std::cout << std::endl;
// 
// 	for (uint64_t i = 0; i < test2.size; i++) {
// 		std::cout << static_cast<char*>(test2.ptr)[i];
// 	}
// 
// 	std::cout << std::endl;
// 
// 	delete[] Test;
// 
// 	FreeBuffer();
}