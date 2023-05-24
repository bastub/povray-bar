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

#declare G_Bas_Socle = box {
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

#declare G_Paroi_Socle = difference {
    box {
        <0, 0, 0>, <10.2, 10, 1> 
    }
    cylinder {
        <14, 12, -1>, <14, 12, 2>, 10
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
    G_Bas_Socle
    texture { M_Socle }
}

#declare H_Paroi_Socle = object {
    G_Paroi_Socle
    texture { M_Socle }
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

#declare Decoupe_Socle = union {
        object {
            G_Socle_Clipper
            translate <-2, 0, -2>
        }
        object {
            G_Socle_Clipper
            translate <10 - 1, 0, -2>
        }
        object {
            G_Socle_Clipper
            translate <-2, 0, 6 - 1>
        }
        object {
            G_Socle_Clipper
            translate <10 - 1, 0, 6 - 1>
        }

    texture { M_Socle }
}

#declare Bas_Socle = difference {
    object {
        H_Socle
    }
    object {
        Decoupe_Socle
    }
}

#declare Haut_Socle = difference {
    object {
        Bas_Socle
    }
    cylinder {
        <6, -1, 3>, <6, 2, 3>, 2
    }

    texture { M_Socle }
}

#declare Socle = union {
    object {
        Bas_Socle
    }
    object {
        Haut_Socle
        translate <0, 9.6, 0>
    }
    object {
        H_Paroi_Socle
        translate <-.1, .8, 2.5>
    }
}