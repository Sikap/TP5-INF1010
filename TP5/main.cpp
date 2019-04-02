/*
* Date : 25 février 2019
* Auteur : AbdeB
*/

#include "Restaurant.h"
#include "ClientPrestige.h"
#include "ClientOccasionnel.h"
#include "debogageMemoire.hpp"

#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	initDebogageMemoire();

	vector<bool> tests;
	Restaurant poly("polyfood.txt", "PolyFood", TypeMenu::Soir);

	// Test 1 - Initialisations des gestionnaires de plats
	tests.push_back((poly.getMenu(TypeMenu::Matin)->getType() == TypeMenu::Matin)
		&& (poly.getMenu(TypeMenu::Midi)->getType() == TypeMenu::Midi)
		&& (poly.getMenu(TypeMenu::Soir)->getType() == TypeMenu::Soir));

	/*
	* Tests gestionnaire generique
	*/
	// Test 2 -Nombre d'elements
	tests.push_back((poly.getMenu(TypeMenu::Matin)->getNombreElements() == 7)
		&& (poly.getMenu(TypeMenu::Midi)->getNombreElements() == 6)
		&& (poly.getMenu(TypeMenu::Soir)->getNombreElements() == 5)
		&& (poly.getTables()->getNombreElements() == 6));

	// Test 3 - Ajouter et trouver plat
	pair<string, Plat*> poke("Poke", new Plat("Poke", 14.5, 9));
	poly.getMenu(TypeMenu::Midi)->ajouter(poke);
	tests.push_back(poly.getMenu(TypeMenu::Midi)->trouverPlat("Poke") == poke.second);

	/*
	* Tests gestionnaire plats
	*/
	// Test 4 - Plat moins cher
	tests.push_back(poly.getMenu(TypeMenu::Matin)->trouverPlatMoinsCher()->getNom() == "Pain");

	// Test 5 - Plat plus cher
	tests.push_back(poly.getMenu(TypeMenu::Soir)->trouverPlatPlusCher()->getNom() == "Poisson");

	// Test 6 - Plat dans interval
	vector<pair<string, Plat*>> platsDansIntervalle = poly.getMenu(TypeMenu::Midi)->getPlatsEntre(6, 14);
	tests.push_back(platsDansIntervalle.size() == 4
		&& platsDansIntervalle[0].second->getNom() == "Nachos"
		&& platsDansIntervalle[3].second->getNom() == "Ratatouille");

	/*
	* Tests gestionnaire plats
	*/

	// Test 7 - Table par id
	Table* table = new Table(10, 8);
	poly.getTables()->ajouter(table);
	tests.push_back(poly.getTables()->getTable(10) == table);

	// Test 8 - 9 - Meilleure table
	tests.push_back(poly.getTables()->getMeilleureTable(8) == table);
	tests.push_back(poly.getTables()->getMeilleureTable(4)->getId() == 2);

	/*
	* Tests restaurant
	*/
	vector<Client*> clients;
	clients.push_back(new ClientOccasionnel("Martin", "b", 2));
	clients.push_back(new ClientOccasionnel("Amy", "wh", 15));
	clients.push_back(new ClientRegulier("John", "sm", 5, 105));
	clients.push_back(new ClientRegulier("Moussa", "T", 3, 45));
	clients.push_back(new ClientPrestige("Andree", "F", 2, 150, ZoneHabitation::Zone2));
	clients.push_back(new ClientPrestige("Marie", "C", 1, 225, ZoneHabitation::Zone1));

	// Test 10 - 15 - Placer client
	vector<bool> testPlacerClients;
	testPlacerClients.push_back(true);
	testPlacerClients.push_back(false);
	testPlacerClients.push_back(true);
	testPlacerClients.push_back(true);
	testPlacerClients.push_back(true);
	testPlacerClients.push_back(true);

	for (int i = 0; i < clients.size(); i++) {
		tests.push_back(poly.placerClients(clients[i]) == testPlacerClients[i]);
	}

	// Test 16 - 17 - Livrer client
	vector<string> commandeMartin;
	commandeMartin.push_back("Poisson");
	commandeMartin.push_back("Muffin");
	vector<string> commandeMarie;
	commandeMarie.push_back("Pates");
	commandeMarie.push_back("Poulet");
	commandeMarie.push_back("Pizza");

	//Ne devrait pas pouvoir se faire livrer
	tests.push_back(!poly.livrerClient(clients[0], commandeMartin));

	//Doit pouvoir se faire livrer
	tests.push_back(poly.livrerClient(clients[5], commandeMarie));

	// Test 18 - 20 - Commander plat
	poly.commanderPlat("Pates", clients[0]->getTable()->getId());

	poly.commanderPlat("Pates", clients[2]->getTable()->getId());

	poly.commanderPlat("Poisson", clients[3]->getTable()->getId());

	poly.commanderPlat("Poisson", clients[4]->getTable()->getId());

	poly.commanderPlat("Muffin", clients[5]->getTable()->getId());
	poly.commanderPlat("Pizza", clients[5]->getTable()->getId());

	tests.push_back(clients[2]->getTable()->getCommande().size() == 1
		&& clients[2]->getTable()->getCommande()[0]->getNom() == "Pates");

	tests.push_back(clients[3]->getTable()->getCommande().size() == 1
		&& clients[3]->getTable()->getCommande()[0]->getNom() == "Poisson");

	tests.push_back(clients[5]->getTable()->getCommande().size() == 2
		&& clients[5]->getTable()->getCommande()[0]->getNom() == "Muffin"
		&& clients[5]->getTable()->getCommande()[1]->getNom() == "Pizza");

	// Test 21
	//tests.push_back(poly.);
	tests.push_back(poly.getTables()->getTable(1)->estOccupee());
	poly.libererTable(1);
	tests.push_back(!poly.getTables()->getTable(1)->estOccupee());

	tests.push_back(poly.getTables()->getTable(3)->estOccupee());
	poly.libererTable(3);
	tests.push_back(!poly.getTables()->getTable(3)->estOccupee());

	/*
	* Affichage des tests
	*/
	
	cout << "TESTS" << endl;
	for (unsigned int i = 0; i < tests.size(); i++)
	{
		cout << "\tTest " << setfill('0') << setw(2) << i + 1 << "... ";
		if (tests[i])
			cout << "OK!" << endl;
		else
			cout << "ECHEC" << endl;
	}

	// Pour tester l'affichage
	//cout << poly;
	
	return 0;
}
