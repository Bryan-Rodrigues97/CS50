import sys

def main():
    if len(sys.argv) != 2:
        print("Wrong usage of CLI arguments")
        sys.exit(1)

    print(f"hello, {sys.argv[1]}")
    sys.exit(0)


main()
