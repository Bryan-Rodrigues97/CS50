import os
import random
import re
import sys

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """
    total_pages = len(corpus)
    ranks = {p: (1 - damping_factor) / total_pages for p in corpus}
    links = corpus[page]

    if links:
        link_prob = damping_factor / len(links)
        for link in links:
            ranks[link] += link_prob

    return normalize(ranks)


def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling n pages
    according to transition model, starting with a page at random.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    ranks = {page: 0 for page in corpus}
    page = random.choice(list(corpus))

    for _ in range(n):
        tModel = transition_model(corpus, page, damping_factor)
        page = random.choices(list(tModel.keys()), weights=list(tModel.values()))[0]
        ranks[page] += 1

    return normalize(ranks)


def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    ranks = initialize_ranks(corpus)
    old_ranks = {page: 0 for page in ranks}

    while True:
        for page in ranks:
            old_ranks[page] = ranks[page]
            ranks[page] = calculate_page_rank(corpus, ranks, page, damping_factor)

        ranks = normalize(ranks)
        if convergence(ranks, old_ranks):
            break

    return ranks


def calculate_page_rank(corpus, page_ranks, page, d):
    """
    Helper function to calculate the PageRank for a specific page.
    """
    links = find_references(corpus, page) or corpus.keys()
    return (1 - d) / len(corpus) + d * sum(page_ranks[link] / len(corpus[link]) for link in links)


def normalize(ranks):
    """
    Normalize a dictionary of PageRank values so they sum to 1.
    """
    total = sum(ranks.values())
    return {page: rank / total for page, rank in ranks.items()}


def convergence(ranks, old_ranks, tolerance=0.001):
    """
    Check if the PageRank values have converged within a tolerance.
    """
    return all(abs(ranks[page] - old_ranks[page]) < tolerance for page in ranks)


def find_references(corpus, page_referenced):
    """
    Find pages that reference a given page.
    """
    return [page for page in corpus if page_referenced in corpus[page]]


def initialize_ranks(corpus):
    """
    Initialize ranks to an equal probability distribution.
    """
    initial_rank = 1 / len(corpus)
    return {page: initial_rank for page in corpus}


if __name__ == "__main__":
    main()
