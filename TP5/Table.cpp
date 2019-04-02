/*
* Date : 25 février 2019
* Auteur : AbdeB
*/

#include "Table.h"
using namespace std;

// Constructeurs
Table::Table(int id, int nbPlaces) :
	id_{ id },
	nbPlaces_{ nbPlaces },
	nbClientsATable_{ 0 },
	clientPrincipal_{ nullptr }
{
}

// Getters.
int Table::getId() const
{
	return id_;
}

int Table::getNbPlaces() const
{
	return nbPlaces_;
}

bool Table::estOccupee() const
{
	return nbClientsATable_ != 0;
}

bool Table::estPleine() const
{
	return nbPlaces_ == 0;
}

int Table::getNbClientsATable() const
{
	return nbClientsATable_;
}

vector<Plat*> Table::getCommande() const
{
	return commande_;
}

Client* Table::getClientPrincipal() const
{
	return clientPrincipal_;
}


// Setters.

void Table::setId(int id)
{
	id_ = id;
}

void Table::setClientPrincipal(Client * clientPrincipal)
{
	clientPrincipal_ = clientPrincipal;
}

void Table::libererTable()
{
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	commande_.clear();
}

void Table::placerClients(int nbClient)
{
	nbPlaces_ -= nbClient;
	nbClientsATable_ = nbClient;
}


// Autres methodes.
void Table::commander(Plat* plat)
{
	commande_.push_back(plat);
}

double Table::getChiffreAffaire() const
{
	double chiffre = 0;
	for (unsigned i = 0; i < commande_.size(); ++i)
		chiffre += commande_[i]->getPrixRevient();
	return chiffre;
}


ostream& operator<<(ostream& os, const Table& table)
{
	os << "La table numero " << table.id_;
	if (table.estOccupee()) {
		os << " est occupee. Le client principal est:" << endl;
		os << table.getClientPrincipal()->getNom() << endl;;

		if (!table.commande_.empty()) {
			os << "Voici la commande passee par les clients :" << endl;
			for (Plat* plat : table.commande_) {
				os << "\t";
				plat->afficherPlat(os);
			}
		}
		else
			os << "Mais ils n'ont rien commande pour l'instant." << endl;
	}
	else
		os << " est vide. " << endl;

	return os;
}
