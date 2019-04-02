/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "PlatBioVege.h"

PlatBioVege::PlatBioVege(string nom, double prix, double cout, double ecotaxe, double vitamines, double proteines, double mineraux) :
	PlatBio(nom, prix, cout, ecotaxe), Vege(nom, vitamines, proteines, mineraux)
{
}
PlatBioVege:: ~PlatBioVege() {}

Plat * PlatBioVege::clone() const
{
	return new PlatBioVege(*this);
}

double PlatBioVege::calculerApportNutritif() const
{
	return (vitamines_ * proteines_ / mineraux_) * RAPPORT_NUTRITIF_BIO * AVANTAGE_SANS_PESTICIDE;
}

void PlatBioVege::afficherPlat(ostream & os) const
{
	PlatBio::afficherPlat(os);
	os << "ET ";
	Vege::afficherVege(os);
}
