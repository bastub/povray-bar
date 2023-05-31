light_source {
    <-150, 500, 80>
    color rgb <1, 1, 1>
}

camera {
    right x * image_width / image_height
    up y
    location <4, 40, 40>
    look_at <10, 5, 0>
}