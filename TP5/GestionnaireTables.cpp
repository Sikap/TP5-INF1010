/********************************************
* Titre: Travail pratique #5 - gestionnaireTables.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/


#include "GestionnaireTables.h"
#include "LectureFichierEnSections.h"


Table * GestionnaireTables::getTable(int id) const
{

	/*for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
		if ((*it)->getId() == id)
			return *it;
	}
	return nullptr;*/
	auto cmp_ID = [=](Table*Table) {return (Table->getId() == id); };
	Table* t= *find_if(conteneur_.begin(), conteneur_.end(), cmp_ID);
	if (t == nullptr) { return nullptr; }
	else return t;
}
Table * GestionnaireTables::getMeilleureTable(int tailleGroupe) const
{
	vector<Table*> t;
	auto sup_Egale_TailleGroupe = [=](Table*Table) {return (Table->getNbPlaces()>= tailleGroupe&& !Table->estOccupee()); };
	copy_if(conteneur_.begin(), conteneur_.end(), back_inserter(t), sup_Egale_TailleGroupe);
	if (t.empty()) { return nullptr; }

	auto cmp_NbPlaces = [](Table*Table1, Table*Table2) {return(Table1->getNbPlaces() < Table2->getNbPlaces());};
	auto min= min_element(t.begin(), t.end(),cmp_NbPlaces);

	return getTable((*min)->getId());
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

