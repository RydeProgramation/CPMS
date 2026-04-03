#include "iostream"

#include "Encodeur.hpp"

using namespace std;
using namespace Encodeur;
using namespace InternalFactory;

int main()
{
	string* str = new string("Hello World!");
	Data test = Encode(str->c_str(), str->size());
	delete str;
	

	/////

	char* Test = new char[test.size];
	std::memcpy(Test, test.ptr, test.size);

	for (uint64_t i = 0; i < test.size; i++) {
		std::cout << Test[i];
	}
	std::cout << std::endl;
	delete[] Test;

	FreeBuffer();

	Test = new char[test.size];
	std::memcpy(Test, test.ptr, test.size);

	for (uint64_t i = 0; i < test.size; i++) {
		std::cout << Test[i];
	}
	std::cout << std::endl;
	delete[] Test;

	std::cin.ignore();
}