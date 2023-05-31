#include "colors.inc"
#include "textures.inc"
#include "woods.inc"
#include "shapes.inc"


// 0 - Variables

#declare V_Arrondi_Carte = .4;
#declare V_Arrondi_Socle = 1;
#declare RandomSeed = seed(1);

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
    <0, 0, 0>, <14, 1.2, 8>
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
        <0, 0, 0>, <13, 12, 1.4> 
}

#declare G_Decoupe_Socle = union {
        object {
            G_Socle_Clipper
            translate < -2, 0, -2>
        }
        object {
            G_Socle_Clipper
            translate <14 - 1, 0, -2>
        }
        object {
            G_Socle_Clipper
            translate < -2, 0, 8 - 1>
        }
        object {
            G_Socle_Clipper
            translate <14 - 1, 0, 8 - 1>
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

#declare G_Socle1 = union {
    object {
        G_Bas_Socle
    }
    object {
        G_Bas_Socle
        translate <0, 12.8, 0>
    }
    object {
        G_Paroi_Socle
        translate < .3, .8, 3.3>
    }
}

#declare G_Corne1 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .8
    < -14, 0, 0>, .8
    <0, 23, 0>, 3
    <0, 60, 0>, 3
}

#declare G_Corne2 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .7
    < -14, 0, 0>, .7
    <0, 23, 0>, 2.9
    <0, 60, 0>, 2.9
}

#declare G_Corne3 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .9
    < -14, 0, 0>, .9
    <0, 23, 0>, 3.1
    <0, 60, 0>, 3.1
}

#declare G_Corne4 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .69
    < -14, 0, 0>, .69
    <0, 23, 0>, 2.89
    <0, 60, 0>, 2.89
}

#declare G_Corne = difference {
    object {
        G_Corne1
    }
    object {
        G_Corne2
    }
    box {
        < -5, 23, -5>, <5, 30, 5>
    }
}

#declare G_Socle = difference {
    object {
        G_Socle1
    }
    object {
        G_Corne3
        translate < 10, 2, 4>
    }
    box {
        < -1, 6.5, 3>, <4, 12.8, 6>
    }
    box {
        < -1, 6, 3>, <3, 7, 6>
    }
}

#declare Sangle = difference {
    cylinder {
        <0, 0, 0>, <0, 1, 0>, 2
    }
    cylinder {
        <0, -.1, 0>, <0, 1.1, 0>, 1.8
    }
}

#declare G_Biere1 = difference {
    object {
        G_Corne4
    }
    box {
        < -5, 20, -5>, <5, 30, 5>
    }
}

#declare G_Biere2 = difference {
    object {
        G_Corne4
    }
    box {
        < -5, 16, -5>, <5, 30, 5>
    }
}

#declare G_Planchette = Round_Box(< 0, 0, 0 >, < 2.5, 1.5, 7.5 >, 0.2, true)

#declare G_Etage1 = union {
    object {
        G_Planchette
    }
    object {
        G_Planchette
        translate <2.51, 0, .2>
    }
    object {
        G_Planchette
        translate <5.3, 0, -.1>
    }
}

#declare G_Etage2 = union {
    object {
        G_Planchette
        translate <0, 0, .1>
    }
    object {
        G_Planchette
        translate <2.51, 0, .2>
    }
}

#declare G_Jenga = union {
    #for (i, 0, 10)
        #for (j, 0, 2)
            #if ((i = 1 & j = 1) | (i = 3 & j = 0) | (i = 4 & j != 1) | (i = 7 & j != 1))
            #else
                object {
                    G_Planchette
                    translate <j * 2.51, i * 3, rand(RandomSeed)/5>
                }
            #end
        #end
    #end

    #for (i, 0, 10)
        #for (j, 0, 2)
            #if ((i = 2 & j = 0) | (i = 3 & j != 1) | (i = 4 & j = 2) | (i = 6 & j = 2) | (i = 10 & j != 0))
            #else
                object {
                    G_Planchette
                    rotate <0, 90, 0>
                    translate <rand(RandomSeed)/5, 1.5+ i * 3, 2.5 + j * 2.51>
                }
            #end
        #end
    #end
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
    T_Wood8
}

#declare M_Verre = material {
    texture {
        pigment { color rgbf <1, 1, 1, .9> }
        finish { 
            ambient 0
            diffuse 0
            specular 0.2
            roughness 1e-3
            reflection {
                4e-2,
                .95
                fresnel on
            }
            conserve_energy
        }
    }
    interior {
        fade_color <1, 1, 1>
        fade_distance 4
        fade_power 1e3
        ior 1.2
    }
}

#declare M_Cuir = texture {
    pigment { rgb <.3, .2, .1> }
    finish {
        ambient .1
        diffuse .5
        specular .5
    }
}

#declare M_Biere = texture {
    pigment { rgbf <.8, .8, 0, .8> }
}

#declare M_Bois = texture {
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
    G_Socle
    texture { M_Socle }
}

#declare H_Corne = object {
    G_Corne
    material { M_Verre }
}

#declare H_Sangle = object {
    Sangle
    texture { M_Cuir }
}

#declare H_Biere1 = object {
    G_Biere1
    texture { M_Biere }
}

#declare H_Biere2 = object {
    G_Biere2
    texture { M_Biere }
}

#declare H_Jenga = object {
    G_Jenga
    texture { M_Bois }
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

#declare Corne1 = union {
    object {
        H_Socle
    }

    object {
        H_Corne 
        translate <10.1, 2, 4>
    }

    object {
        H_Biere1
        translate <10.1, 2, 4>
    }

    object {
        H_Sangle
        rotate < 0, 0, -30>
        translate <2.3, 6, 4>
    }
}

#declare Corne2 = union {
    object {
        H_Socle
    }

    object {
        H_Corne 
        translate <10.1, 2, 4>
    }

    object {
        H_Biere2
        translate <10.1, 2, 4>
    }

    object {
        H_Sangle
        rotate < 0, 0, -30>
        translate <2.3, 6, 4>
    }
}