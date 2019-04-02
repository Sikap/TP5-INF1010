/********************************************
* Titre: Travail pratique #5 - gestionnaireTables.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/


#include "GestionnaireTables.h"
#include "LectureFichierEnSections.h"

Table * GestionnaireTables::getTable(int id) const
{
	set<Table*> T = getConteneur();
	for (auto it = T.begin(); it != T.end(); it++) {
		if ((*it)->getId() == id)
			return *it;
		else return nullptr;
	}
}
Table * GestionnaireTables::getMeilleureTable(int tailleGroupe) const
{
	set<Table*>::iterator it = conteneur_.begin();
	int min = (*it)->getNbPlaces() - tailleGroupe;
	for (it; it != conteneur_.end(); it++) {
		if (min == 0) {
			return (*it);
		}
		else if ((*it)->getNbPlaces() - tailleGroupe < min) {
			min = (*it)->getNbPlaces() - tailleGroupe;
		}
	}
	return *it;
}

void GestionnaireTables::lireTables(const string& nomFichier)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection("-TABLES");
	while (!fichier.estFinSection()) {
		int id, nbPlaces;
		fichier >> id >> nbPlaces;
		ajouter(new Table(id, nbPlaces));
	}
}


GestionnaireTables & GestionnaireTables::operator+=(Table* table)
{
	conteneur_.insert(table);
   return *this;
}

void GestionnaireTables::afficherTables(ostream & os) const
{
	copy(conteneur_.begin(), conteneur_.end(), ostream_iterator<Table*>(os,"\n"));
}

