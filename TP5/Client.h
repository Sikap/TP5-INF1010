#ifndef CLIENT_H
#define CLIENT_H

#include "Table.h"
#include "def.h"

#include <string>
#include <string_view>
#include <iostream>

using namespace std;  //? On ne devrait normalement pas faire de "using" global dans un .h, mais c'est accepte en INF1010.

class Restaurant;
class Table;
class Client
{
public:
	Client();
	Client(string_view nom, string_view prenom, int tailleGroupe);
	virtual ~Client() {};
	//getters
	int getTailleGroupe() const;
	string getNom() const;
	string getPrenom() const;
	Table * getTable()const;
	// setters
	void setTable(Table * table);
	//affichage
	virtual int getNbPoints() const = 0;
	virtual void afficherClient(ostream & os) const = 0;
	virtual double getReduction(const Restaurant & res, double montant, bool estLivraison) = 0;

protected:
	string nom_;
	string prenom_;
	int tailleGroupe_;
	Table * tableOccupee_;
};
#endif

