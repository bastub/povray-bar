#version 3.7

#include "colors.inc"
#include "woods.inc"

// 1 unitée = 1cm
global_settings
{
    assumed_gamma 1.8
    max_trace_level 5
}

// Variables
#declare h = 114;

// 1 - Modélisation Géométrique
#declare G_Sol = plane {y, 0 }
#declare G_Mur = difference {
    box {<0, 0, 0>, <600, 300, 600>}
    box{<0.1,0,0.1>, <590,299,590>}}
#declare G_Compt_D = box{<0,0,0>,<200,h,75>}
#declare G_Compt_C = box{<140,0,75>,<200,h,400>}
#declare G_Bord = box{<130,h+1,-10>,<210,h+6,485>}
#declare G_Flechette = cylinder {<0, 0, 0>, <3, 0, 0>, 25} 


// 2 - Matériaux
#declare Bois = material{texture{pigment{image_map{png "./material/parquet.png"}} rotate<90,0,0> scale 120}}
#declare T_Flechette = material{texture{pigment{image_map{png "./material/dartboard.png"}} rotate<180,90,0> scale 62 translate<0,-37,28.5>}}
#declare Marble = material{texture{pigment{image_map{png "./material/marble.png"}}rotate<90,0,0> scale 80}}
#declare Bois_Fonce = material{texture{pigment{image_map{png "./material/darkwood.png"}} rotate<0,90,0> scale 100}}

// 3 - Habillage
#declare Sol = object{G_Sol material{Bois}}
#declare Mur = object{G_Mur pigment{Gray45}}
#declare Compt_D = object{G_Compt_D material{Bois_Fonce}}
#declare Compt_C = object{G_Compt_C material{Bois_Fonce}}
#declare Bord = object{G_Bord material{Marble}}
#declare Flechette = object{G_Flechette material{T_Flechette}}

// 4 - Assemblage
#declare Comptoir = union{
    object{Compt_C}
    object{Compt_D}
    object{Bord translate<0,0,0>}
    object{Bord translate <-210, 0, -280> rotate<0,90,0>}
}

// 5 - Mise en scène
object{Sol}
object{Mur}
object{Comptoir translate <0,0,110>}
object{Flechette rotate<5,0,0> translate<0,180,240>}


light_source{<300,260,300> White * 1}

light_source{<60,260,50> White * 1}

camera{
    right x * image_width/image_height
    up y
    location <260, 170,250>
    look_at <5,70,70>
    //Champ de vision horizontal
    angle 90
}