from cs50 import get_int

def main():
    n = get_int("Height: ")
    draw(n)

def draw(n):
    if n <= 0:
        return

    draw(n - 1)
    print("#" * n)  # no need to use loops. The * operator will repeat the string many times


main()
