/********************************************
* Titre: Travail pratique #5 - gestionnairePlats.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#include "GestionnairePlats.h"
#include "LectureFichierEnSections.h"
#include "PlatBio.h"
#include "PlatVege.h"
#include "PlatBioVege.h"



void GestionnairePlats::lirePlats(const string& nomFichier, TypeMenu type)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection(entetesDesTypesDeMenu[static_cast<int>(type)]);
	while (!fichier.estFinSection())
	 ajouter(lirePlatDe(fichier));
}

pair<string, Plat*> GestionnairePlats::lirePlatDe(LectureFichierEnSections& fichier)
{
	auto lectureLigne = fichier.lecteurDeLigne();
	Plat* plat;
	string nom, typeStr;
	TypePlat type;
	double prix, coutDeRevient;
	lectureLigne >> nom >> typeStr >> prix >> coutDeRevient;
	type = TypePlat(stoi(typeStr));
	double ecotaxe, vitamines, proteines, mineraux;
	switch (type) {
	case TypePlat::Bio:
		lectureLigne >> ecotaxe;
		plat = new PlatBio{ nom, prix, coutDeRevient, ecotaxe };
		break;
	case TypePlat::BioVege:
		lectureLigne >> ecotaxe >> vitamines >> proteines >> mineraux;
		plat = new PlatBioVege(nom, prix, coutDeRevient, ecotaxe, vitamines, proteines, mineraux);
		break;
	case TypePlat::Vege:
		lectureLigne >> vitamines >> proteines >> mineraux;
		plat = new PlatVege(nom, prix, coutDeRevient, vitamines, proteines, mineraux);
		break;
	default:
		plat = new Plat{ nom, prix, coutDeRevient };
	}
	return pair<string, Plat*>(plat->getNom(), plat);
}

void GestionnairePlats::afficherPlats(ostream & os)
{
	map<string, Plat*> p = getConteneur();
	for (auto it = p.begin(); it != p.end(); it++) {
		 (*it).second->afficherPlat(os);
	}
	//copy(conteneur_.begin(), conteneur_.end(), ostream_iterator<pair<string, Plat*>>(os, "\n"));
}

GestionnairePlats::GestionnairePlats(const string & nomFichier, TypeMenu type):type_(type)
{
	lirePlats(nomFichier,type);
	
}

GestionnairePlats::GestionnairePlats(GestionnairePlats * gestionnaire)
{
	if (this != gestionnaire) { type_ = gestionnaire->type_; }
}

GestionnairePlats::~GestionnairePlats()
{
	
}

TypeMenu GestionnairePlats::getType() const
{
	return type_;
}

Plat * GestionnairePlats::allouerPlat(Plat *)
{
	Plat* p = new Plat;
	return p;
}

Plat * GestionnairePlats::trouverPlatMoinsCher() const
{
	
	pair<string, Plat*> p= *min_element(conteneur_.begin(), conteneur_.end(), FoncteurPlatMoinsCher());
	return p.second;
}

Plat * GestionnairePlats::trouverPlatPlusCher() const
{
	auto cmp = [](pair<string, Plat* >plat1, pair<string, Plat*>plat2) {return (plat1.second->getCout() < plat2.second->getCout()); };
	pair<string, Plat*>p = *max_element(conteneur_.begin(), conteneur_.end(), cmp);
    return p.second;
}

Plat * GestionnairePlats::trouverPlat(const string & nom) const
{
	pair<string, Plat*>p= *conteneur_.find(nom);
	
	return p.second;
}

vector<pair<string, Plat*>> GestionnairePlats::getPlatsEntre(double borneInf, double borneSup)
{
	vector<pair<string, Plat*>>r;
    copy_if(conteneur_.begin(), conteneur_.end(),back_inserter(r),FoncteurIntervalle(borneInf, borneSup));
   return r ;
}
