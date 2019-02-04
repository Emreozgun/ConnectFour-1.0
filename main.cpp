#include <iostream>
#include<cctype>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <typeinfo>
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include "ConnectFourAbstract.h"
#include "Cell.h"
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

using namespace std;


int main()
{
    using namespace ConnectFourGame;
    using namespace Str;

    //Computer making different moves to every compiling with randomly
    srand(time(NULL));
    char PlayMode;
    int wid,heig;

    string line;
    //will take game mode while user input 'S' or 'M'
    do
    {
        cout << "Choose your play game mod( P (plus), D(diag) ve U(undo)) ?" << endl;

        line = readLine();
        //take only first char
        PlayMode = toupper(line[0]);
        //then check that char is it 'S' or 'M'
        if (PlayMode == 'P' || PlayMode == 'D' || PlayMode == 'U')
        {
            break;
        }
        else
        {
            cout << "Error input !" << endl;
        }

    }
    while (1);

    do
    {
        cout << "How many size do you need to play(width and height) ?" << endl;
        //if user enter input different from int like letter ask again """"""""""""""""""""""---------->>>READLINE HALİNE ÇEVİR
        if (!(cin >> wid))
        {
            heig = 0;
            wid = 0;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(!(cin >> heig))
        {
            wid = 0;
            heig = 0;
        }
        //Error input about size
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (wid >= 27 || wid <= 0 || heig <= 0)
            cout << "Error input" << endl;
        else
            break;

    }
    while (1);

    while (1)
    {

        // I use one object with pointer for single and multiplayer games
        if(PlayMode == 'P')
        {

            ConnectFourPlus game1(wid,heig);
            game1.setGameType(Plus);
            //Game created then print,take inputs and play
            game1.startingInput();
            game1.printGame();
            game1.playSingleGame();
            //game will finish in playSingleGame function then delete games object then finish the program
            break;
        }

        if(PlayMode == 'D')
        {
            ConnectFourDiag game2(wid,heig);
            game2.setGameType(Diag);
            //Game created then print,take inputs and play
            game2.startingInput();
            game2.printGame();
            game2.playSingleGame();
            //game will finish in playSingleGame function then delete games object then finish the program
            break;
        }

        if(PlayMode == 'U')
        {
            ConnectFourPlusUndo game3(wid,heig);
            game3.setGameType(PlusUndo);

            //Game created then print,take inputs and play
            game3.startingInput();
            game3.printGame();
            game3.playSingleGame();
            //game will finish in playSingleGame function then delete games object then finish the program

            break;
        }
    }

    return 0;

}
