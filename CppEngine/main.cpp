#include "iostream"

#include "Encodeur.hpp"

/*

SI JAMAIS IL Y A UNE ERREUR LNK 2019, c'est qu'il faut initialiser au moins une fois pour que se soit compiler dans Terminal Engine.lib
SI C'EST UN TEMPLATE IL NE FAUT PAS METTRE EN IMPORT/EXPORT CAR IL FAUT INITIAILISER POUR CHAQUE TYPE

*/

int main()
{
	std::string* str = new std::string("Hello World!");
	std::cout << Encodeur::Encode(*str) << std::endl;
	delete str;

	std::cin.ignore();
}