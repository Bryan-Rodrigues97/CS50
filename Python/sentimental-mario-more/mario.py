from cs50 import get_int

def print_row(hashes, spaces, direction):
    if direction == 'l':
        for hashe in range(hashes):
            if hashe < spaces:
                print(" ", end="")
            else:
                print("#", end="")

    elif direction == 'r':
        for hashe in range(0, hashes-spaces, 1):
            print("#", end="")

while True:
    height = get_int("Height: ")

    if height > 0 and height < 9:
        break

for i in range(height):
    spaces = height-i-1
    print_row(height, height-i-1, "l")
    print("  ", end="")
    print_row(height, height-i-1, "r")
    print()
