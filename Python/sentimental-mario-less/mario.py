from cs50 import get_int

while True:
    height = get_int("Height: ")

    if height > 0 and height < 9:
        break

for i in range(height):
    spaces = height-i-1
    for j in range(height):
        if j < spaces:
            print(" ", end="")
        else:
            print("#", end="")
    print()
