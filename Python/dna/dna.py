import csv
import sys

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: dna database sequence")
        sys.exit(1)

    # Read database file into a variable
    database = load_file(sys.argv[1], True)

    # Read DNA sequence file into a variable
    sequence = load_file(sys.argv[2], False)

    # Find longest match of each STR in DNA sequence
    # Creates a dict with the nucleotides types. Initialized with 0 count
    nucleotides = {}
    for k in database[0]:
        if k != "name":
            nucleotides[k] = 0

    for nucleotide in nucleotides:
        n = longest_match(sequence, nucleotide)
        nucleotides[nucleotide] = n

    #print(nucleotides)
    #print(database)

    # Check database for matching profiles
    for p in database:
        for n in nucleotides:
            if int(p[n]) != int(nucleotides[n]):
                break
        else:
            print(p["name"])
            return
    else:
        print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run

def load_file(fname, readAsCsv):
    file_list = []

    # Try to open the file
    try:
        file = open(fname)

        # If the file isnt found. Return 1
        if not file:
            print(f"Cannot open file named {fname}")
            sys.exit(1)

        # Apeend the file content into a list and returns
        if readAsCsv:
            reader = csv.DictReader(file)
            for row in reader:
                file_list.append(row)
            file.close()
            return file_list
        else:
            content = file.read()
            file.close()
            return content
    except:
        print(f"Cannot open file named {fname}")
        sys.exit(1)

main()
