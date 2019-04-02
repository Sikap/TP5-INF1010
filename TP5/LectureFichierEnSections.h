#pragma once  //? Ceci n'est pas dans le standard ISO C++ mais est supporté par tous les compilateurs principaux; ça sert à remplacer les gardes d'inclusion.
//! \author Francois-R.Boyer@PolyMtl.ca
//! \date 2019-02
//! \file
//? NOTE: Les commentaires //? sont pour but éducatifs et ne devraient pas se trouver dans un programme réel.

#include <fstream>
#include <string>
#include <string_view>  //? (C++17) "string_view" se comporte similairement à "const string&" (il faut le voir comme une référence à un texte malgre qu'il n'y a pas de "&") mais est plus general.
#include <sstream>  //? Les istringstream et ostringstream sont des streams pour lire et ecrire dans des string.
using namespace std;
//! Permet la lecture d'un fichier en sections, chaque section etant une ligne qui debute par un séparateur de section (par defaut "-") et suivie d'un titre de section.
//! Les espaces en début de lignes, incluant les lignes completement vides, ne sont pas importants et sont sautes.
class LectureFichierEnSections : public std::ifstream {
public:
	LectureFichierEnSections(const string& nomFichier, char separateurDeSection = '-');

	LectureFichierEnSections& allerASection(string_view titreSection);
	bool estFinFichier();
	bool estFinSection();
	std::string lireLigne();
	std::istringstream lecteurDeLigne();

private:
	std::streampos debutFichier_;
	char separateurDeSections_;
};
