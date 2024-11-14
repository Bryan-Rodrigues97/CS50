# Blurs an image

from PIL import Image, ImageFilter

# Find edges
before = Image.open("stadium.bmp")
after = before.filter(ImageFilter.FIND_EDGES)
after.save("out.bmp")
