#ifndef DEF_H
#define DEF_H
#include<string_view>
using namespace std;
enum class TypeMenu { Matin, Midi, Soir, first_ = Matin, last_ = Soir };
static const string_view nomsDesTypesDeMenu[] = { "Matin", "Midi", "Soir" };
static const string_view entetesDesTypesDeMenu[] = { "-MATIN", "-MIDI", "-SOIR" }; // Pour le format du fichier.
enum class ZoneHabitation { Zone1, Zone2, Zone3, first_ = Zone1, last_ = Zone3 };
enum class TypePlat { Normal = 0, Bio = 1, Vege = 2, BioVege = 3, first_ = Normal, last_ = BioVege };
const double TAUX_REDUC_REGULIER = 0.1;
const double TAUX_REDUC_PRESTIGE = 0.2;
const double SEUIL_DEBUT_REDUCTION = 75;
const double SEUIL_LIVRAISON_GRATUITE = 200;
const double RAPPORT_NUTRITIF_BIO = 0.9;
const double AVANTAGE_SANS_PESTICIDE = 1.5;
const double RAPPORT_NUTRITIF = 0.8;
const int NB_ZONES_LIVR = static_cast <int>(ZoneHabitation::Zone3) + 1;
const int INDEX_TABLE_LIVRAISON = 4;
const int ID_TABLE_LIVRAISON = INDEX_TABLE_LIVRAISON + 1;

#endif
