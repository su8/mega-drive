pdf2img
=======
<img src="/img/pdf2img.png" alt="" /><img src="/img/pdf2img-two.png" alt="" /><img src="/img/tray.png" alt="" />

pdf2img is a small and open source graphical application written in Python and designed to act as a quick solution for converting PDF files to image files.

pdf2img features support for four different image formats, including PNG, JPG, BMP, and TIFF, as well as support for ten Ghostscript devices, including png16m, pngalpha, pnggray, jpeg, jpegcmyk, jpeggray, bmp16m, bmpgray, tiff24nc, and tiffgray.

Before the actual conversion, users will be able to set the resolution of the output image, as well as to specify the pages they want to convert. The software can convert multiple PDF pages at once, into multiple images, with a single mouse click.
## Archlinux support
Archlinux users can install the program directly from AUR, without the need to download it from here.

    yaourt -S pdf2img

## Downloaded from here
Once you download the program, before starting it copy img/pdf2img_icon.png to /usr/share/pixmaps

    sudo cp img/pdf2img_icon.png /usr/share/pixmaps

11/11/13 name changed, from pdf2png to pdf2img and I'm saying huge THANK YOU to Aaditya Bagga.
## Requirements

* python 
* ghostscript
* python-gobject (for debian is python-gi)
* webkitgtk, pywebkitgtk