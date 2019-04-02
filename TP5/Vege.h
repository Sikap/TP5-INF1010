/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#ifndef VEGE_H
#define VEGE_H
#include <iostream>
#include <string_view>
#include <string>
#include"Taxable.h"
using namespace std;
class Vege
{
public:
	Vege(string nom, double vitamines, double proteines, double mineraux);
	double getVitamines();
	double getProteines();
	double getMineraux();
	void setVitamines(double vitamines);
	void setProteines(double proteines);
	void setMineraux(double mineraux);
	void afficherVege(ostream & os)const;
	virtual double calculerApportNutritif() const = 0;

protected:
	double vitamines_;
	double proteines_;
	double mineraux_;
	string nom_;
};
#endif
