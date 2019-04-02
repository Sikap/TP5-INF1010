/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "PlatBio.h"

PlatBio::PlatBio(string nom, double prix, double cout, double ecotaxe)
	: Plat(nom, prix, cout), ecoTaxe_(ecotaxe) {}

PlatBio::~PlatBio() {}

double PlatBio::getEcoTaxe() const
{
	return ecoTaxe_;
}

void PlatBio::setEcoTaxe(double ecoTaxe)
{
	ecoTaxe_ = ecoTaxe;
}

Plat * PlatBio::clone() const
{
	return new PlatBio(*this);
}

double PlatBio::getPrixDeRevient()
{
	return getPrix() - getCout() + getEcoTaxe();
}

void PlatBio::afficherPlat(ostream& os) const
{
	Plat::afficherPlat(os);
	os << "Plat Bio \tcomprend une Taxe ecologique de :" << ecoTaxe_ << "$" << endl;
}
