def main():
    a = get_int("A: ")
    b = get_int("B: ")

    # formats the output string with 10 places decimal
    print(f"{divide(a,b):.10f}")

def divide(a, b):
    return a / b


def get_int(prompt):
    while(True):
        try:
            return int(input(prompt))
        except:
            pass    # try again


main()
