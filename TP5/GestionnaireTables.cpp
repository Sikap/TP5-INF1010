/********************************************
* Titre: Travail pratique #5 - gestionnaireTables.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/


#include "GestionnaireTables.h"
#include "LectureFichierEnSections.h"

Table * GestionnaireTables::getTable(int id) const
{

	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
		if ((*it)->getId() == id)
			return *it;
	}
	return nullptr;
}
Table * GestionnaireTables::getMeilleureTable(int tailleGroupe) const
{
	set<Table*>::iterator it = conteneur_.begin();
	int  minNouveau = tailleGroupe;
	int   minPrecedent=1000;
	for (it; it != conteneur_.end(); it++) {
		if ((*it)->getNbPlaces() == tailleGroupe) { return *(it); }
		if ((*it)->getNbPlaces() > tailleGroupe ) { 
			minNouveau = (*it)->getNbPlaces();
		   if (minNouveau < minPrecedent) { minPrecedent = minNouveau; }
		}
	}
	return getTable(minPrecedent);
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

