light_source {
    <-150, 500, 80>
    color rgb <1, 1, 1>
}

camera {
    right x * image_width / image_height
    up y
    location < 50, 50, 50>
    look_at <25, 30, 35>
}

// cylinder {
//     <0, 0, 0>, <500, 0, 0>, .1
//     pigment { color rgb <1, 0, 0> } 
// }

// cylinder {
//     <0, 0, 0>, <0, 500, 0>, .1
//     pigment { color rgb <0, 1, 0> } 
// }

// cylinder {
//     <0, 0, 0>, <0, 0, 500>, .1
//     pigment { color rgb <0, 0, 1> } 
// }