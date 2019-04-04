/********************************************
* Titre: Travail pratique #5 - GestionnaireGenerique.h
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#pragma once

#include <algorithm>
#include "Foncteur.h"

using namespace  std;

//              T   = pair<string, Plat*> ou Table*; 
//              C   = map<string, Plat*> ou set<Table*>; 
template<typename T, typename C>
class GestionnaireGenerique
{
public:
	
	C getConteneur() const {return conteneur_;}//TODO
	inline void ajouter(T t) {
	     conteneur_.insert(t);
	}//TODO
	int getNombreElements() const { return conteneur_.size(); }//TODO

protected:
	C conteneur_;
};
