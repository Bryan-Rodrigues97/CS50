def get_letters_count(text):
    alpha = list(filter(str.isalpha,text))
    return len(alpha)

def get_words_count(text):
    words = text.split()
    return len(words)

def get_sentences_count(text):
    sentences = list(filter(lambda c: c == '.' or c == '?' or c == '!', text))
    return len(sentences)

if __name__ == "__main__":
    text = input("Text: ")

    letters = get_letters_count(text)
    words = get_words_count(text)
    sentences = get_sentences_count(text)

    l = (letters/words) * 100;
    s = (sentences/words) * 100;

    # Coleman-Liau index
    # index = 0.0588 * L - 0.296 * S - 15.8
    # L is the average number of letters per 100 words in the text
    # S is the average number of sentences per 100 words in the text.
    index = int(round(0.0588 * l - 0.296 * s - 15.8))

    # Prints on the Output what is the Grade level based on the Coleman-Liau index
    if index < 1:
        print("Before Grade 1")
    elif (index >= 16):
        print("Grade 16+")
    else:
        print(f"Grade {index}")
