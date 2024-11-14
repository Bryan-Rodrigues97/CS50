from cs50 import get_float

while True:
    change = get_float("Change: ")
    if(change > 0):
        break

changeOwned = 0
coins = [0.25, 0.10, 0.05, 0.01]
coin = coins[0]
i = 0

while change>0:
    if coin > change:
        i += 1
        coin = coins[3] if (i > 3) else coins[i]
        continue

    change = round(change - coin, 2)
    changeOwned+=1

print(changeOwned)
