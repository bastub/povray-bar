#version 3.7

#include "elements.inc"
#include "technical.inc"
#include "decor.inc"

// 1 unitée = 1cm

// 5 - Mise en scène
object{Sol}
object{Mur}
object{Comptoir translate <0,0,110>}
object{Cible}
object{Banniere translate <20,160,0>}
object{Wanted}
object {
    Bouteille 
    rotate <0, 60, 0>
    translate <190, 120, 229>
}
object {
    Telephone 
    rotate <0, 260, 0>    
    translate <200, 120, 235>
}
object {
    Corne1
    rotate <0, 110, 0>
    translate <190, 120, 160>
}
object {
    Jenga
    rotate <0, 10, 0>
    translate <190, 120, 120>
}
object {
    Corne2
    rotate <0, -15, 0>
    translate <150, 120, 120>
}
object {
    As_Pique
    rotate <90, 0, 0>
    translate<80, 120.02, 120>
}
object {
    Reine_Coeur
    rotate <90, 30, 0>
    translate<80, 120.04, 120>
}
object {
    Reine_Coeur
    rotate <270, 46, 0>
    translate<97, 120, 135>
}

