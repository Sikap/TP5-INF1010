/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "Plat.h"

Plat::Plat(string_view nom, double prix, double cout) : nom_(nom), prix_(prix), cout_(cout) {}

Plat::~Plat() {}

// Getters 
string Plat::getNom() const {
	return nom_;
}

double Plat::getPrix() const {
	return prix_;
}

double Plat::getCout() const {
	return cout_;
}

// Setters 
void Plat::setNom(string nom) {
	nom_ = nom;
}

void Plat::setPrix(double prix) {
	prix_ = prix;
}

bool Plat::operator < (const Plat& plat) const
{
	return prix_ < plat.prix_;
}

void Plat::afficherPlat(ostream & os) const
{
	os << "PLAT ----" << nom_ << " - " << prix_ << " $ (" << cout_ << "$ pour le restaurant)" << endl;
}

double Plat::getPrixRevient()
{
	return prix_ - cout_;
}

Plat* Plat::clone() const
{
	return new Plat(*this);
}
