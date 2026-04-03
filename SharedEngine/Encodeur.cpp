#include <iostream>
#include "Encodeur.hpp"

using namespace std;
using namespace InternalFactory;

void Encodeur::Encode(const char* input, const size_t sizeof_input, Data& output_)
{
	string output;

	const uint8_t MAGIC[2] = { 0x4D, 0x53 };
	const uint8_t VERSION = 1;
	const uint8_t TYPE = 1;

	output.append(reinterpret_cast<const char*>(MAGIC), sizeof(MAGIC));
	output.push_back(static_cast<char>(VERSION));
	output.push_back(static_cast<char>(TYPE));
	output.append(input, sizeof_input);

	output_.size = output.size();
	//output_.ptr = output.c_str();
}

const Data Encodeur::Encode(const char* input, const size_t sizeof_input)
{
	string temp;

	const uint8_t MAGIC[2] = { 0x4D, 0x53 };
	const uint8_t VERSION = 1;
	const uint8_t TYPE = 1;

	// J'utilise pas mutex ? Mais est-ce vraiment si utile ?

	temp.append(reinterpret_cast<const char*>(MAGIC), sizeof(MAGIC));
	temp.push_back(static_cast<char>(VERSION));
	temp.push_back(static_cast<char>(TYPE));
	temp.append(input, sizeof_input);

	// Mais il manque pas la fin ?

	// allocate a heap buffer, copy the data and add a null terminator
	char* Reslt = new char[temp.size() + 1]; /////// ATTENTUION, IL FAUT PENSER A LIBERER CETTE MEMOIRE APRES UTILISATION
	CreateValue(Reslt, temp.size() + 1);
	std::memcpy(Reslt, temp.data(), temp.size());
	Reslt[temp.size()] = '\0';

	Data result;
	result.size = temp.size();
	result.ptr = static_cast<void*>(Reslt);

	return result;
}

const Data Encodeur::Encode(const Data Input)
{
	string* test = new string("test");
	delete test;
	Data ddfs;
	ddfs.size = 0;
	return ddfs;
}

void Encodeur::Decode(const char* input, const size_t sizeof_input, std::string& output)
{

}

const Data Encodeur::Decode(const char* input, const size_t sizeof_input)
{
	string* test = new string("test");
	delete test;
	Data ddfs;
	ddfs.size = 0;
	return ddfs;
}


const Data Encodeur::Decode(const Data Input)
{
	string* test = new string("test");
	delete test;
	Data ddfs;
	ddfs.size = 0;
	return ddfs;
}
