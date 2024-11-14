while True:
    s = input("Do you agree? ").lower()

    if s in ["y", "yes"]:
        print("\tAgreed")
        break
    elif s in ["n", "no"]:
        print("\tNot Agreed")
        break
    else:
        print("\tInvalid answer\n")
