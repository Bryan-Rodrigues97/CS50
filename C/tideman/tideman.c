#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool can_lock_pair(int currentWinner, int currentLoser, int checkWinner);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i],name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate = ranks[i];

        for(int j = i + 1; j < candidate_count; j++)
        {
            int nextCandidate = ranks[j];
            preferences[candidate][nextCandidate] = preferences[candidate][nextCandidate] + 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > 0)
            {
                if(preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;

                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // finds the greather victory each time inside the loop and set into the current [i] index of the pairs array
    for (int i = 0; i < pair_count; i++)
    {
        int victoryStrength = -1;
        int victoryStrengthIdx = 0;

        for (int j = i; j < pair_count; j++)
        {
            pair currentPair = pairs[j];
            int currentStrength = preferences[currentPair.winner][currentPair.loser] - preferences[currentPair.loser][currentPair.winner];

            if (currentStrength > victoryStrength)
            {
                victoryStrength = currentStrength;
                victoryStrengthIdx = j;
            }
        }

        if (i != victoryStrengthIdx)
        {
            int winnerTmp = pairs[i].winner;
            int loserTmp = pairs[i].loser;

            pairs[i].winner = pairs[victoryStrengthIdx].winner;
            pairs[i].loser = pairs[victoryStrengthIdx].loser;

            pairs[victoryStrengthIdx].winner = winnerTmp;
            pairs[victoryStrengthIdx].loser = loserTmp;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if(can_lock_pair(winner, loser, winner))
        {
            locked[winner][loser] = true;
        }
    }

    return;
}

// Recursive function to determine if a pair can be locked
bool can_lock_pair(int currentWinner, int currentLoser, int checkWinner)
{
    if (currentLoser == checkWinner)
    {
        return false;
    }


    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[currentLoser][i])
        {
            if (!can_lock_pair(currentWinner, i, checkWinner))
            {
                return false;
            }
        }
    }
    return true;
}


// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                winner = false;
                break;
            }
        }

        if (winner)
        {
            printf("%s\n",candidates[i]);
            return;
        }
    }
    return;
}
