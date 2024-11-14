# Dictonary with 1 key pair value
people = {
    "Bryan": "+55 51 99359-2838",
    "Amaro": "+55 51 99838-2668"
}

def main():
    name = input("Name: ")

    # serach for the name in Dictonary
    if name in people:
        print(f"Found {people[name]}")  # if the name is found. The value can be accessed
    else:
        print("Not found")

main()
