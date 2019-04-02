/*
* Date : 25 fevrier 2019
* Auteur : AbdeB
*/
#ifndef CLIENT_REG
#define CLIENT_REG

#include "Client.h"
#include "def.h"

class ClientRegulier : public Client
{
public:
	ClientRegulier();
	ClientRegulier(string_view nom, string_view prenom, int tailleGroupe, int nbPoints);
	virtual ~ClientRegulier();

	//Accesseurs
	virtual int getNbPoints() const;

	//Autres Methodes
	void augmenterNbPoints(int bonus);
	virtual void afficherClient(ostream & os) const;
	virtual double getReduction(const Restaurant & res, double montant, bool estLivraison);

protected:
	int nbPoints_;
};

#endif
