/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "Vege.h"

Vege::Vege(string nom, double vitamines, double proteines, double mineraux)
	: nom_(nom), vitamines_(vitamines), proteines_(proteines), mineraux_(mineraux)
{
}

double Vege::getVitamines()
{
	return vitamines_;
}

double Vege::getProteines()
{
	return proteines_;
}

double Vege::getMineraux()
{
	return mineraux_;
}

void Vege::setVitamines(double vitamines)
{
	vitamines_ = vitamines;
}

void Vege::setProteines(double proteines)
{
	proteines_ = proteines;
}

void Vege::setMineraux(double mineraux)
{
	mineraux_ = mineraux;
}

void Vege::afficherVege(ostream & os) const
{
	os << "PLAT VEGE " << nom_ << " \t";
	os << "vitamines " << vitamines_ << " Proteines " << proteines_
		<< " Mineraux " << mineraux_ << endl;
}


