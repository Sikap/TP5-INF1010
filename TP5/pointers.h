#pragma once
// Extrait de GSL ( Copyright (c) 2015 Microsoft Corporation, sous licence MIT )

//? "owner" ne change rien à la compilation du programme 
//mais permet d'indiquer qui est propriétaire de la mémoire.  
//Par exemple, le type "owner<int*>" est équivalent à "int*", 
//mais permet facilement au programmeur de savoir qu'il faudra faire un "delete" sur 
//ce pointeur (ou le passer à un autre "owner" qui fera le "delete").
template <class T, class = std::enable_if_t<std::is_pointer<T>::value>>
using owner = T;
