def add_book():
    books = []

    # Add three books to shelf
    for i in range(3):
        print(f"Book [{i + 1}]")

        book = dict()
        book["title"] = input("Book title: ")
        book["author"] = input("Book author: ")
        book["year"] = input("Book year: ")

        books.append(book)
        print()


    # Print list of books
    print(books)

if __name__ == "__main__":
    print(__name__)
    add_book()
