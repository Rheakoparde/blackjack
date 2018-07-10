/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Rhea Koparde
 * USC email: koparde@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;
//int cards[NUM_CARDS];

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/ 
  
  for(int i = 0; i <NUM_CARDS; i++){
  cards[i]=i;  
  }
  for(int i=NUM_CARDS-1; i>0;i--){
    int j= rand() % (i + 1);
    int swap = cards[i];
    cards[i]=cards[j];
    cards[j] = swap;
  }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
  int typeCard = id % 13;
  cout << type[typeCard];
  cout << "-";
  int suitCard = id/13;
  cout << suit[suitCard];
  
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int valueCard = id % 13;
  int c = value[valueCard]; // value stored in variable
  return c;
  
}  

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for(int i=0; i<numCards; i++){
    printCard(hand[i]);
    cout << " ";
  }    
  cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int sum =0;
  for(int i=0; i<numCards; i++){
    sum = sum + cardValue(hand[i]);  
  } 
  for(int i=0; i<numCards;  i++){
    if((hand[i] == 12 || hand[i] == 25 || hand[i] == 38 
      || hand[i] == 51) && sum > 21){
      sum = sum-10;
      
    }

  }
  return sum;
  
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);
  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  char playAgain='y';
  
  while(playAgain=='y'){
    shuffle(cards);
    dhand[0]=cards[1];  //initialization for the first 4 given cards,
    dhand[1]=cards[3]; //2 for dealer and 2 for player
    phand[0]=cards[0];
    phand[1]=cards[2];
    int numCardsForDealer=2;
    int numCardsForPlayer=2;
    int numCardsFromDeck= 4;
  
    cout << "Dealer: " << "?" << " "; //initial statement
    printCard(dhand[1]);
    cout << endl;
      
    cout << "Player: ";
    printCard(phand[0]);
    cout << " ";
    printCard(phand[1]);
    cout << endl;
   
    while(getBestScore(phand, numCardsForPlayer) <= 21) 
    {                       //when the player's given cards are already 21
      if(getBestScore(phand, numCardsForPlayer)==21){ 
        while(getBestScore(dhand, numCardsForDealer) < 17){
          dhand[numCardsForDealer] = cards[numCardsFromDeck];
          numCardsForDealer++;
          numCardsFromDeck++;  
        }
        cout << "Dealer: ";
        printHand(dhand, numCardsForDealer);
        break;
     }
      
      cout << "Type 'h' to hit or 's' to stay:" << endl; //game rules
      char play;
      cin >> play; 
      if(play=='h'){
       
        phand[numCardsForPlayer] = cards[numCardsFromDeck];
         numCardsForPlayer++; 
        cout << "Player: ";
        printHand(phand, numCardsForPlayer);
        cout << " ";
        numCardsFromDeck++;
      }
      else if(play=='s'){
        dhand[numCardsForDealer] = cards[numCardsFromDeck];
        while(getBestScore(dhand, numCardsForDealer)<17){
          numCardsFromDeck++;
          numCardsForDealer++;
          cout << " ";
          dhand[numCardsForDealer] = cards[numCardsFromDeck];  
        }  // after staying checks if total of dealer is greater than 21
        cout << "Dealer: ";    
        printHand(dhand, numCardsForDealer);
        if(getBestScore(dhand, numCardsForDealer)>21){ 
        cout << "Dealer bust" << endl;                  //if not it exits the loop
        cout << "Win ";
        cout << getBestScore(phand, numCardsForPlayer);
        cout << " ";
        cout << getBestScore(dhand, numCardsForDealer);
        cout << endl; 
        break; 
        }   //finding who wins or loses based on score only
        if(getBestScore(phand, numCardsForPlayer) < 21      
          && getBestScore(dhand, numCardsForDealer) < 21)
        {
          if(getBestScore(phand, numCardsForPlayer)> 
            getBestScore(dhand, numCardsForDealer))
          {
            cout << "Win  ";
            cout <<  getBestScore(phand, numCardsForPlayer); 
            cout << " ";
            cout << getBestScore(dhand, numCardsForDealer);
            cout << endl;
            break;
          }

          else if(getBestScore(dhand, numCardsForDealer)> 
            getBestScore(phand, numCardsForPlayer))
          {
            cout << "Lose ";
            cout << getBestScore(phand, numCardsForPlayer); 
            cout << " ";
            cout << getBestScore(dhand, numCardsForDealer);
            cout << endl;
            break;
          }
           
          else{
           break;
          }
        }    
      }
    }     
        // for every output after calculating the score
    if(getBestScore(phand, numCardsForPlayer) >21){ 
      cout << "Player bust" << endl;
      cout << "Lose ";
      cout << getBestScore(phand, numCardsForPlayer);
      cout << " ";
      cout << getBestScore(dhand, numCardsForDealer);
      cout << endl;  
      
    }
    else if(getBestScore(phand, numCardsForPlayer)==
      getBestScore(dhand, numCardsForDealer)){
      cout << "Tie ";
      cout << getBestScore(phand, numCardsForPlayer);
      cout << " ";
      cout << getBestScore(dhand, numCardsForDealer);
      cout << endl;  
    }

    else if(getBestScore(phand, numCardsForPlayer)==21){
      cout << "Win ";
      cout << getBestScore(phand, numCardsForPlayer);
      cout << " ";
      cout << getBestScore(dhand, numCardsForDealer);
      cout << endl;  
    }

    else if(getBestScore(dhand, numCardsForDealer)==21){
      cout << "Lose ";
      cout << getBestScore(phand, numCardsForPlayer);
      cout << " ";
      cout << getBestScore(dhand, numCardsForDealer);
      cout << endl;  
    }

    // to create the play again loop after the first round
  
    playAgain = 'n';
    cout << "Play Again? [y/n]" << endl;   
    cin >> playAgain;
    
  }
  return 0;

}
