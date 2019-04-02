/*
* Titre : Table.h - Travail Pratique #3
* Date : 5 Fevrier 2019
* Auteur : Fatou S. Mounzeo
*/

#ifndef TABLE_H
#define TABLE_H

#include "Plat.h"
#include "Client.h"
#include <vector>

class Client;
class Table {
public:
	// Constructeur
	Table(int id = -1, int nbPlaces = 1);

	// Getters
	int getId() const;
	int getNbPlaces() const;
	bool estOccupee() const;
	bool estPleine() const;
	int getNbClientsATable() const;
	vector<Plat*> getCommande() const;
	Client* getClientPrincipal() const;
	double getChiffreAffaire() const;


	// Setters
	void libererTable();
	void placerClients(int nbClients);
	void setId(int id);
	void setClientPrincipal(Client* clientPrincipal);

	// Autres methodes
	void commander(Plat* plat);

	friend ostream& operator<<(ostream& os, const Table& table);

private:
	vector<Plat*> commande_;
	int id_;
	int nbPlaces_;
	int nbClientsATable_;
	Client* clientPrincipal_;
};
#endif // !TABLE_H
