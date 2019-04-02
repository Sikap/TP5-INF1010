/********************************************
* Titre: Travail pratique #5 - Foncteur.h
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#pragma once

#include <algorithm>
#include "Plat.h"

using namespace std;


class FoncteurPlatMoinsCher
{ 

public:
	FoncteurPlatMoinsCher() {};
     bool operator()(pair<string, Plat* >plat1, pair<string, Plat*>plat2){
		return plat1.second->getPrix() <plat2.second->getPrix();
	}

};

class FoncteurIntervalle
{
         // TODO
public:
	FoncteurIntervalle(double inf, double Sup) :borne_Inf_(inf), borne_Sup_(Sup){};
	bool operator()(pair<string, Plat* > p){
		return (borne_Inf_ <= p.second->getPrix() && p.second->getPrix()<= borne_Sup_);
	}
private:
double  borne_Inf_;
double  borne_Sup_;
};

