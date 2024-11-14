import csv
from collections import Counter

def import_file():
    with open("favorites.csv") as file:
        reader = csv.DictReader(file)
        counts = Counter()
        for row in reader:
            counts[str.lower(row["problem"])] += 1

        fav = input("Favorite: ").lower()

        if fav in counts:
            print(f"The problem '{fav.capitalize()}' is favorite by {counts[fav]} persons")
        else:
            print(f"Cannot find {fav.capitalize()}")

if __name__ == "__main__":
    import_file()
