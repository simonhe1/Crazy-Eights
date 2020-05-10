#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <stdlib.h>
#define ALPHABETSIZE 52
using namespace std;

const string ALPHABET[] {"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)","(l)","(m)","(n)","(o)","(p)","(q)","(r)","(s)","(t)","(u)","(v)","(w)","(x)","(y)","(z)"};
class Card 
{
    char _suite;
    string _num;

    public:
        Card()
        {
            _suite = ' ';
            _num = "";
        }

        Card(char suite, string num)
        {
            _suite = suite;
            _num = num;
        }

        bool compare(Card secondCard)
        {
            // If wild card
            if(secondCard._num == "8" || secondCard._num == "*")
            {
                return true;
            }

            if(_suite == secondCard._suite || _num == secondCard._num)
            {
                return true;
            }

            return false;
        }

        char getSuit() { return _suite; }
        string getNum() { return _num; }
        void setSuit(char suite) { _suite = suite; }
        void setNum(string num) { _num = num; }

        friend ostream& operator<<(ostream& os, const Card& card)
        {
            os << card._suite << card._num << "\t";
            return os;
        }
};

class Player
{
    vector<Card> hand;

    public:
    Player()
    {

    }

    void addCard(Card card)
    {
        hand.push_back(card);
    }

    void showHand()
    {
        int index = 0;
        for(auto i = hand.begin();i != hand.end(); ++i)
        {
            cout<<ALPHABET[index++]<<" "<<*i;
        }
        cout<<ALPHABET[index]<< " draw"<<endl;
    }

    void playCard(Card card)
    {
        int index = 0;
        for(auto i = hand.begin();i != hand.end(); ++i)
        {
            index++;
            if(card.compare(*i)) break;
        }
    }
};

void intializeArray(Card* deck)
{
    /* Initialize cards */
    // Aces
    deck[0] = Card('D',"A");
    deck[1] = Card('C',"A");
    deck[2] = Card('H',"A");
    deck[3] = Card('S',"A");
    // 2 ~ 10
    for(int i=2;i<11;i++)
    {
        deck[(i-1)*4] = Card('D', to_string(i));
        deck[(i-1)*4+1] = Card('C', to_string(i));
        deck[(i-1)*4+2] = Card('H', to_string(i));
        deck[(i-1)*4+3] = Card('S', to_string(i));
    }
    // Jack, Queen, King
    deck[40] = Card('D', "J");
    deck[41] = Card('C', "J");
    deck[42] = Card('H', "J");
    deck[43] = Card('S', "J");

    deck[44] = Card('D', "Q");
    deck[45] = Card('C', "Q");
    deck[46] = Card('H', "Q");
    deck[47] = Card('S', "Q");

    deck[48] = Card('D', "K");
    deck[49] = Card('C', "K");
    deck[50] = Card('H', "K");
    deck[51] = Card('S', "K");
}

void intializePlayerHand(Card* deck, Player* players, int& size)
{
    // In this version, deals 6 cards to each player at random
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<6;j++)
        {

            // Generate random number between 0 and size-1
            int randomIndex = rand()%size;
            // Get a copy of the postion at size-1 and switch it with the random index card
            Card temp = deck[randomIndex];
            players[i].addCard(deck[randomIndex]);
            deck[randomIndex] = deck[size-1];
            deck[size-1] = temp;
            size--;
        }
    }
}


int main()
{
    Card deck[ALPHABETSIZE];
    int deckSize = 52;

    vector<Card> pile;

    Player players[4];

    intializeArray(deck);

    intializePlayerHand(deck, players, deckSize);

    // Get a random card to put on top of the pile
    int randomIndex = rand()%deckSize;
    Card temp = deck[randomIndex];
    deck[randomIndex] = deck[deckSize-1];
    deck[deckSize-1] = temp;
    deckSize--;
    if(temp.getNum() == "8")
    {
        while(true)
        {
            char suite;
            cout<<"(a) D (b) C (c) H (d) S"<<endl;
            cout<<"Choose a suite: ";
            cin>>suite;
            // Check if valid suite
            if(suite - 'a' >= 0 && suite - 'a' <=3)
            {
                pile.push_back(Card(suite,"*"));
                break;
            }
        }
    }
    else
    {
        pile.push_back(temp);
    }
    
    cout << "Pile has " << pile.back() << " <-- your turn" << endl;
    cout << endl;
    players[0].showHand();
    cout << endl;
    cout << "Which one to play? ";
    char choice;
    cin >> choice;
    
    for(Player p : players)
    {
        p.showHand();
    }
}