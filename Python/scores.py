from cs50 import get_int

def main():
    scores = []

    for i in range(3):
        scores.append(get_int(f"Score [{i}]: "))

    average = sum(scores) / len(scores)
    print(f"{average:.2f}")

main()
