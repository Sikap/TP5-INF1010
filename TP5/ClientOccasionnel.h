/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#ifndef CLIENT_OCCASIONNEL
#define CLIENT_OCCASIONNEL

#include "Client.h"

class ClientOccasionnel : public Client
{
public:
	ClientOccasionnel(string_view nom, string_view prenom, int tailleGroupe);
	virtual ~ClientOccasionnel();
	virtual int getNbPoints() const;
	virtual void afficherClient(ostream & os) const;
	virtual double getReduction(const Restaurant & res, double montant, bool estLivraison);
};

#endif
