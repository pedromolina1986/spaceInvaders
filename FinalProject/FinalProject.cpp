// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Final Project: SODV1101 - Programming Fundamentals
Student ID: 467777
Student name: Pedro Kuchak Molina

References:
Clear screen: https://cplusplus.com/articles/4z18T05o/
Vectors: https://en.cppreference.com/w/cpp/container/vector
Structures: Googled "C++ How create structures" and https://www.w3schools.com/cpp/cpp_structs.asp
Key press: Googled "C++ how to auto collect keyboard commands" https://coderslegacy.com/c/detect-key-presses-cpp/
Ansi colors: Googled "C++ how to give color in the cout" https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c

Help with C++ code: https://stackoverflow.com/questions

*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

using namespace std;

//START - GLOBAL VARIABLES

//gaming components
//screen
const int width = 30;
const int height = 20;
char screen[height][width];
bool firstTime = true;

//gaming components
struct Bullet {
    int x, y;
    bool active;
};

struct Enemy {
    int x, y;
    bool alive;    
};

struct Spaceship {
    char printingType;
    string name;
};

struct Player {    
    int lifes;
    int points;
    int x;
    int y;
    string name;    
    Spaceship SpaceshipType;
};

struct EnemyBullet {
    int x, y;
    bool active;
};


//gaming components variables
vector<Bullet> bullets;
vector<EnemyBullet> enemyBullets;
vector<Enemy> enemies;
vector<Player> players;
vector<Spaceship> spaceships;
Player currentPlayer;


//gaming controller variables
bool gameOver = false;
int level = 0;
int maxPoints = 0;
int enemiesCount = 0;
int topScore = 0;

//END - GLOBAL VARIABLES

//START - spacehisps controlle
static void genSpaceships() {
    spaceships.push_back({ '^', "Destroyer" });
    spaceships.push_back({ 'T', "T-Fighter" });
    spaceships.push_back({ 'A', "A-Forcce" });
    spaceships.push_back({ 'V', "Voyager" });
    spaceships.push_back({ '8', "8Ball" });
}

static vector<Spaceship> getSpaceships(string name) {
    vector<Spaceship> retShips;
    for (auto& ship : spaceships) {
        if (ship.name == name) {
            retShips.push_back(ship);
        }
    }
    return(retShips);
}

static Spaceship getSpaceshipByName(string name) {
    vector<Spaceship> retShips;
    for (auto& ship : spaceships) {
        if (ship.name == name) {
            return(ship);
        }
    }    
}

static void printSpaceships() {
    int x = 1;
    string typingString = "";
    for (auto& ship : spaceships) {        
        cout << x << ". " << ship.printingType << " - " << ship.name << endl;
        x++;
    }
    cout << x << ". CREATE YOUR OWN SPACESHIP" << endl;
}

//END - spacehisps controlle

//START - Player controller
static void playerRegistration() {

    /*
    int lifes = 3;
    int points = 0;
    int x = width / 2;
    int y = height - 2;
    string name = "";
    Spaceship SpaceshipType;
    */

    //create a new player
    system("cls");

    Player newPlayer;
    int sleepTime = 500;

    cout << "Hurry UP!" << endl << endl;
    Sleep(sleepTime);
    cout << "Space invaders are coming to EARTH!" << endl << endl;
    Sleep(sleepTime);
    cout << "HELP US to defend our land and join our TEAM!" << endl;
    Sleep(sleepTime);
    cout << ".";
    Sleep(sleepTime);
    cout << ".";
    Sleep(sleepTime);
    cout << ".";
    Sleep(sleepTime);
    cout << endl << "What is your name DEFENDER:" << endl;
    
    if (!firstTime) {
        cin.ignore();
        cin.clear();
    }
    else {
        firstTime = false;
    }
    getline(cin, newPlayer.name);
 
    cout << endl << endl << "LET's FIGHT " << newPlayer.name << "!!!!" << endl << endl;
    Sleep(sleepTime);
    cout << "Now pick your SPACESHIP (Type the number and then ENTER):" << endl << endl;
    int spacePick = 0;
    do {
        printSpaceships();
        cin >> spacePick;
        if (!(spacePick >= 0 && spacePick <= spaceships.size() + 1)) {
            cout << endl << "COME ON FIGHTER!!! Pick a better SPACESHIP:" << endl << endl;
        }
        if (spacePick == spaceships.size() + 1) {
            Spaceship newSpaceship;
            cout << "Type your Spaceship name:" << endl;
            cin.ignore();
            cin.clear();
            getline(cin, newSpaceship.name);
            cout << "Type your Spaceshipr character:" << "";
            cin >> newSpaceship.printingType;
            spaceships.push_back(newSpaceship);
        }
    } while (!(spacePick >= 0 && spacePick <= spaceships.size()));

    newPlayer.SpaceshipType = spaceships[spacePick - 1];
    newPlayer.lifes = 3;
    newPlayer.points = 0;
    newPlayer.x = width / 2;
    newPlayer.y = height - 2;

    players.push_back(newPlayer);
};
//END - Player controller

//START - GAME controller
// Function to perform Bubble Sort on players based on points socred.
static void sortRanking(bool ascending) {

    bool allowSwap = false;

    int iterarions = players.size();

    for (int i = 0; i < iterarions - 1; i++)
    {
        allowSwap = false;
        for (int j = i; j < iterarions; j++)
        {
            if (ascending) {
                if (players[i].points > players[j].points) {
                    allowSwap = true;
                }
            }
            else {
                if (players[i].points < players[j].points) {
                    allowSwap = true;
                }
            }
            if (allowSwap) {
                swap(players[j], players[i]);
                allowSwap = false;
            }

        }
    };
}

static void printScoreRanking() {
    
    //sort rank
    sortRanking(0);

    //print rank
    cout << "POWER RANKING" << endl;
    for (auto& player : players) {        
        cout << " | " + player.name.substr(0, 15) << " | " << player.points << " | ";
        cout << player.SpaceshipType.name << "(" << player.SpaceshipType.printingType << ")" << endl;
    }
    topScore = players[0].points;
}

void printSizeTable(int size) {
    for (int i = 0; i < size; i++)
    {
        cout << "=";
    };
}

static void setup() {
    //clear screend and variables
    system("cls");
    bullets.clear();
    enemyBullets.clear();
    enemies.clear();
    enemiesCount = 0;
    if (level == 0) {
        currentPlayer = players.back();
    }

    // Create enemies according level
    for (int x = 2; x < width - 2; x += 4) {
        for (int y = 2; y < level + 2; y++) {
            enemies.push_back({ x, y, true });
            //created to optimize the screen update
            enemiesCount++;
        }
    }

}

static void dialogScreen(string text) {
    //clear screen
    system("cls");

    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << ANSI_COLOR_GREEN << "  ███████  ██████   █████   ██████  ███████     ██ ███    ██ ██  ██ ███████ ██████   ███████ ███████ ███████" << ANSI_COLOR_GREEN << "\n";
    std::cout << ANSI_COLOR_GREEN << "  ██       ██  ██  ██   ██ ██       ██          ██ ████   ██ ██  ██ ██   ██ ██    ██ ██      ██    █ ██     " << ANSI_COLOR_GREEN << "\n";
    std::cout << ANSI_COLOR_GREEN << "  ███████  ██████  ███████ ██       █████       ██ ██ ██  ██ ██  ██ ███████ ██    ██ ████    ███████ ███████" << ANSI_COLOR_GREEN << "\n";
    std::cout << ANSI_COLOR_GREEN << "       ██  ██      ██   ██ ██       ██          ██ ██  ██ ██ ██  ██ ██   ██ ██    ██ ██      ██ ██        ██" << ANSI_COLOR_GREEN << "\n";
    std::cout << ANSI_COLOR_GREEN << "  ███████  ██      ██   ██  ██████  ███████     ██ ██   ████   ██   ██   ██ ██████   ███████ ██   ██ ███████" << ANSI_COLOR_GREEN << "\n";
    std::cout << ANSI_COLOR_GREEN << "                                                                                                            " << ANSI_COLOR_GREEN << "\n";
    std::cout << ANSI_COLOR_GREEN << "                                                                                                            " << ANSI_COLOR_GREEN << "\n";
    std::cout << ANSI_COLOR_GREEN << "                                                                                                            " << ANSI_COLOR_GREEN << "\n";
    std::cout << ANSI_COLOR_RED << text << "                                                                                                     " << ANSI_COLOR_GREEN << "\n";
    if (players.size() > 0) {
        printScoreRanking();
    }
    std::cout << "\n";
    std::cout << "\n";

    //PRESS ANY BUTTON    
    char ret;
    if (gameOver) {
        do {
            ret = _getch();
            if (ret == 'y' || ret == 'Y') {
                //reset the game
                gameOver = false;
                level = 0;
                maxPoints = 0;
                playerRegistration();
                setup();
            }
        } while (ret != 'y' && ret != 'Y' && ret != 'e' && ret != 'E');
    }
    else {
        ret = _getch();
    }
}


static void draw() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = { 0, 0 };
    SetConsoleCursorPosition(hConsole, cursorPosition);

    //print movement
    cout << ANSI_COLOR_CYAN;
    cout << "A MOVE LEFT |";
    cout << "D MOVE RIGHT|";
    cout << "SPACE TO SHOOT | DO NOT DIE!!!" << endl << endl;    

    cout << "|TOP SCORE | " << topScore << endl;

    //print level and points
    printSizeTable(currentPlayer.name.length() + 12);
    cout << endl;
    cout << "  FIGHTER   | " << currentPlayer.name << endl;
    cout << "  LEVEL     | " << level << endl;    
    cout << "  SCORE     | " << currentPlayer.points << endl;
    cout << "  LIFE      | " << currentPlayer.lifes << endl;    
    printSizeTable(currentPlayer.name.length() + 12);
    cout << endl;
    

    // Clear screen buffer
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screen[i][j] = ' ';
        }        
    }        

    // Draw player
    screen[currentPlayer.y][currentPlayer.x] = currentPlayer.SpaceshipType.printingType;

    // Draw bullets
    for (auto& b : bullets) {
        screen[b.y][b.x] = '|';        
    }

    // Draw enemy bullets
    for (auto& eb : enemyBullets) {        
        screen[eb.y][eb.x] = '*';        
    }
    
    // Draw enemies
    for (auto& e : enemies) {
        if (e.alive) {
            screen[e.y][e.x] = 'W';
        }        
    }
    
    // Print screen
    //enemies
    for (int i = 0; i < level + 2; i++) {
        for (int j = 0; j < width; j++) {
            cout << ANSI_COLOR_GREEN << screen[i][j];
        }        
        cout << endl;
    }

    //bullets and player
    for (int i = level + 3; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << ANSI_COLOR_RESET << screen[i][j];
        }
        cout << endl;
    }
}

static void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (currentPlayer.x > 0) currentPlayer.x = currentPlayer.x - 1; break;
            case 'd': if (currentPlayer.x < width - 1) currentPlayer.x = currentPlayer.x + 1; break;
            case ' ': 
                bullets.push_back({ currentPlayer.x, height - 3, true });             
                break;
            case 'q': gameOver = true; break;     
        }
    }
}

static void update() {    

    // Move bullets
    int x = 0;
    for (auto& b : bullets) {
        b.y--;        
        for (auto& e : enemies) {
            if (e.alive && b.active && b.x == e.x && b.y == e.y) {
                e.alive = false;
                b.active = false;
                currentPlayer.points = currentPlayer.points + 50;
                maxPoints = maxPoints + 50;
                //every time an enemy is defeated 1*level enemy bullets is shotted
                enemiesCount = enemiesCount - 1;
                enemyBullets.push_back({ e.x, 2, true });
                enemyBullets.push_back({ e.x / 2 , 2, true });
            }
        }
        if (b.y < 0) {            
            bullets.erase(bullets.begin() + x);
            x--;            
        };
        x++;
    }    

    x = 0;
    for (auto& eb : enemyBullets) {
        if (eb.active) {
            eb.y++;
            if (currentPlayer.x == eb.x && eb.y == currentPlayer.y) {
                currentPlayer.lifes = currentPlayer.lifes - 1;
                currentPlayer.points = currentPlayer.points - 100;
            }            
            if (eb.y > height - 2) {
                enemyBullets.erase(enemyBullets.begin() + x);
                x--;               
            };
            x++;
        }
    }    
    
    //Life up each 1000 points
    if (maxPoints % 1000 == 0 && maxPoints > 0) {
        currentPlayer.lifes = currentPlayer.lifes + 1;
        maxPoints = maxPoints + 50;
    };

    //Game over if life gets zero
    if (currentPlayer.lifes <= 0) {
        players[players.size() - 1] = currentPlayer;
        gameOver = true;
    };

    
    if (enemiesCount == 0) {
        level = level + 1; 
        setup();        
    }
}
//END - Game controller

//main gaming function
int main() {

    dialogScreen("PRESS ANY BUTTON TO START");

    //Spaceships types generator
    genSpaceships();

    //create player
    playerRegistration();

    setup();        
    
    while (!gameOver) {
        draw();
        input();
        update();   
        Sleep(20);

        if (gameOver) {            
            Sleep(1000);
            dialogScreen("GAME OVER!!! THANKS FOR PLAYING!!! \n Press E to EXIT or Y to PLAY AGAIN...");                       
        }

    }    

    return 0;
}
