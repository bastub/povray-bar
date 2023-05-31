#version 3.7;

// 0 - Imports

#include "elements.inc"
#include "technical.inc"

// 1 - Mise en scène

plane {
    y, 0
    pigment { color rgb <0.5, 0.5, 0.5> }
}

sky_sphere {
    pigment {
        bozo
    }
}

object {
    As_Pique
    rotate <90, 0, 0>
    translate<0, .02, 0>
}

object {
    Reine_Coeur
    rotate <90, 30, 0>
    translate<0, .04, 0>
}

object {
    Reine_Coeur
    rotate <270, 46, 0>
    translate<17, 0, 15>
}

object {
    H_Socle
    translate <10, 0, 0>
    rotate <0, 27, 0>
}

object {
    H_Corne 
    translate <0, 5, 0>
}