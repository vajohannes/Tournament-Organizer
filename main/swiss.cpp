#include "swiss.h"
#include "match.h"

Swiss::Swiss(int numRounds, const PlayerList &list) : curRound(0), numRounds(numRounds), list(list)
{
    this->list.sort();
}

Swiss::~Swiss()
{
    // Swiss constructor is PBR, no memory allocation and thus no memory deallocation is needed.
}

void Swiss::play()
{
    while (curRound < numRounds)
    {
        curRound += 1;
        int numScores = curRound * 2 - 1;
        PlayerList **lists = new PlayerList *[numScores];

        int startIndex = 0;
        for (int i = numScores - 1; i >= 0; --i)
        {
            int endIndex = startIndex;
            while (endIndex < list.getNumPlayers() && list.getPlayer(endIndex)->getScore() == i)
            {
                ++endIndex;
            }
            lists[i] = list.splice(startIndex, endIndex);
            startIndex = endIndex;
        }

        for (int i = numScores - 1; i >= 0; --i)
        {
            if (lists[i]->getNumPlayers() == 0)
            {
                continue;
            }
            lists[i]->sort();

            int midIndex = lists[i]->getNumPlayers() / 2;

            for (int j = 0; j < midIndex; ++j)
            {
                Match m{lists[i]->getPlayer(j), lists[i]->getPlayer(j + midIndex)};
                m.play();
            }

            if (lists[i]->getNumPlayers() % 2 == 1)
            {
                Player *lastPlayer = lists[i]->getPlayer(lists[i]->getNumPlayers() - 1);
                if (i == 0)
                {
                    lastPlayer->addScore(2);
                }
                else
                {
                    lists[i - 1]->addPlayer(lastPlayer);
                }
            }
        }

        list.sort();
        printLeaderboard();

        for (int i = 0; i < numScores; ++i)
        {
            delete lists[i];
        }
        delete[] lists;
    }

    /* for (curRound = 1; curRound <= numRounds; curRound++)
    {
        // Create an array of PlayerList for each possible score
        PlayerList scoreLists[2 * curRound - 1];
        for (int i = 0; i < list.getNumPlayers(); i++)
        {
            int score = list.getPlayer(i)->getScore();
            scoreLists[2 * curRound - 2 - score].addPlayer(list.getPlayer(i));
        }

        // Play matches for each non-empty PlayerList
        for (int i = 2 * curRound - 2; i >= 1; i--)
        {
            if (scoreLists[i].getNumPlayers() > 0)
            {
                // Sort the list by score and ELO
                scoreLists[i].sort();

                // Play matches for each pair of players around the midpoint
                int midpoint = scoreLists[i].getNumPlayers() / 2;
                for (int j = 0; j < midpoint; j++)
                {
                    Match match(scoreLists[i].getPlayer(j), scoreLists[i].getPlayer(midpoint + j));
                    match.play();
                }

                // Handle odd number of players
                if (scoreLists[i].getNumPlayers() % 2 != 0)
                {
                    Player *byePlayer = scoreLists[i].getPlayer(scoreLists[i].getNumPlayers() - 1);
                    int byeScore = i - 1;
                    if (byeScore == 0)
                    {
                        byePlayer->addScore(2);
                    }
                    else
                    {
                        scoreLists[i - 2].addPlayer(byePlayer);
                    }
                }
            }
        }

        // Sort the final list and print the leaderboard
        list.sort();
        printLeaderboard();

        // Delete dynamically allocated memory
        for (int i = 0; i < 2 * curRound - 1; i++)
        {
            for (int j = 0; j < scoreLists[i].getNumPlayers(); j++)
            {
                delete scoreLists[i].getPlayer(j);
            }
        }
    } */
}