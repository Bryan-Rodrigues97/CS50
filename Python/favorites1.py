import csv
from collections import Counter

def import_file():
    with open("favorites.csv") as file:
        reader = csv.DictReader(file)
        counts = Counter()
        for row in reader:
            counts[row["problem"]] += 1

        # lists the top 5 five favorite problems
        for fav, count in counts.most_common(5):
            print(f"{fav}: {count}")

if __name__ == "__main__":
    import_file()
