import qrcode

img = qrcode.make("bandeira96542020")
img.save("qr.png", "PNG")
