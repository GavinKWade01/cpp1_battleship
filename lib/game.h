#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "consts.h"

class BaseGame
{
protected:
    Board *board;
    virtual int solve() = 0;

public:
    BaseGame();
    ~BaseGame();
    int run();
};

class ControlGame : public BaseGame
{
protected:
    int solve() override
    {
        int hits = 0;
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (this->board->guess(i, j) == ResponseType::HIT)
                {
                    hits += 1;
                }
            }
        }
        return hits;
    }
};

class AssignmentGame : public BaseGame
{
protected:
    /*
    I made this so that I will scan the space for the response then if it is a hit or miss then it will continue on, but on a nearmiss it will then begin to circle the nearmiss.
    It will go through the if statement to circle the center then if it finds the ship it then breaks and goes back to where the initial Nearmiss was found.
    */
    int x, y = 0;
    int hits = 0;
    for (int a = 0; a < WIDTH; a++)
    {
        for (int b = 0; b < HEIGHT - 1; b++)
        {
            if (this->board->guess(a, b) == ResponseType::HIT)
            {
                hits += 1;
                break;
            }

            if (this->board->guess(a, b) == ResponseType::NEARMISS)
            {
                x = a;
                y = b;
                x -= 1;
                y -= 1;
            }
            else if (this->board->guess(x, y) != ResponseType::HIT)
            {
                if (this->board->guess(x, y) == ResponseType::HIT)
                {
                    hits += 1;
                    break;
                }
                x += 1;
            }
            else if (this->board->guess(x, y) != ResponseType::HIT)
            {
                if (this->board->guess(x, y) == ResponseType::HIT)
                {
                    hits += 1;
                    break;
                }
                x += 1;
            }
            else if (this->board->guess(x, y) != ResponseType::HIT)
            {
                if (this->board->guess(x, y) == ResponseType::HIT)
                {
                    hits += 1;
                    break;
                }
                x -= 2;
                y += 1;
            }
            else if (this->board->guess(x, y) != ResponseType::HIT)
            {
                if (this->board->guess(x, y) == ResponseType::HIT)
                {
                    hits += 1;
                    break;
                }
                x += 2;
            }
            else if (this->board->guess(x, y) != ResponseType::HIT)
            {
                if (this->board->guess(x, y) == ResponseType::HIT)
                {
                    hits += 1;
                    break;
                }
                x -= 2;
                y += 1;
            }
            else if (this->board->guess(x, y) != ResponseType::HIT)
            {
                if (this->board->guess(x, y) == ResponseType::HIT)
                {
                    hits += 1;
                    break;
                }
                x += 1;
            }
            else if (this->board->guess(x, y) != ResponseType::HIT)
            {
                if (this->board->guess(x, y) == ResponseType::HIT)
                {
                    hits += 1;
                    break;
                }
                x += 1;
            }
        }
    }
    return SHIP_COUNT;
};

#endif /* GAME_H */
