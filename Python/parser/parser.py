import nltk
import sys
import re

TERMINALS = """
Adj -> "country" | "dreadful" | "enigmatical" | "little" | "moist" | "red"
Adv -> "down" | "here" | "never"
Conj -> "and" | "until"
Det -> "a" | "an" | "his" | "my" | "the"
N -> "armchair" | "companion" | "day" | "door" | "hand" | "he" | "himself"
N -> "holmes" | "home" | "i" | "mess" | "paint" | "palm" | "pipe" | "she"
N -> "smile" | "thursday" | "walk" | "we" | "word"
P -> "at" | "before" | "in" | "of" | "on" | "to"
V -> "arrived" | "came" | "chuckled" | "had" | "lit" | "said" | "sat"
V -> "smiled" | "tell" | "were"
"""

NONTERMINALS = """
S -> N V
S -> NP VP
S -> NP VP AdvP
AP -> Adj | Adj AP
NP -> N | Det N | Adj N | Det Adj N | N PP
PP -> P NP | P AdjP
VP -> V | V NP | V NP PP | V Adv NP | V PP
CNP -> NP PP | NP NP
"""

grammar = nltk.CFG.fromstring(NONTERMINALS + TERMINALS)
parser = nltk.ChartParser(grammar)
np_list = list()

def main():

    # If filename specified, read sentence from file
    if len(sys.argv) == 2:
        with open(sys.argv[1]) as f:
            s = f.read()

    # Otherwise, get sentence as input
    else:
        s = input("Sentence: ")

    # Convert input into list of words
    s = preprocess(s)

    # Attempt to parse sentence
    try:
        trees = list(parser.parse(s))
    except ValueError as e:
        print(e)
        return
    if not trees:
        print("Could not parse sentence.")
        return

    # Print each tree with noun phrase chunks
    for tree in trees:
        tree.pretty_print()

        print("Noun Phrase Chunks")
        np_list = list()
        for np in np_chunk(tree):
            print(" ".join(np.flatten()))


def preprocess(sentence):
    """
    Convert `sentence` to a list of its words.
    Pre-process sentence by converting all characters to lowercase
    and removing any word that does not contain at least one alphabetic
    character.
    """
    wordListTokenized = list()
    pattern = re.compile(r'[a-z]')

    for word in nltk.word_tokenize(sentence.lower()):
        if pattern.match(word):
            wordListTokenized.append(word)

    return wordListTokenized


def np_chunk(tree):
    """
    Return a list of all noun phrase chunks in the sentence tree.
    A noun phrase chunk is defined as any subtree of the sentence
    whose label is "NP" that does not itself contain any other
    noun phrases as subtrees.
    """

    for leaf in tree:
        if len(leaf) == 1:
            if leaf.label() == "NP":
                np_list.append(leaf)
        else:
            if leaf.label() == "NP":
                if not tree_has_np_child(leaf):
                    np_list.append(leaf)
            else:
                np_chunk(leaf)

    return np_list

def tree_has_np_child(tree):
    np_child = False

    for leaf in tree:
        if leaf.label() == "NP":
            return True

        if len(leaf) > 1:
            return tree_has_np_child(leaf)

    return np_child



if __name__ == "__main__":
    main()
