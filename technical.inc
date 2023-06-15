#include "rad_def.inc"

light_source{
    <300,260,300> White * .2
    area_light <0, 0, 0>, <500, 0, 500>, 5, 5 

}

light_source{
    <50,260,590> rgb <1, 1, .9> * 0.9
    spotlight
    point_at <60,0,50>
    fade_power 1.2
    fade_distance 250
    radius 20
}

camera{
    right x * image_width/image_height
    up y
    location <260, 170,250> look_at <5,70,70> //Plan de base
    //location <60,170,160> look_at <5,170,170>   //Plan plus rapproché
    //Champ de vision horizontal
    angle 90
}

global_settings {
    assumed_gamma 1.8
    max_trace_level 5
    radiosity { Rad_Settings(Radiosity_IndoorHQ, no, no) }
}
