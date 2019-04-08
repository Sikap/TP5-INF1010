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
	menuMatin_ = new GestionnairePlats("menu.txt", TypeMenu::Matin);
	tables_= new GestionnaireTables();
	tables_->lireTables("menu.txt");
	
	
}

Restaurant::Restaurant(const string& nomFichier, string_view nom, TypeMenu moment) :
	nom_{ nom },
	momentJournee_{ moment },
	chiffreAffaire_{ 0 },
	fraisLivraison_{}
{
	menuMatin_ = new GestionnairePlats(nomFichier, TypeMenu::Matin);
	menuMidi_= new GestionnairePlats(nomFichier, TypeMenu::Midi);
	menuSoir_= new GestionnairePlats(nomFichier, TypeMenu::Soir);
	tables_ = new GestionnaireTables();
	tables_->lireTables(nomFichier);
	menuActuel()->lirePlats(nomFichier, moment);
	lireAdresses(nomFichier);
	
}

// Destructeur.
Restaurant::~Restaurant()
{
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;
	for (Table* table : tables_->getConteneur())
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


// Autres methodes.

void Restaurant::libererTable(int id)
{
	Table* t = tables_->getTable(id);
	chiffreAffaire_ += t->getChiffreAffaire();
	chiffreAffaire_ += calculerReduction(t->getClientPrincipal(), t->getChiffreAffaire(), id == ID_TABLE_LIVRAISON);
	t->libererTable();
	
}

ostream& operator<<(ostream& os, const Restaurant& restaurent)
{
	os << "Le restaurant " << restaurent.getNom();
	if (restaurent.chiffreAffaire_ != 0)
		os << " a fait un chiffre d'affaire de : " << restaurent.chiffreAffaire_ << "$" << endl;
	else
		os << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;

	os << "-Voici les tables : " << endl;

	for (Table* table : restaurent.tables_->getConteneur())
		os << *table << endl;

	os << "-Voici son menu : " << endl;
	for (TypeMenu typeMenu : { TypeMenu::Matin, TypeMenu::Midi, TypeMenu::Soir }) {
		GestionnairePlats* menu = restaurent.getMenu(typeMenu);
		os << restaurent.getNomTypeMenu(typeMenu)<< " : " << endl;;
		menu->afficherPlats(os);
		os << endl << "Le plat le moins cher est : ";
		menu->trouverPlatMoinsCher()->afficherPlat(os);
		os << endl;
	}
	return os;
}
void Restaurant::commanderPlat(string_view nom, int idTable)
{
	if (Table* table = getTable(idTable); table && table->estOccupee())
	
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
	Table* MeilleureTable = tables_->getMeilleureTable(tailleGroupe);
	//TODO : Si possible assigner la table au client sinon retourner false.
	if (MeilleureTable == nullptr) { return false; }
	client->setTable(MeilleureTable);
	MeilleureTable->setClientPrincipal(client);
	MeilleureTable->placerClients(tailleGroupe);

	return true;
}

bool Restaurant::livrerClient(Client* client, const vector<string>& commande)
{
	if (dynamic_cast<ClientPrestige*>(client)) {
		// TODO: Placer le client principal a la table fictive en utilisant la classe GestionnaireTables.
		//tables_->getTable(INDEX_TABLE_LIVRAISON)->setClientPrincipal(client);
		Table* table = tables_->getTable(ID_TABLE_LIVRAISON);
		table->setClientPrincipal(client);
		// tables_[INDEX_TABLE_LIVRAISON]->setClientPrincipal(client); // L'appel du TP4
		// TODO: Placer client à la table fictive en utilisant la classe GestionnaireTables.
		table->placerClients(1);
		// tables_[INDEX_TABLE_LIVRAISON]->placerClients(1); // L'appel du TP4
		// Placer la commande
		for (unsigned int i = 0; i < commande.size(); i++)
			commanderPlat(commande[i], INDEX_TABLE_LIVRAISON);
		// Liberer la table fictive.
		libererTable(ID_TABLE_LIVRAISON);
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
	switch (zone) {
	case ZoneHabitation::Zone1: return 0;
	case ZoneHabitation::Zone2: return 1;
	case ZoneHabitation::Zone3: return 2;
   }
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

Table* Restaurant::getTable(int id) const
{

	return tables_->getTable(id);

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

GestionnaireTables * Restaurant::getTables() const
{
	return tables_;
}

string Restaurant::getNomTypeMenu(TypeMenu typeMenu) const
{
	switch(typeMenu) {
	case TypeMenu::Matin: return "Matin";
	case TypeMenu::Midi: return "Midi";
	case TypeMenu::Soir: return "Soir";
	}
}
