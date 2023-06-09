#version 3.7

#include "colors.inc"
#include "woods.inc"

// 1 unitée = 1 cm

// |----------------------------------------------------------------------|
// |-------------------- I - Modélisation géométrique --------------------|
// |----------------------------------------------------------------------|

#declare G_Sol = plane {y, 0 }
#declare G_Mur = difference {
    box {<0, 0, 0>, <600, 300, 600>}
    box{<0.1,0,0.1>, <590,299,590>}}
#declare G_Compt_D = box{<0,0,0>,<200,115,75>}
#declare G_Compt_C = box{<0,0,0>,<60,115,325>}
#declare G_Bord = box{<0,0,0>,<90,5,495>}
#declare G_Flechette = cylinder {<0, 0, 0>, <3, 0, 0>, 25}
#declare G_Contour_cible = box{<0,0,0>, <1,80,80>}
#declare G_Banniere = box{<0,0,0>, <240,110,1>}
#declare G_Affiche = box{<0,0,0>, <0.4,30,26>}

// |----------------------------------------------------------------------|
// |--------------------------- II - Matériaux ---------------------------|
// |----------------------------------------------------------------------|

// 2 - Matériaux
#declare Bois = material{texture{pigment{image_map{png "./material/parquet.png"}} rotate<90,0,0> scale 120}}
#declare T_Flechette = material{texture{pigment{image_map{png "./material/dartboard.png"}} rotate<180,90,0> scale 62 translate<0,-37,28.5>}}
#declare Marble = material{texture{pigment{image_map{png "./material/marble.png"}}rotate<90,0,0> scale 80}}
#declare Bois_Fonce = material{texture{pigment{image_map{png "./material/darkwood.png"}} rotate<0,90,0> scale 100}}
#declare Liege = material{texture{pigment{image_map{png "./material/liege.png"}} rotate<0,90,0> scale 90}}
#declare T_Banniere = material{texture{pigment{image_map{"./material/Banniere.png"}} rotate<0,180,0> scale <240,110,90>}}
#declare T_Wanted1 = material{texture{pigment{image_map{png "./material/WantedSylvain.png"}} rotate<0,270,0> scale 30} translate<0,0,-1>}
#declare T_Wanted2 = material{texture{pigment{image_map{png "./material/WantedSylvainDono.png"}} rotate<0,270,0> scale<30,30,25>} translate<0,0,1>}
#declare T_Wanted3 = material{texture{pigment{image_map{png "./material/FurryMaster.png"}} rotate<0,270,0> scale<30,30,25>} translate<0,0,1>}
#declare T_Wanted4 = material{texture{pigment{image_map{png "./material/DarkREM7.png"}} rotate<0,270,0> scale<30,30,25>} translate<0,0,1>}

// |----------------------------------------------------------------------|
// |--------------------------- III - Habillage --------------------------|
// |----------------------------------------------------------------------|


// 3 - Habillage
#declare Sol = object{G_Sol material{Bois}}
#declare Mur = object{G_Mur pigment{Gray45}}
#declare Compt_D = object{G_Compt_D material{Bois_Fonce}}
#declare Compt_C = object{G_Compt_C material{Bois_Fonce}}
#declare Bord = object{G_Bord material{Marble}}
#declare Flechette = object{G_Flechette material{T_Flechette}}
#declare Contour_Cible = object{G_Contour_cible material{Liege}}
#declare Banniere = object{G_Banniere material{T_Banniere}}
#declare Wanted1 = object{G_Affiche material{T_Wanted1}}
#declare Wanted2 = object{G_Affiche material{T_Wanted2}}
#declare Wanted3 = object{G_Affiche material{T_Wanted3}}
#declare Wanted4 = object{G_Affiche material{T_Wanted4}}

// |--------------------------------------------------------------------|
// |--------------------------- IV - Assemblage ------------------------|
// |--------------------------------------------------------------------|

#declare Comptoir = union{
    object{Compt_C translate <140,0,75>}
    object{Compt_D}
    object{Bord translate<120,115,-10>}
    object{Bord translate <-75, 115, -285> rotate<0,90,0>}
}

#declare Cible = union{
    object{Flechette rotate<5,0,0> translate<1,180,70>}
    object{Contour_Cible translate<0,140,30>}
}

#declare Wanted = union{
    object{Wanted1 translate<0,180, 120>}
    object{Wanted2 translate<0,180, 152>}
    object{Wanted3 translate<0,180, 184>}
    object{Wanted4 translate<0,180, 216>}
}