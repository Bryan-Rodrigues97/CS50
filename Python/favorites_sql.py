from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite: ")

rows = db.execute("SELECT COUNT(*) as total FROM favorites WHERE problem = ?", favorite)
#print(rows)
# Access the first index and returns the value of the key total
print(rows[0]["total"])
