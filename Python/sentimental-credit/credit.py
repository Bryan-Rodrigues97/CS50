import re

MIN_LENGTH = 13
MAX_LENGTH = 16

AMEX_CODES = ["34", "37"]
AMEX_LENGTH = [15]

MASTER_CODES = ["51", "52", "53", "54", "55"]
MASTER_LENGTH = [16]

VISA_CODES = ["40", "41", "42", "43", "44", "45", "46", "47", "48", "49"]
VISA_LENGTH = [13, 16]


# Check if the user input has a valid lenght and only numbers
def valid_length_numbers(creditcard):
    if len(creditcard) < MIN_LENGTH or len(creditcard) > MAX_LENGTH:
        return False

    if not bool(re.match(r"^\d+$", creditcard)):
        return False

    return True

def split_number_sum(num):
    if(num > 9):
        return int(num/10) + int(num%10)
    return num

# Calculates the checksum. Returns True if is valid
def valid_checksum(creditcard):
    sum = False
    productSum = 0
    nonProductSum = 0

    for n in range(len(creditcard)-1, -1, -1):
        rest = int(creditcard[n])

        if sum:
            productSum += split_number_sum(rest * 2)
        else:
            nonProductSum += rest

        sum = not sum

    # TODO
    checkSum = productSum + nonProductSum;

    return (checkSum%10) == 0

if __name__ == "__main__":
    creditcard = input("Number: ")

    if not valid_length_numbers(creditcard) or not valid_checksum(creditcard):
        print("INVALID")
    else:
        code = creditcard[:2]
        cardLen = len(creditcard)

        if code in AMEX_CODES and cardLen in AMEX_LENGTH:
            print("AMEX")
        elif code in MASTER_CODES and cardLen in MASTER_LENGTH:
            print("MASTERCARD")
        elif code in VISA_CODES and cardLen in VISA_LENGTH:
            print("VISA")
        else:
            print("INVALID")
