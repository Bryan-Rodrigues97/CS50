# list of dictionaries, with multiple key values pairs
people = [
    {"name": "Bryan", "number": "+55 51 99359-2838"},
    {"name": "Amaro", "number": "+55 51 99838-2668"},
]

def main():
    name = input("Name: ")

    for person in people:
        if(person["name"] == name):
            print(f"{person["number"]}")
            break
    else:
        print("Not found")

main()
