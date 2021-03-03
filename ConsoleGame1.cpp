#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <vector>
using namespace std;

int width = 25;//120
int height = 25;//29

class Entity {
public:
    int x, y, health, attack, xp, coins;
};
class Player :public Entity {
public:
    int level;
    Player() {
        x = 2;
        y = 2;
        level = 1;
        health = 5;//5
        attack = 2;//2
        coins = 0;//0
        xp = 0;
    }
    //1-27 y
    //1-118 x
};
class Snake :public Entity {
public:
    Snake() {
        x = (rand() % (width - 2) + 1);
        y = (rand() % (height - 2) + 1);
        health = 1;
        attack = 1;
        coins = 1;
        xp = 3;
    }
};
class Bear :public Entity {
public:
    Bear() {
        x = (rand() % (width - 2) + 1);
        y = (rand() % (height - 2) + 1);
        health = 10;
        attack = 5;
        coins = 3;
        xp = 7;
    }
};
class Dragon :public Entity {
public:
    Dragon() {
        x = (rand() % (width - 2) + 1);
        y = (rand() % (height - 2) + 1);
        health = 50;
        attack = 20;
        coins = 10;
        xp = 100;
    }
};
class Assassin :public Entity {
public:
    Assassin() {
        x = (rand() % (width - 2) + 1);
        y = (rand() % (height - 2) + 1);
        health = 250;
        attack = 100;
        coins = 1000;
        xp = 1000;
    }
};

class Game {
private:

    int snakeKills = 0;
    int bearKills = 0;
    int birdKills = 0;
    int dragonKills = 0;
    int invis = 0;
    int blink = 0;
    int light = 4;
    bool snakespawn = false;
    bool bearspawn = false;
    bool dragonspawn = false;
    bool assassinspawn = false;
    bool quit;
    bool occupied = false;
    bool win = false;
    Player* player;
    Snake* snake;
    Bear* bear;
    Dragon* dragon;
    Assassin* assassin;
    vector<Snake> snakeList;
    vector<Bear> bearList;
    vector<Dragon> dragonList;
public:
    Game() {
        quit = false;
        player = new Player;
    }
    ~Game()
    {
        delete player;
    }
    void Draw() {

        string output;
        if (!win) {
            for (int i = 0; i < height; i++) {//height i y
                for (int j = 0; j < width; j++) {//width j x
                    if (i == 0 || i == height - 1) {
                        output += 'X';
                        occupied = true;
                    }
                    else if (j == 0 || j == width - 1) {
                        output += 'X';
                        occupied = true;
                    }
                    else if (player->x == j && player->y == i) {
                        output += 'O';
                        occupied = true;
                    }
                    else if ((abs(player->x - j) + abs(player->y - i)) >= light) {
                        output += '.';
                        occupied = true;
                    }


                    vector<Dragon>::iterator itD;
                    for (itD = dragonList.begin(); itD != dragonList.end(); ++itD) {
                        if ((itD->x == j) && (itD->y == i)) {
                            if (!occupied) {
                                output += 'D';
                                occupied = true;
                            }
                        }
                    }
                    vector<Bear>::iterator itB;
                    for (itB = bearList.begin(); itB != bearList.end(); ++itB) {
                        if ((itB->x == j) && (itB->y == i)) {
                            if (!occupied) {
                                output += 'B';
                                occupied = true;
                            }
                        }
                    }
                    vector<Snake>::iterator itS;
                    for (itS = snakeList.begin(); itS != snakeList.end(); ++itS) {
                        if ((itS->x == j) && (itS->y == i)) {
                            if (!occupied) {
                                output += 'S';
                                occupied = true;
                            }
                        }
                    }
                    if (assassinspawn) {
                        if (invis >= 16000) {
                            if (assassin->x == j && assassin->y == i) {
                                output += 'A';
                                occupied = true;
                            }
                            invis++;
                            if (invis == 20000) {
                                invis = 0;
                            }
                        }
                        else {
                            invis++;
                        }

                    }

                    if (!occupied) {
                        output += ' ';
                    }

                    occupied = false;

                }
                if (i == 0)
                    output += "\t BEASTIARY";
                if (i == 1)
                    output += "\t --------------------";
                if (i == 2) {
                    output += "\t(S)NAKES: KILLED:";
                    output += std::to_string(snakeKills);
                    output += " ATT:1 HP:1 XP:3";
                }
                if (i == 3 && bearspawn) {
                    output += "\t(B)EARS: KILLED:";
                    output += std::to_string(bearKills);
                    output += " ATT:5 HP:10 XP:7";
                }
                if (i == 4 && dragonspawn) {
                    output += "\t(D)RAGONS: KILLED:";
                    output += std::to_string(dragonKills);
                    output += " ATT:20 HP:50 XP:100";
                }
                if (i == 5 && assassinspawn) {
                    output += "\t(A)SSASSIN KILLABLE?  ATT:100 HP:250 XP:WIN   HIDES IN THE SHADOWS";
                }
                output += '\n';
            }
            output += "HEALTH: ";
            output += std::to_string(player->health);
            output += "\tATTACK: ";
            output += std::to_string(player->attack);
            output += "\tLEVEL: ";
            output += std::to_string(player->level);
            output += "\tCOINS: ";
            output += std::to_string(player->coins);
            output += "\nCONTROLS: W^| A<| S>| Dv \t(Q)UIT\n(H)EAL: 3 HP FOR 5 COINS\t(L)IGHT: 1 MORE LIGHT FOR 10 COINS\nXP: ";
            for (int i = 0; i < player->xp % 10; i++) {
                output += 'O';
            }
            for (int i = 0; i < (10 - (player->xp % 10)); i++) {
                output += 'o';
            }
            output += ' ';
            output += std::to_string((player->xp) % 10);
            output += "/10";
            system("cls");
            cout << output;
            output = "";
        }
        else {

            cout << " __   __  _______  __   __    _     _  _______  __    _ " << endl;
            cout << "|  | |  ||       ||  | |  |  | | _ | ||       ||  |  | |" << endl;
            cout << "|  |_|  ||   _   ||  | |  |  | || || ||   _   ||   |_| |" << endl;
            cout << "|       ||  | |  ||  |_|  |  |       ||  | |  ||       |" << endl;
            cout << "|_     _||  |_|  ||       |  |       ||  |_|  ||  _    |" << endl;
            cout << "  |   |  |       ||       |  |   _   ||       || | |   |" << endl;
            cout << "  |___|  |_______||_______|  |__| |__||_______||_|  |__| ";
            Sleep(10000);
            quit = true;
        }

    }

    void Input() {
        if (GetKeyState('A') & 0x8000)
        {
            if (player->x != 1)
                player->x--;
        }
        if (GetKeyState(VK_LEFT) & 0x8000)
        {
            if (player->x != 1)
                player->x--;
        }
        if (GetKeyState('D') & 0x8000)
        {
            if (player->x != width - 2)
                player->x++;
        }
        if (GetKeyState('W') & 0x8000)
        {
            if (player->y != 1)
                player->y--;
        }
        if (GetKeyState('S') & 0x8000)
        {
            if (player->y != height - 2)
                player->y++;
        }
        if (GetKeyState('Q') & 0x8000)
        {
            quit = true;
        }
        if (GetKeyState('H') & 0x8000)
        {
            if (player->coins >= 5) {
                player->coins = player->coins - 5;
                player->health = player->health + 3;
            }
        }
        if (GetKeyState('L') & 0x8000)
        {
            if (player->coins >= 10) {
                player->coins = player->coins - 10;
                light = light + 1;;
            }
        }
    }

    void Logic() {
        bool newSnake = false;
        bool newBear = false;
        bool newDragon = false;
        int templevel;
        if (!snakespawn) {
            snakespawn = true;
            snake = new Snake;
            snakeList.push_back(*snake);
        }

        vector<Snake>::iterator itS;
        for (itS = snakeList.begin(); itS != snakeList.end(); ++itS) {
            if ((player->x == itS->x) && (player->y == itS->y)) {
                player->health -= itS->attack;
                itS->health -= player->attack;
            }
            if (itS->health <= 0) {
                player->xp += itS->xp;
                player->coins += itS->coins;
                itS->health = 1;
                itS->y = (rand() % (height - 2) + 1);
                itS->x = (rand() % (width - 2) + 1);
                snakeKills++;
                if ((snakeKills % 5) == 0 && snakeKills <= 25) {
                    newSnake = true;
                }
                if (snakeKills == 1 && !bearspawn) {
                    bearspawn = true;
                    bear = new Bear;
                    bearList.push_back(*bear);
                }
            }
        }
        vector<Bear>::iterator itB;
        for (itB = bearList.begin(); itB != bearList.end(); ++itB) {
            if ((player->x == itB->x) && (player->y == itB->y)) {
                player->health -= itB->attack;
                itB->health -= player->attack;
            }
            if (itB->health <= 0) {
                player->xp += itB->xp;
                player->coins += itB->coins;
                itB->health = 1;
                itB->y = (rand() % (height - 2) + 1);
                itB->x = (rand() % (width - 2) + 1);
                bearKills++;
                if ((bearKills % 5) == 0 && bearKills <= 25) {
                    newBear = true;
                }
                if (bearKills == 1 && !dragonspawn) {
                    dragonspawn = true;
                    dragon = new Dragon;
                    dragonList.push_back(*dragon);
                }
            }
        }
        vector<Dragon>::iterator itD;
        for (itD = dragonList.begin(); itD != dragonList.end(); ++itD) {
            if ((player->x == itD->x) && (player->y == itD->y)) {
                player->health -= itD->attack;
                itD->health -= player->attack;
            }
            if (itD->health <= 0) {
                player->xp += itD->xp;
                player->coins += itD->coins;
                itD->health = 1;
                itD->y = (rand() % (height - 2) + 1);
                itD->x = (rand() % (width - 2) + 1);
                dragonKills++;
                if ((dragonKills % 5) == 0 && dragonKills <= 25) {
                    newDragon = true;
                }
                if ((dragonKills == 5 && !assassinspawn)) {
                    assassinspawn = true;
                    assassin = new Assassin;
                }

            }
        }
        if (assassinspawn) {
            if ((player->x == assassin->x) && (player->y == assassin->y)) {
                player->health -= assassin->attack;
                assassin->health -= player->attack;
                if (assassin->health <= 0) {
                    win = true;
                }
            }
        }


        if (newSnake) {
            newSnake = false;
            snake = new Snake;
            snakeList.push_back(*snake);
        }
        if (newBear) {
            newBear = false;
            bear = new Bear;
            bearList.push_back(*bear);
        }
        if (newDragon) {
            newDragon = false;
            dragon = new Dragon;
            dragonList.push_back(*dragon);
        }
        if (blink != 5) {
            blink++;
        }
        else {
            blink = 0;
            vector<Snake>::iterator itS;
            for (itS = snakeList.begin(); itS != snakeList.end(); ++itS) {
                int roll = (rand() % 6);
                if (roll == 0) {
                    if (itS->x != 1)
                        itS->x--;
                }
                if (roll == 1) {
                    if (itS->x != width - 2)
                        itS->x++;
                }
                if (roll == 2) {
                    if (itS->y != 1)
                        itS->y--;
                }
                if (roll == 3) {
                    if (itS->y != height - 2)
                        itS->y++;
                }
            }
            vector<Bear>::iterator itB;
            for (itB = bearList.begin(); itB != bearList.end(); ++itB) {
                int roll = (rand() % 8);
                if (roll == 0) {
                    if (itB->x != 1)
                        itB->x--;
                }
                if (roll == 1) {
                    if (itB->x != width - 2)
                        itB->x++;
                }
                if (roll == 2) {
                    if (itB->y != 1)
                        itB->y--;
                }
                if (roll == 3) {
                    if (itB->y != height - 2)
                        itB->y++;
                }
            }
            vector<Dragon>::iterator itD;
            for (itD = dragonList.begin(); itD != dragonList.end(); ++itD) {
                int roll = (rand() % 10);
                if (roll == 0) {
                    if (itD->x != 1)
                        itD->x--;
                }
                if (roll == 1) {
                    if (itD->x != width - 2)
                        itD->x++;
                }
                if (roll == 2) {
                    if (itD->y != 1)
                        itD->y--;
                }
                if (roll == 3) {
                    if (itD->y != height - 2)
                        itD->y++;
                }
            }
            if (assassinspawn) {
                int roll = (rand() % 4);
                if (roll == 0) {
                    if (assassin->x != 1)
                        assassin->x--;
                }
                if (roll == 1) {
                    if (assassin->x != width - 2)
                        assassin->x++;
                }
                if (roll == 2) {
                    if (assassin->y != 1)
                        assassin->y--;
                }
                if (roll == 3) {
                    if (assassin->y != height - 2)
                        assassin->y++;
                }
            }


        }

        ///////////////////////////////////////
        ///////////////////////////////////////
        templevel = player->level;

        player->level = (player->xp / 10) + 1;

        if (templevel != player->level) {
            player->health = 3 + 2 * player->level;
            player->attack = 1 + player->level;
        }
        if (player->health <= 0) {
            system("cls");
            cout << " __   __  _______  __   __    ___      _______  _______  ______\n";
            cout << "|  | |  ||       ||  | |  |  |   |    |       ||       ||      |\n";
            cout << "|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||   ___|\n";
            cout << "|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |  |___\n";
            cout << "|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||   ___|\n";
            cout << "  |   |  |       ||       |  |       ||       | _____| ||  |___\n";
            cout << "  |___|  |_______||_______|  |_______||_______||_______||______|\n";
            Sleep(5000);
            quit = true;
        }
    }

    void Run() {
        while (!quit)
        {
            Input();
            Draw();
            Logic();
            Sleep(15);
        }
    }
};


int main()
{
    bool quit = false;
    srand(time(NULL));
    Game game1;
    game1.Run();
    cout << "Game over!" << endl;
    return 0;
}