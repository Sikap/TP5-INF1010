/********************************************
* Titre: Travail pratique #5 - gestionnairePlats.h
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#pragma once

#include "Plat.h"
#include "Vege.h"
#include "GestionnaireGenerique.h"
#include "Foncteur.h"
#include "vector"
#include <utility>
#include <map>
#include <algorithm>
#include <functional>
#include<iterator>
using namespace std;

class GestionnairePlats: public GestionnaireGenerique<pair<string,Plat*>,map<string, Plat*>>// TODO : Ajouter l'héritage 
{
public:
	GestionnairePlats(const string& nomFichier, TypeMenu type); //TODO
	GestionnairePlats(GestionnairePlats* gestionnaire); // TODO

	~GestionnairePlats(); // TODO

	TypeMenu getType() const; // TODO

	Plat* allouerPlat(Plat*); // TODO

	Plat* trouverPlatMoinsCher() const; // TODO
	Plat* trouverPlatPlusCher() const; // TODO

	Plat* trouverPlat(const string& nom) const; // TODO
	vector<pair<string, Plat*>> getPlatsEntre(double borneInf, double borneSup); // TODO
	void lirePlats(const string& nomFichier, TypeMenu type);
	pair<string, Plat*> lirePlatDe(LectureFichierEnSections& fichier);

	void afficherPlats(ostream& os);

private:
	TypeMenu type_;
};