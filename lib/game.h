#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "consts.h"
#include <ostream>
#include <iostream>
#include <map>

class BaseGame {
protected:
  Board * board;
  virtual int solve() = 0;
public:
  BaseGame();
  ~BaseGame();
  int run();
};


class ControlGame : public BaseGame {
protected:
    int solve() override {
        int hits = 0;
        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                if(this->board->guess(i, j) == ResponseType::HIT)
                {
                    hits += 1;
                    std::cout << "Control hits = " << hits << std::endl;
                }
            }
        }
        return hits;
    }
};

class AssignmentGame : public BaseGame {
  protected:
    //IMPLEMENT YOUR SEARCH ALGORITHM HERE
        int x, y = 0;
        std::map<int, int> xyMap;
        bool hitOnA = false;
        int hits = 0;
        int move_count = 0;
        for(int a = 0; a < WIDTH; a++)
        {
            hitOnA = false;
            //std::cout << "Loop A iteration: " << a << std::endl;
            for(int b = 0; b < HEIGHT - 1; b++)
            {
            move_count ++;
                //std::cout << "Loop B iteration: " << b << std::endl;
                if(this->board->guess(a, b) == ResponseType::HIT)
                {
                    if(!hitOnA){
                        hits += 1;
                        hitOnA = true;
                        std::cout << "Hit with b = " << b << " and a = " << a << std::endl;
                        std::cout << "Current hits = " << hits << std::endl;
                    }
                }
                else if(this->board->guess(a, b) == ResponseType::NEARMISS)
                {
                    //Setting the x to a and y to b allows me to store the initial values in order to return to where I was at so that it will continue to search. 
                    x = a;
                    y = b;
                    //The if/elseif from here makes it so that it loops around the starting position until the ship is found, then it returns to where it was before. 
                    //x -= 1;
                    //y -= 1;

                    for(int c = HEIGHT; c > b; c--){  
                        if(this->board->guess(x, y) == ResponseType::HIT)
                        {
                            if(!hitOnA){
                                hits += 1;
                                hitOnA = true;
                                std::cout << "Hit with c = " << c << " and a = " << a << std::endl;
                                std::cout << "Current hits = " << hits << std::endl;
                                break;
                            }
                        }

                        if(y > 0){
                            y -= 1;
                        }
                    }

                }
                else{
                    y += 1;
                }
                
                if (hits == 25)
                {
                    break;
                }

            }
        }
        return SHIP_COUNT;
};


#endif /* GAME_H */
