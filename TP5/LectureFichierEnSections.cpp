//! \author Francois-R.Boyer@PolyMtl.ca
//! \date 2019-02
//! \file
//? NOTE: Les commentaires //? sont pour but éducatifs et ne devraient pas se trouver dans un programme réel.

#include "LectureFichierEnSections.h"
#include <cassert>  //? Contient "assert" qui permet de s'assurer qu'une expression est vraie, et terminer le programme avec un message d'erreur en cas contraire.
using namespace std;

LectureFichierEnSections::LectureFichierEnSections(const string& nomFichier, char separateurDeSections) :
	ifstream{nomFichier},  //? ifstream ne supporte pas string_view comme nom de fichier, d'où l'utilisation de const string&.
	debutFichier_{tellg()},
	separateurDeSections_{separateurDeSections}
{
	exceptions(ios::failbit);
}

LectureFichierEnSections& LectureFichierEnSections::allerASection(std::string_view titreSection)
{
	//? On hérite d'ifstream, donc on peut utiliser directement seekg de la classe de base.
	assert(titreSection[0] == separateurDeSections_ && "Le titre de section doit commencer par le séparateur de section."); //NOTE: Utiliser starts_with de C++20 lorsqu'il sera supporté.
	while (!estFinFichier())
		if (lireLigne() == titreSection)
			return *this;
	assert(false && "Erreur dans le fichier ou le programme, un titre de section n'a pas été trouvé.");
	return *this; // On ne devrait jamais se rendre à cette ligne.
}

bool LectureFichierEnSections::estFinFichier()
{
	return eof() || ws(*this).eof();
}

bool LectureFichierEnSections::estFinSection()
{
	return estFinFichier() || peek() == separateurDeSections_;
}

string LectureFichierEnSections::lireLigne()
{
	string ligne;
	//? Puisqu'on hérite de ifstream, si on écrit juste "getline" ça va tenter d'utiliser celui dans "istream", il faut donc faire "::getline" pour appeler la version globale.
   // std::getline(*this, ligne,'\r');//pour mac
    std::getline(*this, ligne); // pour windows
   
	return ligne;
}

istringstream LectureFichierEnSections::lecteurDeLigne()
{
	std::istringstream lectureLigne{lireLigne()};
	lectureLigne.exceptions(ios::failbit);
	return lectureLigne;
}
