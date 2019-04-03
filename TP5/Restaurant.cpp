/*
* Date : 25 f�vrier 2019
* Auteur : AbdeB
*/

#include "Restaurant.h"
#include "LectureFichierEnSections.h"
#include "debogageMemoire.hpp"
#include <cassert>
using namespace std;

//constructeurs 
Restaurant::Restaurant() :
	Restaurant{ "menu.txt", "Inconnu", TypeMenu::Matin }
{
}

Restaurant::Restaurant(const string& nomFichier, string_view nom, TypeMenu moment) :
	nom_{ nom },
	momentJournee_{ moment },
	chiffreAffaire_{ 0 },
	fraisLivraison_{}
{
	menuMatin_->lirePlats(nomFichier, TypeMenu::Matin);
	menuMidi_->lirePlats(nomFichier, TypeMenu::Midi);
	menuSoir_->lirePlats(nomFichier, TypeMenu::Soir);
	menuActuel();
	lireAdresses(nomFichier);
}

// Destructeur.
Restaurant::~Restaurant()
{
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;
	for (GestionnaireTables* table : tables_)
		delete table;
}


// Setters.

void Restaurant::setMoment(TypeMenu moment)
{
	momentJournee_ = moment;
}

void Restaurant::setNom(string_view nom)
{
	nom_ = nom;
}

void  Restaurant::setChiffreAffaire(double chiffre)
{
	chiffreAffaire_ = chiffre;
}
// Getters.

string Restaurant::getNom() const
{
	return nom_;
}

TypeMenu Restaurant::getMoment() const
{
	return momentJournee_;
}

/*double Restaurant::getFraisLivraison(int index) const
{
	return fraisLivraison_[index];
}
*/

// Autres methodes.

void Restaurant::libererTable(int id)
{
	
	if (GestionnaireTables* table = getTable(id)) {
		chiffreAffaire_ += table->getTable(id)->getChiffreAffaire();
		chiffreAffaire_ += calculerReduction(table->getTable(id)->getClientPrincipal(), table->getTable(id)->getChiffreAffaire(), id == tables_[INDEX_TABLE_LIVRAISON]->getTable(INDEX_TABLE_LIVRAISON)->getId());
		table->getTable(id)->libererTable();
	}
}

ostream& operator<<(ostream& os, const Restaurant& restaurent)
{
	os << "Le restaurant " << restaurent.getNom();
	if (restaurent.chiffreAffaire_ != 0)
		os << " a fait un chiffre d'affaire de : " << restaurent.chiffreAffaire_ << "$" << endl;
	else
		os << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;

	os << "-Voici les tables : " << endl;

	for (GestionnaireTables* table : restaurent.tables_)
		table->afficherTables(os);
	    os << endl;
		
	os << "-Voici son menu : " << endl;
	for (TypeMenu typeMenu : { TypeMenu::Matin, TypeMenu::Midi, TypeMenu::Soir }) {
		GestionnairePlats* menu = restaurent.getMenu(typeMenu);
		//os<< getNomTypeMenu(typeMenu) << " : " << endl;
			menu->afficherPlats(os) ;
			os << "Le plat le moins cher est : ";
		menu->trouverPlatMoinsCher()->afficherPlat(os);
		os << endl;
	}
	return os;
}

void Restaurant::commanderPlat(string_view nom, int idTable)
{
	if (Table* table = getTable(idTable)->getTable(idTable); table && table->estOccupee())
			
		if (Plat* plat = menuActuel()->trouverPlat(std::string(nom).c_str())) {
			table->commander(plat);
			return;
		}
	cout << "Erreur : table vide ou plat introuvable." << endl << endl;
}

bool Restaurant::operator <(const Restaurant& autre) const
{
	return chiffreAffaire_ < autre.chiffreAffaire_;
}


bool Restaurant::placerClients(Client* client)
{
	const int tailleGroupe = client->getTailleGroupe();
	//TODO : trouver la table la plus adaptée pour le client. 
	tables_[tailleGroupe]->getMeilleureTable(tailleGroupe);
	//TODO : Si possible assigner la table au client sinon retourner false.
	client->setTable(tables_[tailleGroupe]->getMeilleureTable(tailleGroupe));
	if (tables_[tailleGroupe]->getMeilleureTable(tailleGroupe) == nullptr) { return false; }
}

bool Restaurant::livrerClient(Client* client, const vector<string>& commande)
{
	if (dynamic_cast<ClientPrestige*>(client)) {
		// TODO: Placer le client principal a la table fictive en utilisant la classe GestionnaireTables.
		tables_[INDEX_TABLE_LIVRAISON]->getTable(INDEX_TABLE_LIVRAISON)->setClientPrincipal(client);
		// tables_[INDEX_TABLE_LIVRAISON]->setClientPrincipal(client); // L'appel du TP4
		// TODO: Placer client à la table fictive en utilisant la classe GestionnaireTables.
		tables_[INDEX_TABLE_LIVRAISON]->getTable(INDEX_TABLE_LIVRAISON)->placerClients(client->getTailleGroupe());
		// tables_[INDEX_TABLE_LIVRAISON]->placerClients(1); // L'appel du TP4
		// Placer la commande
		for (unsigned int i = 0; i < commande.size(); i++)
			commanderPlat(commande[i], INDEX_TABLE_LIVRAISON);
		// Liberer la table fictive.
		libererTable(INDEX_TABLE_LIVRAISON);
		return true;
	}
	else {
		return false;
	}
}

double Restaurant::calculerReduction(Client* client, double montant, bool estLivraison)
{
	return client->getReduction(*this, montant, estLivraison);
}

double Restaurant::getFraisLivraison(ZoneHabitation zone) const
{
	return fraisLivraison_[static_cast<int>(zone)];
}

GestionnairePlats* Restaurant::getMenu(TypeMenu typeMenu) const
{
	switch (typeMenu) {
	case TypeMenu::Matin: return menuMatin_;
	case TypeMenu::Midi: return menuMidi_;
	case TypeMenu::Soir: return menuSoir_;
	}
	assert(false && "Le type du menu est invalide");
	return nullptr;  // On ne devrait jamais se rendre � cette ligne.
}

GestionnairePlats* Restaurant::menuActuel() const
{
	return getMenu(momentJournee_);
}

GestionnaireTables* Restaurant::getTable(int id) const
{
	return tables_[id];

}


void Restaurant::lireAdresses(const string& nomFichier)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection("-ADDRESSES");
	while (!fichier.estFinSection()) {
		int zone; double frais;
		fichier >> zone >> frais;
		fraisLivraison_[zone] = frais;
	}
}

double Restaurant::getChiffreAffaire() {
	return chiffreAffaire_;

}

string Restaurant::getNomTypeMenu(TypeMenu typeMenu)
{
	return string{ nomsDesTypesDeMenu[static_cast<int>(typeMenu)] };
}
