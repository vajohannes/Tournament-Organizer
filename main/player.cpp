#include "player.h"

#include <cstring>

Player::Player(const char *const name, const int elo)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->elo = elo;
    this->score = 0;
}

Player::~Player()
{
    delete[] name;
}

PlayerList::PlayerList()
{
    this->numPlayers = 0;
    this->players = nullptr;
}

PlayerList::PlayerList(const PlayerList &list)
{

    /* this->players = new Player *[list.numPlayers];
    for (int i = 0; i < list.numPlayers; ++i)
    {
        players[i] = list.players[i];
    } */
    this->numPlayers = list.numPlayers;
    this->players = new Player *[this->numPlayers];
    for (int i = 0; i < this->numPlayers; i++)
    {
        this->players[i] = list.players[i];
    }
}

PlayerList::~PlayerList()
{
    delete[] players;
}

void PlayerList::addPlayer(Player *const player)
{
    // Increase size of array
    Player **temp = new Player *[numPlayers + 1];
    for (int i = 0; i < numPlayers; i++)
    {
        temp[i] = players[i];
    }

    temp[numPlayers] = player;

    delete[] players;
    players = temp;
    numPlayers += 1;

    /* // Increase size of array if necessary
    if (numPlayers == 0)
    {
        players = new Player *[1];
    }
    else
    {
        Player **temp = new Player *[numPlayers + 1];
        for (int i = 0; i < numPlayers; i++)
        {
            temp[i] = players[i];
        }
        delete[] players;
        players = temp;
    }

    // Add new player to end of array and update numPlayers
    players[numPlayers] = player;
    numPlayers++; */

    /* if (numPlayers != 0)
    {
        for (int i = 0; i < numPlayers; ++i)
        {
            players[i] = player;
            PlayerList *newList;
            // delete[] player;
            // newList->*players = new Player *[numPlayers + 1];
            // strcpy(players, players);
        }
    }
    else
    {
        ++numPlayers;
        players = new Player *[numPlayers];
        players[0] = player;
    } */

    /* int currCapacity = 1;
    // If the array is full, allocate a new array with double the capacity
    if (numPlayers == currCapacity)
    {
        currCapacity *= 2;
        Player **newPlayers = new Player *[currCapacity];
        for (int i = 0; i < numPlayers; i++)
        {
            newPlayers[i] = players[i];
        }
        delete[] players;
        players = newPlayers;
    }
    // Add the new player to the end of the array
    players[numPlayers] = player;
    numPlayers++; */
}

void PlayerList::sort()
{
    /* bool swapped;
    for (int i = 0; i < numPlayers - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < numPlayers - i - 1; j++)
        {
            if (players[j]->getScore() < players[j + 1]->getScore() ||
                (players[j]->getScore() == players[j + 1]->getScore() &&
                 players[j]->getELO() < players[j + 1]->getELO()))
            {
                Player *temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    } */

    for (int i = numPlayers - 1; i >= 0; --i)
    {
        for (int j = 0; j < 1; ++j)
        {
            if (players[j]->getScore() < players[j + 1]->getScore() || (players[j]->getScore() == players[j + 1]->getScore() && players[j]->getELO() < players[j + 1]->getELO()))
            {
                Player *temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

PlayerList *PlayerList::splice(const int startIndex, const int endIndex) const
{
    /* int newList_num = endIndex - startIndex;
    PlayerList *newList;
    newList->players = new Player *[newList_num];
    newList->numPlayers = newList_num;
    for (int i = 0; i < newList_num; i++)
    {
        newList->addPlayer(players[startIndex + i]);
    }
    return newList; */

    if (startIndex < 0 || endIndex > numPlayers)
    {
        return new PlayerList;
    }
    if (endIndex <= startIndex)
    {
        return new PlayerList;
    }
    PlayerList *list = new PlayerList;
    list->numPlayers = endIndex - startIndex;
    list->players = new Player *[list->numPlayers];
    for (int i = 0; i < list->numPlayers; ++i)
    {
        list->players[i] = players[startIndex + i];
    }
    return list;
}