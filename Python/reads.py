import csv

def read_csv():
    books = []

    # Add books to shelf by reading from books.csv
    # Using the "with" synthax the file will be automatically closed. Otherwhise "file = open(filenalle); file.close(co)"
    with open("books.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:
            books.append(row)

    # Print books
    for book in books:
        print(f"{book["author"]} wrote {book["title"]}")

# Entry point
if __name__ == "__main__":
    read_csv()
