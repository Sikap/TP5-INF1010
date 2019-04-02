/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "PlatVege.h"

PlatVege::PlatVege(string nom, double prix, double cout, double vitamines, double proteines, double mineraux)
	: Plat(nom, prix, cout), Vege(nom, vitamines, proteines, mineraux)
{
	setTaxe();
}

PlatVege::~PlatVege() {}

Plat* PlatVege::clone()const
{
	return new PlatVege(*this);
}

void PlatVege::afficherPlat(ostream & os) const
{
	Plat::afficherPlat(os);
	Vege::afficherVege(os);
	os << "(Apport nutritif  " << calculerApportNutritif() << "mg)\n";
}

double PlatVege::calculerApportNutritif() const
{
	return (vitamines_ * proteines_ / mineraux_) * RAPPORT_NUTRITIF;
}

void PlatVege::setTaxe()
{
	taxe_ = .07;
}

double PlatVege::getTaxe() const
{
	return taxe_;
}
