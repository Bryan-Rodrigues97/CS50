from sys import argv

def main():
    # ternary if
    print(f"hello, {argv[1]}") if len(argv) == 2 else print("hello, world")

main()
