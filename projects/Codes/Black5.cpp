//Implimentation
#include"Black5.h"

int random(const int x,const int y){
    int ran;
    srand(time(NULL));
    ran = (rand()%(y-x+1))+ x;
    return ran;
};

hand generateRandomCard() {
    int ran1, ran2;
    string suit,num;

    ran1 = (rand()% 4) + 1; 
    ran2 = (rand()% 13) + 1; 

    if (1 <= ran2 && ran2 <=10){
        num = to_string(ran2);
    }
    else if(ran2 == 11){
        num = "Jack";
        ran2 = 10;
    }
    else if(ran2 == 12){
        num = "Queen";
        ran2 = 10;
    }
    else if(ran2 == 13){
        num = "King";
        ran2 = 10;
    }

    switch(ran1){
        case 1:
            suit = "Diamond";
            break;
        case 2:
            suit = "Heart";
            break;
        case 3:
            suit = "Spade";
            break;
        case 4:
            suit = "Clover";
            break;
    }

    hand randomCard;
    randomCard.numback = ran2;
    randomCard.num = num;
    randomCard.suit = suit;
    return randomCard;
}


hand generateRandomCard(int random){
    int ran1, ran2,ranran;
    string suit,num;
    ranran = 1+(rand()%100);


    ran1 = rand() % 4 + 1; 

    switch(ran1){
        case 1:
            suit = "Diamond";
            break;
        case 2:
            suit = "Heart";
            break;
        case 3:
            suit = "Spade";
            break;
        case 4:
            suit = "Clover";
            break;
    }
    

    if(1 <= ranran && ranran <= random){
        ran2 = rand()%4;
        if(ran2 == 0){
            num = "10";
            ran2 = 10;
        }
        else if(ran2 == 1){
            num = "Jack";
            ran2 = 10;
        }
        else if(ran2 == 2){
            num = "Queen";
            ran2 = 10;
        }
        else if(ran2 == 3){
            num = "King";
            ran2 = 10;
        }
    }
    else{
        ran2 = rand() % 13 + 1; 
        if (2 <= ran2 && ran2 <=10){
            num = to_string(ran2);
        }
        else if(ran2 == 1){
            num = "Ace";
        }
        else if(ran2 == 11){
            num = "Jack";
            ran2 = 10;
        }
        else if(ran2 == 12){
            num = "Queen";
            ran2 = 10;
        }
        else if(ran2 == 13){
            num = "King";
            ran2 = 10;
        }
    }
    

    hand randomCard;
    randomCard.numback = ran2;
    randomCard.num = num;
    randomCard.suit = suit;
    return randomCard;
}


//need to modify
bool isBlackjack(int x,int y){
    bool jack = false;
    if(x == 10 || x == 11 || x == 12 || x == 13){
        if(y == 1){
            jack = true;
        }
    }
    else if(y == 10 || y == 11 || y == 12 || y == 13){
        if(x == 1){
            jack = true;
        }
    }
    return jack;
}

int randomProbability(){
    int proba;
    proba = (rand()%100)+1;
    return proba;
}


bool judgeFifteen(){
    bool check;
    int fift;
    fift = 1+(rand()%100);
    if(1 <= fift && fift <= 15){
        check = true;
    }
    else{
        check = false;
    }
    return check;
}



double updatePlayerBalance(double buyin,double bet,char wincond,char suggest,char choice){
    //The payout for a player winning a hand against the dealer is 1:1
    //The payout for winning a hand with Blackjack is 1.5:1. 
    double currentBalance;
    switch(wincond){
        case 'B':{
            if(suggest == choice){
                currentBalance = buyin + (bet * 1.5);
            }
            else{
                currentBalance = buyin + (bet * 1.5 + bet * 0.8);
            }
            break;
        }
        case 'U':{
            if(suggest == choice){
                cout << "Followed the suggestion\n";
                currentBalance = buyin + bet;
            }
            else{
                cout << "Did not follow the suggestion\n";
                currentBalance = buyin + (bet * 1.8);
            }
            break;
        }
        case 'D':{
            if(suggest != choice){
                cout << "Did not follow the suggestion\n";
                currentBalance = buyin - bet - (bet*0.2);
            }
            else{
                cout << "Followed the suggestion\n";
                currentBalance = buyin - (bet * 0.8);
            }
            break;
        }
        case 'T':{
            currentBalance = buyin;
            break;
        }

    }

    return currentBalance;
}


void displayoutcome(double x, double y, char z){
    cout << "--------------------\n";
    switch(z){
        case 'B':{
            cout <<"Congratulations! You hit Blackjack!\n";
            break;
        }
        case 'U':{
            cout <<"Congratulations! You win!\n";
            break;
        }
        case 'D':{
            cout <<"You lost\n";
            break;
        }
        case 'T':{
            cout <<"Tie\n";
            break;
        }
    }
    cout<<"Balance update : ";
    if(y-x >= 0){
        cout << "+$"<< y-x << endl;
    }
    else if(y-x < 0){
        cout << "-$"<< -1*(y-x) << endl;
    }
    cout << "Your balance is : $" << y << endl;
    return;
}



void checkAce(int &x, int &y){
    int caseOne,caseTwo;
    if(x == 1){
        caseOne = 1 + y;
        caseTwo = 11 + y;
        if(caseTwo > 21){
            x = 1;
            }
        else{
            x = 11;
        }
    }
    else if(y == 1){
        caseOne = 1 + x;
        caseTwo = 11 + x;
        if(caseTwo > 21){
            y = 1;
            }
        else{
            y = 11;
        }
    }
    else if(x == 1 && y == 1){
        x = 11;
    }
}

void displayGameSummary(int buyin, int balance, int tim, int win, int lose, int tie, int winjack, int losejack, int tiejack){
    int money;
    money  = balance- buyin;
    cout << "========== Game summary ==========\n";
    cout << "Total Round Played : " << tim << endl;
    cout << "Total Non Blackjack Win : " << win << endl;
    cout << "Total Blackjack Win : " << winjack << endl;
    cout << "Total Non Blackjack lose : " << lose << endl;
    cout << "Total Blackjack lose : " << losejack << endl;
    cout << "Total Non Blackjack tie : " << tie << endl;
    cout << "Total Blackjack tie : " << tiejack << endl;
    cout << "Final Balance : $" << balance << endl;
    cout << "Net Gain : $" << money << endl;

    return;
}
