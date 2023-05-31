#include "colors.inc"
#include "textures.inc"
#include "woods.inc"


// 0 - Variables

#declare V_Arrondi_Carte = .4;
#declare V_Arrondi_Socle = 1;

// 1 - Modélisation géométrique

#declare G_Carte = box {
    <0, 0, 0>, <1, 1, 1>   
}

#declare G_Carte_Clipper = difference {
    box {
        <0, 0, -1>, <1, 1, 1>
    }
    cylinder {
        <0, 0, -2>, <0, 0, 2>, V_Arrondi_Carte
    }
    cylinder {
        <1, 0, -2>, <1, 0, 2>, V_Arrondi_Carte
    }
    cylinder {
        <0, 1, -2>, <0, 1, 2>, V_Arrondi_Carte
    }
    cylinder {
        <1, 1, -2>, <1, 1, 2>, V_Arrondi_Carte
    }
}

#declare G_Bas_Socle1 = box {
    <0, 0, 0>, <10, 1.2, 6>
}

#declare G_Socle_Clipper = difference {
    box {
        <0, -1, 0>, <3, 2, 3>
    }
    cylinder {
        <0, -2, 0>, <0, 3, 0>, V_Arrondi_Socle
    }
    cylinder {
        <3, -2, 0>, <3, 3, 0>, V_Arrondi_Socle
    }
    cylinder {
        <0, -2, 3>, <0, 3, 3>, V_Arrondi_Socle
    }
    cylinder {
        <3, -2, 3>, <3, 3, 3>, V_Arrondi_Socle
    }
}

#declare G_Paroi_Socle = box {
        <0, 0, 0>, <9.4, 10, 1> 
}

#declare G_Decoupe_Socle = union {
        object {
            G_Socle_Clipper
            translate < -2, 0, -2>
        }
        object {
            G_Socle_Clipper
            translate <10 - 1, 0, -2>
        }
        object {
            G_Socle_Clipper
            translate < -2, 0, 6 - 1>
        }
        object {
            G_Socle_Clipper
            translate <10 - 1, 0, 6 - 1>
        }
}

#declare G_Bas_Socle = difference {
    object {
        G_Bas_Socle1
    }
    object {
        G_Decoupe_Socle
    }
}

#declare G_Socle = union {
    object {
        G_Bas_Socle
    }
    object {
        G_Bas_Socle
        translate <0, 10.8, 0>
    }
    object {
        G_Paroi_Socle
        translate < .3, .8, 2.5>
    }
}

#declare G_Corne1 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, 1
    < -14, 0, 0>, 1
    <0, 20, 0>, 4
    <0, 60, 0>, 4
}

#declare G_Corne2 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .9
    < -14, 0, 0>, .9
    <0, 20, 0>, 3.9
    <0, 60, 0>, 3.9
}

#declare G_Corne = difference {
    object {
        G_Corne1
    }
    object {
        G_Corne2
    }
    box {
        < -5, 20, -5>, <5, 25, 5>
    }
}


// 2 - Matériaux

#declare M_Carte_Dos = texture {
    pigment {
        image_map {
            png "images/carte_dos.png"
            map_type 0
        }
    }
        finish {
        ambient .1
        diffuse .5
        specular .5
    }
}

#declare M_Carte_As_Pique = texture {
    pigment {
        image_map {
            png "images/carte_as_pique.png"
            map_type 0
        }
    }
    finish {
        ambient .1
        diffuse .5
        specular .5
    }
}

#declare M_Carte_Reine_Coeur = texture {
    pigment {
        image_map {
            png "images/carte_reine_coeur.png"
            map_type 0
        }
    }
    finish {
        ambient .1
        diffuse .5
        specular .5
    }
}

#declare M_Socle = texture {
    T_Wood7
}

#declare M_Verre = texture {
    pigment {
        rgbf <.95, .95, .95, .9>
    }
    finish {
        ambient .1
        diffuse .5
        specular .9
        reflection {
            0.1, 1
        }
        ior 1.2
    }
}

// 3 - Habillage

#declare H_Carte_Dos = object {
    G_Carte
    texture { M_Carte_Dos }
    scale <6.4, 8.9, .01>
}

#declare H_Devant_As_Pique = object {
    G_Carte
    texture { M_Carte_As_Pique }
    scale <6.4, 8.9, .01>
}

#declare H_Devant_Reine_Coeur = object {
    G_Carte
    texture { M_Carte_Reine_Coeur }
    scale <6.4, 8.9, .01>
}

#declare H_Socle = object {
    G_Socle
    texture { M_Socle }
}

#declare H_Corne = object {
    G_Corne
    texture { M_Verre }
}

// 4 - Assemblage

#declare Decoupe_Carte = union {
    object {
        G_Carte_Clipper
        translate <-1 + V_Arrondi_Carte, 8.9 - V_Arrondi_Carte, 0>
    }
    object {
        G_Carte_Clipper
        translate <-1 + V_Arrondi_Carte, -1 + V_Arrondi_Carte, 0>
    }
    object {
        G_Carte_Clipper
        translate <6.4 - V_Arrondi_Carte, 8.9 - V_Arrondi_Carte, 0>
    }
    object {
        G_Carte_Clipper
        translate <6.4 - V_Arrondi_Carte, -1 + V_Arrondi_Carte, 0>
    }
}

#declare As_Pique = difference {
    merge {
        object {
            H_Carte_Dos
            translate <0, 0, .01>
        }
        object {
            H_Devant_As_Pique
        }
    }
    object {
        Decoupe_Carte
    }
}

#declare Reine_Coeur = difference {
    merge {
        object {
            H_Carte_Dos
            translate <0, 0, .01>
        }
        object {
            H_Devant_Reine_Coeur
        }
    }
    object {
        Decoupe_Carte
    }
}

