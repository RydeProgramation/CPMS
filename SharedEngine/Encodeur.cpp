#include <iostream>
#include "Encodeur.hpp"

using namespace std;
using namespace InternalFactory;

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

const Data Encodeur::Decode(const char* input, const size_t sizeof_input)
{
	return Data{ 0, nullptr };
}