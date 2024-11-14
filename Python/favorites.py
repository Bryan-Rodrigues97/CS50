import csv

fav_lang = {}
fav_problem = {}

def import_file():
    with open("favorites.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:

            # Insert or Updates the fav_lang dict
            if row["language"] not in fav_lang:
                fav_lang[row["language"]] = 1
            else:
                fav_lang[row["language"]] += 1

            # Insert or Updates the fav_problem dict
            if row["problem"] not in fav_problem:
                fav_problem[row["problem"]] = 1
            else:
                fav_problem[row["problem"]] += 1

if __name__ == "__main__":
    import_file()

    print("Languages:")
    # the "key=fav_lang.get" in "sorted" function indicates that the for loop will use the value of the key for sorting. The default it is use the key name
    # the function dict.get returns the value for the key
    for l in sorted(fav_lang, key=fav_lang.get, reverse=True):
        print(f"\t{l}: {fav_lang[l]}")

    print()
    print("Problems:")
    for p in sorted(fav_problem, key=fav_problem.get, reverse=True):
        print(f"\t{p}: {fav_problem[p]}")
