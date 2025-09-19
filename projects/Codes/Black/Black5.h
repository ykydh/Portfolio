//Header
#ifndef BLACK_H_
#define BLACK_H_
#include<iostream>
#include<string>
#include<iomanip>
#include<unistd.h>
#include<ctime>
#include<cstdlib>
using namespace std;


struct hand {
    int numback;
    string num;
    string suit;
};

//Produce integers between x and y
//Precondition none
//Post condition none
int random(const int x,const int y);

//choose number
//Precondition none
//Post condition none
hand generateRandomCard();

//choose number when fifteen percent chance is true
//Precondition take integer percentage
//Post condition none
hand generateRandomCard(int random);

//output a suit to a display
//pre parameter should be a string of suits
//post output a suit
void suit(string suit);

//check whether hand is black jack or not
//pre parameter has to be an integer card num
//post return true when black jack false when not a black jack
bool isBlackjack(int x,int y);


//choose random probability from 1% to 100 %
//pre none
//post return a probability as an float
int randomProbability();

//check whether the round has increased possibility
//pre none
//post return bool value (when 15% chance true: normal false)
bool judgeFifteen();


//update players balance
//pre a parameter have to be a char win condition and current balance and bet amount
//post return player's current balance
double updatePlayerBalance(double buyin,double bet,char wincond,char suggest,char choice);

//display outcome
//pre take initial balance and a balance after modification and  win condition as parameters 
//post print outcomes to the display
void displayoutcome(double x, double y, char z);

//check ace and determin 1 or 11
//pre two integers which represent values of cards
//post choose 1 or 11 and return as reference
void checkAce(int &x, int &y);

//dispay game summary
//pre take initial and current balance, counted 6 game conditions, and a total game number as parameters
//post display summary to a display
void displayGameSummary(int buyin, int balance, int tim, int win, int lose, int tie, int winjack, int losejack, int tiejack);

template <typename T>
    char adviseOptimalActionOnLuck(const T threshold, const int player, const int dealerUp){
      char recommend;
      int possibility;
      possibility = rand()%100;
      int decision;
      cout << "Suggestion : ";
      if (possibility >= threshold){
        if(9 <= player && player <= 11){
          cout << "Double down\n";
          recommend = 'D';
        }
        else if(player <= 11){
          cout << "Hit\n";
          recommend = 'H';
        }
        else if(12 <= player && player <= 16){
          if(7 <= dealerUp){
            cout << "Hit\n";
            recommend = 'H';
          }
          else{
            cout << "Stand\n";
            recommend = 'S';
          }
        }
        else if(17 <= player){
          cout << "Stand\n";
          recommend = 'S';
        }
      }
      else{
        decision = rand()%2;
        if(decision == 0){
          cout << "Hit\n";
          recommend = 'H';
        }
        else if(decision == 1){
          cout << "Stand\n";
          recommend = 'S';
        }
      }
      return recommend;
    }


#endif
