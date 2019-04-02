/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "ClientRegulier.h"

ClientRegulier::ClientRegulier() : nbPoints_(0) {}

ClientRegulier::ClientRegulier(string_view nom, string_view prenom, int tailleGroupe, int npoints)
	: Client(nom, prenom, tailleGroupe), nbPoints_(npoints) {}

ClientRegulier:: ~ClientRegulier() {}

int ClientRegulier::getNbPoints() const
{
	return nbPoints_;
}

void ClientRegulier::augmenterNbPoints(int bonus)
{
	nbPoints_ += bonus;
}

void ClientRegulier::afficherClient(ostream & os) const
{
	Client::afficherClient(os);
	os << " statut: " << "Regulier" << std::endl;
	os << "\tPossede " << nbPoints_ << " points.";
	os << std::endl;
}

double ClientRegulier::getReduction(const Restaurant & res, double montant, bool estLivraison)
{
	double reduction = 0.0;

	if (getNbPoints() > SEUIL_DEBUT_REDUCTION)
		reduction = (-montant * TAUX_REDUC_REGULIER);

	return reduction;
}
