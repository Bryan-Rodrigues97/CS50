book = dict()
book["title"] = "Corduroy"      # title is the key, Corduroy is the value
book["author"] = "Don Freeman"  # author is the key, Don Freeman is the value

print(book)
# {'title': 'Corduroy', 'author': 'Don Freeman'}

# print the dict keys
for k in book:
    print(k)

# converting dict to list
book_keys = book.items()

for k in book_keys:
    print(k[1])
