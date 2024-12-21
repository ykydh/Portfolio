//Main function
#include"Black5.h"
int tim = 0;
int win = 0;
int lose = 0;
int tiet;
int winjack = 0;
int losejack = 0;
int tiejack = 0;
int main(){
    //seed for general use
    //srand(time(NULL));
    //seed for submission
    srand(2101);
    bool userWin,dealerWin,fifteen;
    int num,winCheckUser,winCheckDealer,userCards = 0,dealerCards=-1,count;
    char dec,cont,quit,wincond,suggest,choice,winner = 'O';
    double buyin,original,keep;
    double bet;
    int ranpr, threshold;
    string user;

    threshold = rand()%100;
    //initial setting of user name and buy-in
    cout<<"Input a user name : ";
    getline(cin,user);
    cout << "\n\nHello "<<user<<" !\n";
    num = random(100,1000);
    buyin = static_cast<double>(num);
    keep = buyin;
    cout << setprecision(2)<<fixed;
    do{
        count = 3;
        winner = ' ';
            //input bet
            do{
                do{
                    cout << "Your balance is $"<<buyin<<endl;
                    cout <<"\nPlease enter an amount of money you bet. \n$";
                    cin >> bet;
                    if( 0 < bet && bet <= buyin){
                        break;
                    }

                    cout << "\n\nError\nInput an amount of money less than or equal to your buyin\n";
                }while(bet > buyin);
            cout << "Conferm your bet.\n$"<<bet<<"\n(Y/N) : ";
            cin >> dec;
            dec = toupper(dec);
            if(dec == 'Y'){
                break;
            };
            }while(dec != 'Y');
            tim += 1;
            fifteen = judgeFifteen();
            dec = ' ';
            cout <<"\n\n"<<user << "---------------\n";
            if(fifteen == false){
            //not fifteen 
            hand randomCard1 = generateRandomCard();
            hand randomCard2 = generateRandomCard();
            cout << "Card1 --- "<< randomCard1.num<<" of "<< randomCard1.suit <<endl;
            cout << "Card2 --- "<< randomCard2.num<<" of "<< randomCard2.suit <<endl;
            checkAce(randomCard1.numback,randomCard2.numback);
            userCards = randomCard1.numback+ randomCard2.numback;
            userWin = isBlackjack(randomCard1.numback,randomCard2.numback);
            }
            else if(fifteen == true){
            //fifteen
            ranpr = randomProbability();
            hand randomCard1 = generateRandomCard(ranpr);
            ranpr = randomProbability();
            hand randomCard2 = generateRandomCard(ranpr);   
            cout << "Card1 --- "<< randomCard1.num<<" of "<< randomCard1.suit <<endl;
            cout << "Card2 --- "<< randomCard2.num<<" of "<< randomCard2.suit <<endl;
            checkAce(randomCard1.numback,randomCard2.numback);
            userCards = randomCard1.numback+ randomCard2.numback;
            userWin = isBlackjack(randomCard1.numback,randomCard2.numback);
            }

            //dealer
            cout <<"\nDealer---------------\n";
            hand dealercard1 = generateRandomCard();
            hand dealercard2 = generateRandomCard();
            checkAce(dealercard1.numback,dealercard2.numback);
            cout << "Card1 --- "<< dealercard1.num<<" of "<< dealercard1.suit <<endl;
            cout << "Card2 --- "<< "***"<<" of "<< "*** --> [Hidden]" <<endl;
            dealerWin = isBlackjack(dealercard1.numback,dealercard2.numback);

            
            if (userWin && !dealerWin){
                winner = 'U';
                winjack += 1;
            }
            else if (userWin && dealerWin){
                winner = 'T';
                tiejack += 1;
            }
            else if(!userWin && dealerWin){
                winner = 'D';
                losejack += 1;
            }

            switch(winner){
                case 'U':
                {
                    cout << "Black Jack! User win\n";
                    break;
                }
                case 'T':
                {
                    cout << "Tie\n";
                    break;
                }
                case 'D':
                {
                    cout << "Dealer win. Black Jack\n";
                    break;
                }
                case 'O':
                {
                    break;
                }
            } 
            //advise
            suggest = adviseOptimalActionOnLuck(threshold, userCards, dealercard1.numback);   
            //Player's turn
            do{
                if(userCards>21){
                    break;
                }
                cout <<"Choose your action\n\nStand : S\nHit  : H\n";
                if(count == 3){
                    cout << "Double down : D\n";
                }
                cout << "Choice : ";
                cin >> dec;
                cout << endl;
                dec = toupper(dec);
                if(count == 3){
                    choice = dec;
                }
                switch (dec)
                {
                case 'S':
                    break;
                
                case 'H':{
                    sleep(1);
                    hand randomCard3 = generateRandomCard();
                    cout << user <<"---\nCard"<<count<<" --- "<< randomCard3.num<<" of "<< randomCard3.suit <<endl;
                    
                    userCards += randomCard3.numback;
                    count++;
                    break;
                    }
                case'D':{
                    if((2*bet)< buyin){
                        sleep(1);
                        bet = 2 * bet;
                        hand randomCard3 = generateRandomCard();
                        cout << user <<"---\nCard3--- "<< randomCard3.num<<" of "<< randomCard3.suit <<endl;
                        userCards += randomCard3.numback;
                        break;
                    }
                    else;{
                        cout << "Error\nYou are not able to do double down because your balance is less than you need\n";
                        cout <<"Choose your action\n\nStand : S\nHit  : H\n";
                        cout << "Choice : ";
                        cin >> dec;
                        cout << endl;
                        dec = toupper(dec);
                        if(dec == 'H'){
                            sleep(2);
                            hand randomCard3 = generateRandomCard();
                            cout << user <<"---\nCard"<<count<<" --- "<< randomCard3.num<<" of "<< randomCard3.suit <<endl;
                            userCards += randomCard3.numback;
                            count++;
                        }
                        break;
                    }
                }
                default:
                    cout << "Will you quit? (Y/N)";
                    cin >> quit;
                    quit = toupper(quit);
                    break;
                }
                if(quit == 'Y')
                    break;
                else if(dec == 'S'|| dec == 'D')
                    break;
            }while(userCards<=21);
            
            //Dealer's turn
            if(userCards<=21){
            count = 3;
            sleep(2);
            cout << "\nThe hidden card has revealed\n" << "Card2 --- "<< dealercard2.num<<" of "<< dealercard2.suit <<endl;
            cout << "\nDealer---------------\n";
            cout << "Card1 --- "<< dealercard1.num<<" of "<< dealercard1.suit <<endl;
            cout << "Card2 --- "<< dealercard2.num<<" of "<< dealercard2.suit <<endl;
            dealerCards = dealercard1.numback + dealercard2.numback;
            if(dealerCards<=16){
                do{
                    sleep(1);
                    cout << "\nDealer hits\n";
                    hand dealercard3 = generateRandomCard();
                    dealerCards += dealercard3.numback;
                    sleep(2);
                    cout << "Card"<< count <<" --- "<< dealercard3.num<<" of "<< dealercard3.suit <<endl;
                    if(dealerCards>16){
                        break;
                    }
                }while(dealerCards <= 16);
            }
            cout << "\nDealer stands\n";
            }

            sleep(1);
            if(userCards>21){
                    cout << "The dealer's hidden card  was\n" << dealercard2.num<<" of "<< dealercard2.suit <<endl;
                    dealerCards = 0;
                }
            //check win
            if(dealerCards != 21 && userCards == 21){
                cout << user << " win "<< user <<" is black jack\n";
                wincond = 'B';
                winjack += 1;
            } 
            else if(dealerCards == 21 && userCards != 21){
                cout << "Dealer win dealer is black jack\n";
                wincond = 'D';
                losejack += 1;
            }
            else if(dealerCards == 21 && userCards == 21){
                cout << "Tie "<< user << " and dealer are both black jack\n";
                wincond = 'T';
                tiejack += 1;
            }
            else if(userCards>21 && dealerCards <= 21){
                cout <<"Dealer win "<< user << " is busted\n";
                wincond = 'D';
                lose += 1;
            }
            else if(dealerCards>21 && userCards <= 21){
                cout << user << " win dealer is busted\n";
                wincond = 'U';
                win += 1;
            }
            else if(dealerCards >= 21 && userCards >= 21){
                cout << "Tie "<< user << " and dealer are both busted\n";
                wincond = 'T';
                tiet += 1;
            }
            else{
                winCheckUser = 21 - userCards;
                winCheckDealer = 21 - dealerCards;
                if(winCheckUser < winCheckDealer){
                    cout << user <<" wins, "<< user <<" is " << (21 - winCheckUser) << " closer to 21\n";
                    wincond = 'U';
                    win += 1;
                }
                else if(winCheckDealer < winCheckUser){
                    cout << "Dealer wins, dealer is " <<(21 - winCheckDealer)<< " closer to 21\n";
                    wincond = 'D';
                    lose += 1;
                }
                else{
                    cout << "Tie.\n";
                    wincond = 'T';
                    tiet += 1;
                }
            }
            original = buyin;
            cout << "Suggest:"<<suggest<<" Choice :"<<choice<<endl;
            buyin = updatePlayerBalance(buyin,bet,wincond,suggest,choice);
            displayoutcome(original,buyin,wincond);
            if(buyin <= 0){
                break;
            }
            cout << "Will you continue? (Y/N) : ";
            cin >> cont;
            cont = toupper(cont);
            if(cont == 'N'){
                break;
            }
        }while(cont == 'Y' && buyin >= 0);
        if(buyin < 0){
            buyin = 0;
        }
        displayGameSummary(keep, buyin, tim, win, lose, tiet, winjack, losejack, tiejack);
        return 0;
    }

        
