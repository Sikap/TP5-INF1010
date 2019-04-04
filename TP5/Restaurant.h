
/*
* Titre : Restaurant.h - Travail Pratique #1
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Table.h"
#include "Client.h"
#include "ClientPrestige.h"
#include "pointers.h"
#include "GestionnaireTables.h"
#include "GestionnairePlats.h"
#include "def.h"

#include <string_view>
#include <iostream>
using namespace std;
class Client;
class Table;
class Restaurant {
public:
	// Constructeurs.

	Restaurant();
	Restaurant(const string& nomFichier, string_view nom, TypeMenu moment);
	Restaurant(const Restaurant& autre) = delete;  //? Le programme ne fait jamais de copie de restaurant,
                                                   //donc cette methode n"est jamais cree par defaut par le compilateur
    
	// Destructeur.
	~Restaurant();

	// Setters.

	void setMoment(TypeMenu moment);
	void setNom(string_view nom); 
    void setChiffreAffaire( double chiffre);
	// Getters.

	string getNom() const;
	TypeMenu getMoment() const;
    double getChiffreAffaire();
	GestionnaireTables* getTables() const; // TODO : À implémenter
	GestionnairePlats* getMenu(TypeMenu typeMenu) const; // TODO: retourner un GestionnairePlats* a la place
	double getFraisLivraison(ZoneHabitation zone) const;
    string getNomTypeMenu(TypeMenu typeMenu);

	// Autres methodes.
	void lireAdresses(const string& fichier);
	void libererTable(int id);


	void commanderPlat(string_view nom, int idTable);
	bool operator <(const Restaurant& restau) const ;
	Restaurant& operator=(const Restaurant& autre) = delete;  //? Le programme ne fait jamais de copie de restaurant, donc cette fonction n'�tait pas test�e et par cons�quent probablement �rron�e.
	
	bool placerClients(Client* client);
	bool livrerClient(Client* client, const vector<string>& nomPlats);
	
	double calculerReduction(Client* client, double montant, bool livraison);
	//friend ostream& operator<<(ostream& os, const Restaurant& restau);
	friend ostream& operator<<(ostream& os, const Restaurant& restaurent);

private:
	GestionnairePlats* menuActuel() const; // TODO : retourner GestionnairePlats 
	GestionnaireTables* getTable(int id) const; // TODO : À retirer, utiliser GestionnaireTables

	string nom_;
	TypeMenu momentJournee_;
	double chiffreAffaire_;

	// TODO : Retirer les Menu et utiliser des GestionnairePlats* à la place.
	// Differents menus en fonction du moment de la journ�e.
	owner<GestionnairePlats *> menuMatin_;  //? "owner" est juste un indicateur que la classe est propri�taire des menus (et devra faire un "delete"), mais owner<Menu*> est �quivalent � Menu*; voir pointers.h .
    owner<GestionnairePlats *> menuMidi_;
	owner<GestionnairePlats *> menuSoir_;
	
	// Liste des tables.
	// TODO: Retirer ce vecteur et utiliser un GestionnaireTables à la place.
	owner < GestionnaireTables*>tables_;  //? "owner" est juste un indicateur que la classe est propri�taire des tables (et devra faire un "delete"), mais owner<Table*> est �quivalent � Table*; voir pointers.h .

	// Tarif des trois zones de livraison.
	double fraisLivraison_[NB_ZONES_LIVR]; 
};


#endif // !RESTAURANT_H
