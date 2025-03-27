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

*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

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

//gaming components
struct Bullet {
    int x, y;
    bool active;
};

struct Enemy {
    int x, y;
    bool alive;    
};

struct Player {    
    int lifes = 3;
    int points = 0;
    int x = width / 2;
    int y = height - 2;
};

struct EnemyBullet {
    int x, y;
    bool active;
};


//gaming components variables
vector<Bullet> bullets;
vector<EnemyBullet> enemyBullets;
vector<Enemy> enemies;
Player currentPlayer;

//gaming controller variables
bool gameOver = false;
int level = 0;
int maxPoints = 0;
int enemiesCount = 0;

//END - GLOBAL VARIABLES

static void dialogScreen(string text) {
    //clear screen
    system("cls");

    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << ANSI_COLOR_GREEN << "  ███████  ██████   █████   ██████  ███████     ██ ███    ██ ██  ██ ███████ ██████   ███████ ███████ ███████"<< ANSI_COLOR_GREEN  << "\n";
    std::cout << ANSI_COLOR_GREEN << "  ██       ██  ██  ██   ██ ██       ██          ██ ████   ██ ██  ██ ██   ██ ██    ██ ██      ██    █ ██     "<< ANSI_COLOR_GREEN  << "\n";
    std::cout << ANSI_COLOR_GREEN << "  ███████  ██████  ███████ ██       █████       ██ ██ ██  ██ ██  ██ ███████ ██    ██ ████    ███████ ███████"<< ANSI_COLOR_GREEN  << "\n";
    std::cout << ANSI_COLOR_GREEN << "       ██  ██      ██   ██ ██       ██          ██ ██  ██ ██ ██  ██ ██   ██ ██    ██ ██      ██ ██        ██"<< ANSI_COLOR_GREEN  << "\n";
    std::cout << ANSI_COLOR_GREEN << "  ███████  ██      ██   ██  ██████  ███████     ██ ██   ████   ██   ██   ██ ██████   ███████ ██   ██ ███████"<< ANSI_COLOR_GREEN  << "\n";
    std::cout << ANSI_COLOR_GREEN << "                                                                                                            "<< ANSI_COLOR_GREEN  << "\n";
    std::cout << ANSI_COLOR_GREEN << "                                                                                                            "<< ANSI_COLOR_GREEN  << "\n";
    std::cout << ANSI_COLOR_GREEN << "                                                                                                            "<< ANSI_COLOR_GREEN  << "\n";
    std::cout << ANSI_COLOR_RED << text <<"                                                                                                     "<< ANSI_COLOR_GREEN << "\n";
    if (currentPlayer.points > 0) {
        std::cout << "SCORE:" << currentPlayer.points << "\n";
    }    
    std::cout << "\n";
    std::cout << "\n";
 
    //PRESS ANY BUTTON
    char ret = _getch();
}

static void setup() {
    //clear screend and variables
    system("cls");
    bullets.clear();
    enemyBullets.clear();
    enemies.clear();
    enemiesCount = 0;

    // Create enemies according level
    for (int x = 2; x < width - 2; x += 4) {
        for (int y = 2; y < level + 2; y++) {
            enemies.push_back({ x, y, true });
            //created to optimize the screen update
            enemiesCount++;
        }
    }   

}

static void draw() {
    system("cls");

    //print movement
    cout << ANSI_COLOR_CYAN << "a <- MOVE LEFT" << endl;
    cout << "b -> MOMVE RIGHT" << endl;
    cout << "SPACE to shoot " << endl << endl;

    //print level and points
    cout << "LEVEL " << level << endl;
    cout << "SCORE - " << currentPlayer.points << endl;
    cout << "LIFE  - " << currentPlayer.lifes << endl;
    

    // Clear screen buffer
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screen[i][j] = ' ';
        }        
    }        

    // Draw player
    screen[currentPlayer.y][currentPlayer.x] = 'T';

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
        if (b.y < 0) {            
            bullets.erase(bullets.begin() + x);
            x--;
            if (x == 0) {
                bullets.clear();
            }
        };
        x++;
     }

    x = 0;
    for (auto& eb : enemyBullets) {
        if (eb.active) {
            eb.y++;
            if (eb.y > height - 2) {
                enemyBullets.erase(enemyBullets.begin() + x);
                x--;
                if (x == 0) {
                    enemyBullets.clear();
                }
            };
            x++;
        }
    }

    // Check bullet-enemy collision
    for (auto& b : bullets) {
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
    }

    // Check enemy bullet - player collision
    for (auto& eb : enemyBullets) {
        
            if (eb.active && currentPlayer.x == eb.x && eb.y == currentPlayer.y) {
                currentPlayer.lifes = currentPlayer.lifes - 1;
                currentPlayer.points = currentPlayer.points - 100;                
            }        
    }

    //Life up each 1000 points
    if (maxPoints % 1000 == 0 && maxPoints > 0) {
        currentPlayer.lifes = currentPlayer.lifes + 1;
        maxPoints = maxPoints + 50;
    };

    //Game over if life gets zero
    if (currentPlayer.lifes <= 0) {
        gameOver = true;
    };

    
    if (enemiesCount == 0) {
        level = level + 1; 
        setup();        
    }
}

//main gaming function
int main() {

    setup();    

    dialogScreen("LEVEL 1 - PRESS ANY BUTTON TO START");
    
    while (!gameOver) {
        draw();
        input();
        update();        
    }
    maxPoints = currentPlayer.points;
    dialogScreen("GAME OVER!!! THANKS FOR PLAYING!!!");    
    return 0;
}
