#include "colors.inc"
#include "textures.inc"
#include "woods.inc"
#include "shapes.inc"

// |----------------------------------------------------------------------|
// |-------------------------- 0 - Variables -----------------------------|
// |----------------------------------------------------------------------|

#declare V_Arrondi_Carte = .4;
#declare V_Arrondi_Socle = 1;
#declare RandomSeed = seed(1);





// |----------------------------------------------------------------------|
// |-------------------- I - Modélisation géométrique --------------------|
// |----------------------------------------------------------------------|

// I.1 - Modèles des cartes

// Boite de la carte
#declare G_Carte = box {
    <0, 0, 0>, <6.4, 8.9, .01>
}

// Objet qui permettra de découper la carte pour lui donner une forme arrondie
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

// Union de 4 clippers pour découper la carte
#declare G_Decoupe_Carte = union {
    object {
        G_Carte_Clipper
        translate < -1 + V_Arrondi_Carte, 8.9 - V_Arrondi_Carte, 0>
    }
    object {
        G_Carte_Clipper
        translate < -1 + V_Arrondi_Carte, -1 + V_Arrondi_Carte, 0>
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

// ------
// I.2. - Modélisation des boissons

// I.2.1. - Modèles des cornes en verre

// Paroi extérieur d'une corne
#declare G_Corne1 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .8
    < -14, 0, 0>, .8
    <0, 23, 0>, 3
    <0, 60, 0>, 3
}

// Paroi intérieur d'une corne
#declare G_Corne2 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .7
    < -14, 0, 0>, .7
    <0, 23, 0>, 2.9
    <0, 60, 0>, 2.9
}

// Création d'une corne creuse
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

// Objet de la forme d'une corne permettant de creuser le socle de la corne
#declare G_Corne3 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .9
    < -14, 0, 0>, .9
    <0, 23, 0>, 3.1
    <0, 60, 0>, 3.1
}

// Objet de la forme d'une corne permettant de créer la bière 
#declare G_Corne4 = sphere_sweep {
    cubic_spline 
    4,
    < -50, 4, 0>, .69
    < -14, 0, 0>, .69
    <0, 23, 0>, 2.89
    <0, 60, 0>, 2.89
}


// ---
// I.2.2. - Modèle du socle

// Base du socle des cornes (Partie haute et partie basse) sans bords arrondis
#declare G_Base_Socle1 = box {
    <0, 0, 0>, <14, 1.2, 8>
}

// Objet qui permettra de découper le socle pour lui donner une forme arrondie
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

// Union de 4 clippers pour découper la base du socle
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

// Paroi du socle
#declare G_Paroi_Socle = box {
        <0, 0, 0>, <13, 12, 1.4> 
}

// Base du socle avec bords arrondis
#declare G_Base_Socle = difference {
    object {
        G_Base_Socle1
    }
    object {
        G_Decoupe_Socle
    }
}

// Socle des cornes pas encore creusé
#declare G_Socle1 = union {
    object {
        G_Base_Socle
    }
    object {
        G_Base_Socle
        translate <0, 12.8, 0>
    }
    object {
        G_Paroi_Socle
        translate < .3, .8, 3.3>
    }
}

// Socle des cornes creusé
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


// ---
// I.2.3. - Modèle de la sangle

// Sangle de la corne
#declare G_Sangle = difference {
    cylinder {
        <0, 0, 0>, <0, 1, 0>, 2
    }
    cylinder {
        <0, -.1, 0>, <0, 1.1, 0>, 1.8
    }
}


// ---
// II.2.4. - Modèles de la bière

// Première bière, pas trop entamée
#declare G_Biere1 = difference {
    object {
        G_Corne4
    }
    box {
        < -5, 20, -5>, <5, 30, 5>
    }
}

// Deuxième bière, un peu plus entamée
#declare G_BiereBis = difference {
    object {
        G_Corne4
    }
    box {
        < -5, 16, -5>, <5, 30, 5>
    }
}


// ---
// I.2.5. - Modèles de la mousse

// Création d'un blob contenant 50 x 50 sphères avec une hauteur aléatoire
#declare G_Mousse1 = blob {
    threshold .65
    #for (i, 0, 50)
        #for (j, 0, 50)
            sphere {
            < i/5, rand(RandomSeed)/3, j/5 >, 1, 1
            }
        #end
    #end
}

// Mousse de la première bière
#declare G_Mousse = intersection {
    object {
        G_Mousse1 
        translate <4.9, 23, -1>
    }

    object {
        G_Corne4
        translate <10.1, 2, 4>
    }
}

// Mousse de la deuxième bière
#declare G_MousseBis = intersection {
    object {
        G_Mousse1 
        translate <4.9, 19, -1>
    }

    object {
        G_Corne4
        translate <10.1, 2, 4>
    }
}

// I.2.6 - Modèle de la bouteille

#declare G_Bouteille = lathe {
    bezier_spline
    40,
    <0, 0>, <3, 0>, <3, 0>, <3, 2> 
    <3, 2>, <3, 5>, <3, 5>, <3, 10> 
    <3, 10>, <3, 16>, <1.7, 16>, <1.2, 20.8> 
    <1.2, 20.8>, <1.5, 21.6>, <1.2, 21.6>, <1.2, 22.1>
    <1.2, 22.1>, <1.4, 22.6>, <1.1, 22.6>, <1.1, 22.6>
    <1.1, 22.6>, <1, 22.6>, <.8, 22.6>, <.9, 22>
    <.9, 22>, <.9, 21.5>, <1.2, 21.5>, <.9, 20.7>
    <.9, 20.7>, <1.4, 15.9>, <2.7, 15.9>, <2.7, 9.9>
    <2.7, 9.9>, <2.7, 4.9>, <2.7, 4.9>, <2.7, 1.9> 
    <2.7, 1.9>, <2.7, .3>, <2.7, .3>, <0, .3>
}

#declare G_Etiquette = difference {
    cylinder {
        <0, 0, 0>, <0, 8, 0>, 3.1
    }
    cylinder {
        <0, -1, 0>, <0, 9, 0>, 3
    }
}


// ------
// I.3. - Modèles du Jenga

// Planchettes du Jenga, boîte avec arrêtes et coins arrondis
#declare G_Planchette = Round_Box(< 0, 0, 0 >, < 2.5, 1.5, 7.5 >, 0.2, true)



// ------
// I.4. - Modèles du téléphone

// I.4.1. - Modèle de la coque

// Coque du téléphone, boîte avec arrêtes et coins arrondis, creusée et tronquée
#declare G_Coque = difference {
    Round_Box(< 0, 0, 0 >, < 16.2, 7.4, 1 >, 0.5, true)

    Round_Box(< .1, .1, .1 >, < 16.1, 7.3, .9 >, 0.4, true)

    box {
        < -1, -1, -1>, <20, 8, .2>
    }
}


// ---
// I.4.2. - Modèle de l'écran

// Ecran du téléphone, boîte avec arrêtes et coins arrondis
#declare G_Ecran = Round_Box(< 0, 0, 0 >, < 16, 7.2, .8 >, 0.4, true)



// |----------------------------------------------------------------------|
// |--------------------------- II - Matériaux ---------------------------|
// |----------------------------------------------------------------------|

// II.1. - Matériaux des cartes

// Dos d'une carte (image)
#declare M_Carte_Dos = texture {
    pigment {
        image_map {
            png "images/carte_dos.png"
            map_type 0
        }
        scale <6.4, 8.9, .01>
    }
        finish {
        ambient .1
        diffuse .5
        specular .5
    }
}

// As de pique (image)
#declare M_Carte_As_Pique = texture {
    pigment {
        image_map {
            png "images/carte_as_pique.png"
            map_type 0
        }
        scale <6.4, 8.9, .01>
    }
    finish {
        ambient .1
        diffuse .5
        specular .5
    }
}

// Reine de coeur (image)
#declare M_Carte_Reine_Coeur = texture {
    pigment {
        image_map {
            png "images/carte_reine_coeur.png"
            map_type 0
        }
        scale <6.4, 8.9, .01>
    }
    finish {
        ambient .1
        diffuse .5
        specular .5
    }
}


// ------
// II.2. - Matériaux des boissons 

// Socle (bois)
#declare M_Socle = texture {
    T_Wood8
}

// Corne (verre)
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

// Sangle (cuir)
#declare M_Cuir = texture {
    pigment { rgb <.3, .2, .1> }
    finish {
        ambient .1
        diffuse .5
        specular .5
    }
}

// Bière (bière)
#declare M_Biere = material {
    texture {
        pigment { rgbf <.8, .8, 0, .8> }
        finish {
            ambient .5
            diffuse .5
            specular .05
            roughness 1e-3
        }
    }
    interior {
        ior 1.2
        fade_color <.6, .6, 0>
        fade_distance 10
        fade_power 10
    }
}

// Mousse (mousse)
#declare M_Mousse = texture {
    pigment { rgbf <1, 1, 1, .1> }
    finish {
        ambient .1
        diffuse .5
        specular .5
    }
}

// Bouteille de bière (verre)
#declare M_Bouteille = material {
    texture {
        pigment { color rgbf <200/255, 165/255, 0, .7> }
        finish { 
            ambient 0
            diffuse 0
            specular 0.2
            roughness 1e-3
            reflection {
                4e-3,
                .95
                fresnel on
            }
            conserve_energy
        }
    }
    interior {
        fade_color <.3, .12, 0>
        fade_distance 10
        fade_power 1e3
        ior 1.2
    }
}

#declare M_Etiquette = texture {
    pigment {
        image_map {
            png "images/etiquette.png"
            map_type 2
            once
        }
        scale <18.85, 8, 18.85>
    }
    finish {
        ambient .1
        diffuse .5
        specular .5
    }
}


// ------
// II.3. - Matériaux du Jenga

// Planchette (bois)
#declare M_Planchette = texture {
    T_Wood7
}


// ------
// II.4. - Matériaux du téléphone

// Coque (silicone noir)
#declare M_Coque = texture {
    pigment { rgb <0, 0, 0> }
}

// Ecran (image)
#declare M_Ecran = texture {
    pigment {
        image_map {
            jpeg "images/ecran.jpg"
            map_type 0
        }
        scale <16, 7.2, 1>
    }
    finish {
        emission 1
        diffuse .6
    }
}





// |----------------------------------------------------------------------|
// |--------------------------- III - Habillage --------------------------|
// |----------------------------------------------------------------------|

// III.1. - Habillage des cartes

// Dos d'une carte
#declare H_Carte_Dos = object {
    G_Carte
    texture { M_Carte_Dos }
    
}

// As de pique
#declare H_Devant_As_Pique = object {
    G_Carte
    texture { M_Carte_As_Pique }
}

// Reine de coeur
#declare H_Devant_Reine_Coeur = object {
    G_Carte
    texture { M_Carte_Reine_Coeur }
}


// ------
// III.2. - Habillage des boissons

// Socle
#declare H_Socle = object {
    G_Socle
    texture { M_Socle }
}

// Corne
#declare H_Corne = object {
    G_Corne
    material { M_Verre }
}

// Sangle
#declare H_Sangle = object {
    G_Sangle
    texture { M_Cuir }
}

// Première bière
#declare H_Biere1 = object {
    G_Biere1
    material { M_Biere }
}

// Deuxième bière
#declare H_BiereBis = object {
    G_BiereBis
    material { M_Biere }
}

// Première mousse
#declare H_Mousse = object {
    G_Mousse
    texture { M_Mousse }
}

// Deuxième mousse
#declare H_MousseBis = object {
    G_MousseBis
    texture { M_Mousse }
}

// Bouteille de bière
#declare H_Bouteille = object {
    G_Bouteille
    material { M_Bouteille }
    texture { 
        M_Etiquette
        translate <0, 2, 0>
        rotate <0, -14, 0> 
    }
}


// ------
// III.3. - Habillage du Jenga

// Planchette
#declare H_Planchette = object {
    G_Planchette
    texture { M_Planchette }
}


// ------
// III.4. - Habillage du téléphone

// Coque
#declare H_Coque = object {
    G_Coque
    texture { M_Coque }
}

// Ecran
#declare H_Ecran = object {
    G_Ecran
    texture { M_Ecran }
}





// |--------------------------------------------------------------------|
// |--------------------------- IV - Assemblage ------------------------|
// |--------------------------------------------------------------------|

// IV.1. - Assemblage des cartes

// Carte
#declare Decoupe_Carte = union {
    object {
        G_Carte_Clipper
        translate < -1 + V_Arrondi_Carte, 8.9 - V_Arrondi_Carte, 0>
    }
    object {
        G_Carte_Clipper
        translate < -1 + V_Arrondi_Carte, -1 + V_Arrondi_Carte, 0>
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

// As de pique
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

// Reine de coeur
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


// ------
// IV.2. - Assemblage des boissons

// Première corne
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
        H_Mousse
    }

    object {
        H_Sangle
        rotate < 0, 0, -30>
        translate <2.3, 6, 4>
    }
}

// Deuxième corne
#declare Corne2 = union {
    object {
        H_Socle
    }

    object {
        H_Corne 
        translate <10.1, 2, 4>
    }

    object {
        H_BiereBis
        translate <10.1, 2, 4>
    }

    object {
        H_MousseBis
    }

    object {
        H_Sangle
        rotate < 0, 0, -30>
        translate <2.3, 6, 4>
    }
}

#declare Bouteille = object {
    H_Bouteille
}


// ------
// IV.3. - Assemblage du Téléphone

// Téléphone
#declare Telephone = union {
    object {
        H_Coque
    }
    object {
        H_Ecran
        translate <.1, .1, .1>
    }

    rotate <90, 0, 0>
    translate <0, 1, 0>
}


// ------
// IV.4. - Assemblage du Jenga


// Tour de Jenga
#declare Jenga = union {
    #for (i, 0, 10)
        #for (j, 0, 2)
            // Nous voulons que certaines planchettes soient manquantes
            #if ((i = 1 & j = 1) | (i = 3 & j = 0) | (i = 4 & j != 1) | (i = 7 & j != 1))
            #else
                object {
                    H_Planchette
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
                    H_Planchette
                    rotate <0, 90, 0>
                    translate <rand(RandomSeed)/5, 1.5+ i * 3, 2.5 + j * 2.51>
                }
            #end
        #end
    #end
}