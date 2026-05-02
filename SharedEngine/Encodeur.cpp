#include <iostream>
#include "Encodeur.hpp"
#include <cassert>  // à inclure
#include <bitset>


using namespace std;
using namespace InternalFactory;

const Data Encodeur::Encode(const char* input, const size_t sizeof_input)
{
	string temp;

	const uint8_t MAGIC[2] = { 0x4D, 0x53 };
	const uint8_t VERSION = 1;
	const uint8_t TYPE = 1;
	const uint8_t LENGTH = sizeof_input;

	// J'utilise pas mutex ? Mais est-ce vraiment si utile ?

	temp.append(reinterpret_cast<const char*>(MAGIC), sizeof(MAGIC));
	temp.push_back(static_cast<char>(VERSION));
	temp.push_back(static_cast<char>(TYPE));
	temp.push_back(static_cast<char>(LENGTH));
	temp.append(input, sizeof_input);

	Data checksum = JCS32(temp.data(), temp.size());

	temp.append(static_cast<const char*>(checksum.ptr), checksum.size);

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
	string temp(input, sizeof_input);

	// Vérification de la validité de l'entrée
	if (temp.size() < 4 || temp[0] != 'M' || temp[1] != 'S' || temp[2] != 1 || temp[3] != 1) {
		cerr << "Invalid input format" << endl;
		return Data{ 0, nullptr };
	}

	// Extraction des données après l'en-tête
	string decoded = temp.substr(4);

	// allocate a heap buffer, copy the data and add a null terminator
	char* Reslt = new char[decoded.size() + 1]; /////// ATTENTUION, IL FAUT PENSER A LIBERER CETTE MEMOIRE APRES UTILISATION
	CreateValue(Reslt, decoded.size() + 1);
	std::memcpy(Reslt, decoded.data(), decoded.size());
	Reslt[decoded.size()] = '\0';
	Data result;
	result.size = decoded.size();
	result.ptr = static_cast<void*>(Reslt);
	return result;
}

const Data Encodeur::JCS32(const char* input, const size_t sizeof_input)
{
	char* Interpretation = new char[sizeof_input];
	std::memcpy(Interpretation, input, sizeof_input);

	uint64_t step1 = sizeof_input;

	for (size_t i = 0; i < sizeof_input; i++)
	{
		step1 = (step1 + Interpretation[i] + 1) * (Interpretation[i] + 1);
	}

	// tableau de bits compact
	uint8_t* Step2 = new uint8_t[5]; // CLAUDE A DIT DE FAIRE ÇA POUR LA LECTURE DU DEBBUGGER C'EST LACHE DE FAIRE ÇA MAIS HASSOUL
	std::memset(Step2, 0, 5);

	for (int i = 0, j = 0; i < 64; i += 2, j++)
	{
		int bit = (step1 >> i) & 1;

		if (bit) // ignorer
			Step2[j / 8] |= (1 << (j % 8)); //// PROBELEME DE MERDE À 3
	}

	for (int i = 0; i < 31; i++)
	{
		int bit = (Step2[i / 8] >> (i % 8)) & 1;

		if (bit == 0)
		{
			int next = (Step2[(i + 1) / 8] >> ((i + 1) % 8)) & 1;

			if (next)
			{
				Step2[i / 8] |= (1 << (i % 8));
				Step2[(i + 1) / 8] &= ~(1 << ((i + 1) % 8));
			}

			i++;
		}
	}

	uint8_t* Step3 = new uint8_t[9];
	std::memcpy(Step3, Step2, 4);

	uint32_t v2 = 0;
	uint64_t v3 = 0;

	{
		/////////////// A ENELVER 

		std::memcpy(&v2, Step2, 4);

		// std::cout << std::bitset<32>(v2) << '\n';

		std::memcpy(&v3, Step3, 8);

		// std::cout << std::bitset<64>(v3) << '\n';

		/////////////// A ENELVER - fin
	}

	for (int i = 0; i < 32; i++)
	{
		int src = 31 - i;
		int dst = i + 32;
		int bit = (Step2[src / 8] >> (src % 8)) & 1;

		Step3[dst / 8] &= ~(1 << (dst % 8));   // reset
		Step3[dst / 8] |= (bit << (dst % 8));  // set
	}

	char* Reslt = new char[8]; /////// ATTENTUION, IL FAUT PENSER A LIBERER CETTE MEMOIRE APRES UTILISATION

	std::memcpy(Reslt, Step3, 8);

	{
		/////////////// A ENELVER 

		std::memcpy(&v2, Step2, 4);

		// std::cout << std::bitset<32>(v2) << '\n';

		std::memcpy(&v3, Step3, 8);

		// std::cout << std::bitset<64>(v3) << '\n';

		/////////////// A ENELVER - fin
	}

	Data result;

	result.size = 8;
	result.ptr = static_cast<void*>(Reslt);
	delete[] Step2;
	delete[] Step3;
	delete[] Interpretation;
	CreateValue(Reslt, 8);

	return result;
}





















