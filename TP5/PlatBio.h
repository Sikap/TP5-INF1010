/*
* Date : 25 février 2019
* Auteur : AbdeB
*/

#ifndef PLAT_BIO_H
#define PLAT_BIO_H

#include <string>
#include <iostream>
#include "Plat.h"

using namespace std;

class PlatBio : public Plat {
public:
	// Constructeur
	PlatBio(string nom = "inconnu", double prix = 0, double cout = 0, double ecotaxe = 0);
	virtual ~PlatBio();

	// Getters 
	double getEcoTaxe() const;

	// Setters 
	void setEcoTaxe(double ecoTaxe);
	virtual void afficherPlat(ostream& os) const; 
	virtual  double getPrixDeRevient(); 
	virtual Plat * clone() const;

protected:
	double ecoTaxe_;

};

#endif // !PLAT_BIO_H
