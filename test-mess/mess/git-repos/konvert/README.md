Konvert
=====
ImageMagick's convert alternative in python.

## Requirements

* python2
* python2-pillow
* ghostscript

## Archlinux support

Archlinux users can install the program directly from AUR, without the need to download it from here.

    yaourt -S konvert-git

## Usage Options:

    input image formats:
        jpg, png, gif, bmp, pcx, ppm, tiff, pdf, tif, im, eps, xwd, pgm, pbm, tga

    output image formats:
        jpg, png, gif, bmp, pcx, ppm, tiff, pdf, tif, im, webp, pgm, pbm, tga

    input image = 1.png , output image = 2.png

    konvert image to image:
        konvert 1.png 1.jpg

    resize image:
        konvert 1.png -resize 600x700 2.png

    rotate image:
        konvert 1.png -rotate 60 2.png

    image information:
        konvert 1.png -info

    crop:
        konvert 1.png -crop 425x250 2.png

    contrast, color, brightness, sharpness: 1 = 100% (the original is 100%), 1.5 = 150%, 2 = 200%, 2.5 = 250%
    input image = 1.png , output image = 2.png

    contrast:
            konvert 1.png -contrast 1 2.png
    color:
            konvert 1.png -color 1 2.png
    sharpness:
            konvert 1.png -sharpness 1 2.png
    brightness:
            konvert 1.png -brightness 1 2.png

## Effects:

    input image = 1.png , output image = 2.png

    blur:
        konvert 1.png -blur 2.png
    contour:
        konvert 1.png -contour 2.png
    detail:
        konvert 1.png -detail 2.png
    edge:
        konvert 1.png -edge 2.png
    edge2:
        konvert 1.png -edge2 2.png
    edge3:
        konvert 1.png -edge3 2.png
    embross:
        konvert 1.png -embross 2.png
    smooth:
        konvert 1.png -smooth 2.png

## PDF konversion options:

    1 program name, 2 file name, 3 resolution, 4 from page, 5 to page, 6 image format, 7 sDevice (type: konvert -help sdevice)
    konvert file.pdf 100 20 30 png png16m

    1 program name, 2 file name, 3 resolution, 4 from page, 5 to page, 6 image format (png, jpg, bmp, tiff)
    konvert file.pdf 100 20 30 png

    1 program name, 2 file name, 3 resolution, 4 from page, 5 to page
    konvert file.pdf 100 20 30

    1 program name, 2 file name, 3 from page, 4 to
    konvert file.pdf 20 30

## Individual options or effects usage:

    konvert -help rotate
    konvert -help crop
    and so on ...