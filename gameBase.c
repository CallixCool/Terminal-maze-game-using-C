#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

int checkMovement(int maze[][201], int x, int y, int size, int specifier, int lookingFor) {
    int moves = 0;
    // printf("%d\n", size);

    // specifier = 0
    if (specifier == 0) {
        if (maze[x+1][y] == lookingFor && x < size-1) moves++; 
        if (maze[x-1][y] == lookingFor && x > 0)      moves++; 
        if (maze[x][y+1] == lookingFor && y < size-1) moves++; 
        if (maze[x][y-1] == lookingFor && y > 0)      moves++; 
    }
    else {
        if (maze[x+1][y] == lookingFor && specifier == 2 && x < size-1) moves++; 
        if (maze[x-1][y] == lookingFor && specifier == 4 && x > 0)      moves++; 
        if (maze[x][y+1] == lookingFor && specifier == 1 && y < size-1) moves++; 
        if (maze[x][y-1] == lookingFor && specifier == 3 && y > 0)      moves++; 
    }
    
    //1 up
    //2 right
    //3 down
    //4 left
    
    return moves;
}

int generateMaze(char maze[][201], int size) {
    int mapSize = 2 * size + 1;
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            maze[i][j] = '#';
            // if (i == 0 || i == mapSize-1 || j == 0 || j == mapSize-1 || (i % 2 == 0 && j % 2 == 0)) {
            //     maze[i][j] = '#';
            // } else {
            //     maze[i][j] = '.';
            // }
        }
    }

    //  0 = empty
    //  1 = checked
    // -1 = back tracked
    int mazeModel[201][201];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mazeModel[i][j] = 0;
        }
    }

    // choose starting point ======================================================
    int moleX = rand() % size;
    int moleY = rand() % size;
    mazeModel[moleX][moleY] = 1;
    maze[moleX * 2 + 1][moleY * 2 + 1] = ' ';

    // creating -===================================================================
    int complete = 0;
    int backTracking = 0;
    int step = 2;
    while (!complete) {
        if (!backTracking) {
            int totalMovements = checkMovement(mazeModel, moleX, moleY, size, 0, 0);
            if (totalMovements > 0) {
                // decide where to go and just go i guess =====================================
                int turns = rand() % totalMovements + 1;
                int count = 0;
                for (int i = 1; i <= 4; i++) {
                    if (checkMovement(mazeModel, moleX, moleY, size, i, 0) > 0) count++;
                    if (count == turns) {
                        if (i == 1) {
                            moleY++; 
                            maze[moleX * 2 + 1][moleY * 2] = ' ';
                        }
                        if (i == 2) {
                            moleX++; 
                            maze[moleX * 2][moleY * 2 + 1] = ' ';
                        }
                        if (i == 3) {
                            moleY--; 
                            maze[moleX * 2 + 1][moleY * 2 + 2] = ' ';
                        }
                        if (i == 4) {
                            moleX--; 
                            maze[moleX * 2 + 2][moleY * 2 + 1] = ' ';
                        }
                        maze[moleX * 2 + 1][moleY * 2 + 1] = ' ';
                        mazeModel[moleX][moleY] = step;
                        step++;
                        break;
                    }
                }
            } 
            else {
                backTracking = 1;
                // step we will be looking for
                step -= 2;
                // complete = 1;
                // maze[moleX * 2 + 1][moleY * 2 + 1] = 'b';
            }
        } 

        else {
            //backtracking========================================================================
            
            int totalMovements = checkMovement(mazeModel, moleX, moleY, size, 0, 0);
            if (totalMovements > 0) {
                step += 2;
                backTracking = 0;
            } 
            else {
                mazeModel[moleX][moleY] = -1;
                if      (checkMovement(mazeModel, moleX, moleY, size, 1, step) > 0) {
                    moleY++;
                }
                else if (checkMovement(mazeModel, moleX, moleY, size, 2, step) > 0) {
                    moleX++;    
                }
                else if (checkMovement(mazeModel, moleX, moleY, size, 3, step) > 0) {
                    moleY--;
                }
                else if (checkMovement(mazeModel, moleX, moleY, size, 4, step) > 0) {
                    moleX--;
                }
                step--;
            }
        }
 
        int numOfBacktracked = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (mazeModel[i][j] == -1) numOfBacktracked++;
            }
        }
        if (numOfBacktracked == size*size) complete = 1;
    }

    return 0;
}

int clearScreen() {
    printf("\033[H\033[2J");
    return 0;
}

int mainMenu(int s) {
    clearScreen();
    printf("\n /$$      /$$                                     /$$      /$$                       /$$                        ");
    printf("\n| $$$    /$$$                                    | $$$    /$$$                      | $$                        ");
    printf("\n| $$$$  /$$$$  /$$$$$$  /$$$$$$$$  /$$$$$$       | $$$$  /$$$$  /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$ ");
    printf("\n| $$ $$/$$ $$ |____  $$|____ /$$/ /$$__  $$      | $$ $$/$$ $$ |____  $$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$");
    printf("\n| $$  $$$| $$  /$$$$$$$   /$$$$/ | $$$$$$$$      | $$  $$$| $$  /$$$$$$$|  $$$$$$   | $$    | $$$$$$$$| $$  \\__/");
    printf("\n| $$\\  $ | $$ /$$__  $$  /$$__/  | $$_____/      | $$\\  $ | $$ /$$__  $$ \\____  $$  | $$ /$$| $$_____/| $$      ");
    printf("\n| $$ \\/  | $$|  $$$$$$$ /$$$$$$$$|  $$$$$$$      | $$ \\/  | $$|  $$$$$$$ /$$$$$$$/  |  $$$$/|  $$$$$$$| $$      ");
    printf("\n|__/     |__/ \\_______/|________/ \\_______/      |__/     |__/ \\_______/|_______/    \\___/   \\_______/|__/      ");
    printf("\n                                                                                                                 ");
    printf("\nBy CallixCool                                                                                                                 ");
    printf("\n                                                                                                                 ");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n-Play Game    "); if (s == 1) printf("<<<");
    printf("\n-Information  "); if (s == 2) printf("<<<");
    printf("\n-Quit         "); if (s == 3) printf("<<<");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n [z] Enter [x] Cancel");
    return 0;
}

int gameoverScreen(int s, int hi, int newHi, int count) {
    clearScreen();
    printf("\n==Game Over==");
    printf("\n");
    printf("\nScore = %d", s);
    printf("\n");
    printf("\nHigh Score = %d", hi); if (newHi) printf(" (NEW HIGHSCORE)");
    printf("\n");
    printf("\nReturning to menu in %d", count);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n"); 
    printf("\n"); 
    printf("\n"); 
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}

int instructionPage(int s) {
    clearScreen();
    printf("\n==How to Play==");
    printf("\n");
    printf("\n");
    printf("\n");
    if (s == 1) {
        printf("\nAll you gotta do");
        printf("\nis to navigate the");
        printf("\nGUY \033[1;34m<>\033[0m through the");
        printf("\nmaze and into the ");
        printf("\nfinish line \033[1;32m\u2588\u2588\033[0m");
        printf("\n");
        printf("\n");
        printf("\n     Page 1 / 3  >>>");
    } else if (s == 2) {
        printf("\nThough beware for");
        printf("\nthere is a time ");
        printf("\nlimit and maze shall");
        printf("\nonly grow once solved");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n<<<  Page 2 / 3  >>>");
    } else if (s == 3) {
        printf("\n");
        printf("\nHighscore is saved in");
        printf("\nscore.txt ");
        printf("\n");
        printf("\nok thanks goodluck");
        printf("\n");
        printf("\n");
        printf("\n<<<  Page 3 / 3     [z] to Return");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n [z] Enter [x] Cancel");
    return 0;
}

int loadMaze(char maze[][201], int size, int invert, int hi, int score, float time) {
    clearScreen();
    printf("\n");
    for (int i = 0; i < size*2 + 1; i++) {
            for (int j = 0; j < size*2 + 1; j++) {
                if (!invert) {
                    if (maze[i][j] == '#') printf("\033[1;47;37m\u2588\u2588\033[0m");
                    if (maze[i][j] == ' ') printf("  ");
                    if (maze[i][j] == 'P') printf("\033[1;34m<>\033[0m");
                    if (maze[i][j] == 'G') printf("\033[1;32m\u2588\u2588\033[0m");
                } else {
                    if (maze[i][j] == '#') printf("  ");
                    if (maze[i][j] == ' ') printf("\033[1;47;37m\u2588\u2588\033[0m");
                    if (maze[i][j] == 'P') printf("\033[1;47;34m<>\033[0m");
                    if (maze[i][j] == 'G') printf("\033[1;47;32m\u2588\u2588\033[0m");
                }
                    
            }
            
            for (int j = 0; j < 60 - 2*(size*2 + 1); j++) printf(" ");
            if (i == 2) printf("Highscore      = %d", hi);
            if (i == 3) printf("Score          = %d", score);
            if (i == 4) printf("Level          = %d", size - 6);
            if (i == 5) printf("Remaining time = %d:%05.2f", (int) time / 60, fmod(time, 60));

            printf("\n"); 
        }
    return 0;
}

int gameOptions(int s, float time, int color) {
    clearScreen();
    printf("\n==Game Options==");
    printf("\n");
    printf("\n");
    printf("\n-Time Limit    "); 
    if (s == 1) {
        if (time == 1) printf("  %.0f>>", time);
        else if (time == 5) printf("<<%.0f", time);
        else printf("<<%.0f>>", time);
    }
    else printf("  %.0f", time);
    printf("\n-Invert Colors ");
    if (s == 2) {
        if (color == 0) printf("  White walls>>");
        if (color == 1) printf("<<Black walls");
    }
    else {
        if (color == 0) printf("  White walls");
        if (color == 1) printf("  Black walls");
    }
    printf("\n");
    printf("\n-Play          "); if (s == 3) printf("<<<");
    printf("\n-Back          "); if (s == 4) printf("<<<");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n [z] Enter [x] Cancel");
    
    return 0;
}

int main () {
    system("chcp 65001 > nul");
    srand(time(NULL));
    int ch, running = 1, selection = 1, selection2 = 1, previousSelection = 1, currentMenu = 1, previousMenu = 1, inverted = 0;
    int score = 0, highScore = 0, currentSize = 9, size = 7, playing = 0, onCountdown = 0, countdown = 3, newLevel = 0;
    int playerX, playerY, goalX, goalY, prevX, prevY, prevGoalX, prevGoalY, gameover = 0, newHighscore = 0;
    float timeLimit = 1, previousTimeLimit = 1, previousInverted = 0, timer, screenRefreshTimer = 0, gameoverTime = 5;
    char maze[201][201];
    int direction[2] = {0, 0};
    clock_t last_tick = clock();

    FILE *f = fopen("score.txt", "a+");
    fscanf(f, "%d", &highScore);
    fclose(f);

    mainMenu(1);
    while (running) {
        clock_t current_tick = clock();
        double delta_time_seconds = (double)(current_tick - last_tick) / CLOCKS_PER_SEC;

        if (_kbhit()) { 
            ch = _getch(); 
            if (ch == 27) {
                break; // Exit loop if 'q' is pressed
            }
            if (ch == 0 || ch == 224) { // Special key code
                switch (_getch()) { // Read the actual key code
                    case 72: direction[1] = 1; break;
                    case 80: direction[1] = -1; break;
                    case 77: direction[0] = 1; break;
                    case 75: direction[0] = -1; break;
                }
            }
            if (ch == 'g') {
                playing = 1;
                currentMenu = 4;
                onCountdown = 1;
                countdown = 0;
                selection = 1;
                screenRefreshTimer = 0;
                timer = timeLimit * 60;
                clearScreen();
                printf("\n%d", countdown);
            }
        }
        
        if (currentMenu == 1) { // main menu ===========================================================================
            selection -= direction[1];
            if (previousMenu != currentMenu) mainMenu(selection);
            previousMenu = currentMenu;
            if (selection < 1) selection = 1;
            if (selection > 3) selection = 3;
            if (ch == 'x') selection = 3;
            if (selection != previousSelection) mainMenu(selection);
            if (selection == 1 && ch == 'z') {
                currentMenu = 3;
                selection = 1;
            }
            if (selection == 2 && ch == 'z') {
                currentMenu = 2;
                selection = 1;
            }
            if (selection == 3 && ch == 'z') running = 0;
            previousSelection = selection;
        }
        if (currentMenu == 2) { // instructions menu ===========================================================================
            selection += direction[0];
            if (previousMenu != currentMenu) instructionPage(selection);
            previousMenu = currentMenu;
            if (selection < 1) selection = 1;
            if (selection > 3) selection = 3;
            if (selection != previousSelection) instructionPage(selection);
            if ((selection == 3 && ch == 'z') || ch == 'x') {
                currentMenu = 1;
                selection = 1;
            }
            previousSelection = selection;
        }
        if (currentMenu == 3) { // Game Options menu ===========================================================================
            selection2 += direction[0];
            selection -= direction[1];
            if (previousMenu != currentMenu) gameOptions(selection, timeLimit, inverted);
            previousMenu = currentMenu;
            if (selection < 1) selection = 1;
            if (selection > 4) selection = 4;
            if (selection != previousSelection) gameOptions(selection, timeLimit, inverted);
            previousTimeLimit = timeLimit;
            if (selection == 1) {
                timeLimit += direction[0];
                if (timeLimit < 1) timeLimit = 1;
                if (timeLimit > 4) timeLimit = 5;
            }
            if (timeLimit != previousTimeLimit) gameOptions(selection, timeLimit, inverted);
            previousInverted = inverted;
            if (selection == 2) {
                inverted += direction[0];
                if (inverted < 0) inverted = 0;
                if (inverted > 1) inverted = 1;
            }
            if (inverted != previousInverted) gameOptions(selection, timeLimit, inverted);
            if (selection == 3 && ch == 'z') {
                playing = 1;
                currentMenu = 4;
                onCountdown = 1;
                countdown = 3;
                selection = 1;
                screenRefreshTimer = 0;
                timer = timeLimit * 60;
                gameover = 0;
                score = 0;
                size = 7;
                clearScreen();
                printf("\n%d", countdown);
            }
            if ((selection == 4 && ch == 'z') || ch == 'x') {
                currentMenu = 1;
                selection = 1;
            }
            previousSelection = selection;
        }

        if (playing) { // Game ================================================================================================
            if (onCountdown) {
                screenRefreshTimer += delta_time_seconds;
                if (screenRefreshTimer > 1) {
                    screenRefreshTimer = 0;
                    countdown--;
                    clearScreen();
                    printf("\n%d", countdown);
                    
                }
                if (countdown <= 0) {
                    onCountdown = 0;
                    newLevel = 1;
                    screenRefreshTimer = 1;
                }
            } 
            else if (gameover) { // Gameover screen ====================================================================================
                if (gameoverTime <= 0) {
                    currentMenu = 1;
                    selection = 1;
                    playing = 0;
                    newHighscore = 0;
                    mainMenu(1);
                }
                if (screenRefreshTimer <= 0) {
                    gameoverScreen(score, highScore, newHighscore, countdown--);
                    screenRefreshTimer = 1;
                }
                screenRefreshTimer -= delta_time_seconds;
                gameoverTime -= delta_time_seconds;
            } 
            else {
                if (newLevel) { // New Level ======================================================================================
                    if (size > 13) size = 13;
                    generateMaze(maze, size);
                    int playerX = (rand() % size) * 2 + 1;
                    int playerY = (rand() % size) * 2 + 1;
                    int goalX = (rand() % size) * 2 + 1;
                    int goalY = (rand() % size) * 2 + 1;
                    while (playerX == goalX && playerY == goalY) {
                        int goalX = (rand() % size) * 2 + 1;
                        int goalY = (rand() % size) * 2 + 1;
                    }

                    maze[playerX][playerY] = 'P';
                    maze[goalX][goalY] = 'G';
                    // printf("%d %d", playerX, playerY);
                    // printf("%d %d", goalX, goalY);
                    prevX = playerX;
                    prevY = playerY;
                    prevGoalX = goalX;
                    prevGoalY = goalY;
                    newLevel = 0;
                    loadMaze(maze, size, inverted, highScore, score, timer);

                }
                else { // Gameplay ==============================================================================================
                    if (screenRefreshTimer < 0) {
                        loadMaze(maze, size, inverted, highScore, score, timer);
                        // printf("%d %d", playerX, playerY);
                        // printf("%d %d", goalX, goalY);
                        screenRefreshTimer = 1;
                    }

                    playerX -= direction[1];
                    playerY += direction[0];
                    
                    if (maze[playerX][playerY] == '#') {
                        playerX = prevX;
                        playerY = prevY;
                    }

                    if (playerX != prevX || playerY != prevY) {
                        maze[playerX][playerY] = 'P';
                        maze[prevX][prevY] = ' ';

                        loadMaze(maze, size, inverted, highScore, score, timer);
                        screenRefreshTimer = 1;
                    }

                    if (playerX == goalX && playerY == goalY) {
                        newLevel++; 
                        size++;
                        score++;
                    }

                    if (timer <= 0 || ch == 'q') {
                        gameover++;
                        gameoverTime = 5;
                        gameoverScreen(score, highScore, newHighscore, 5);
                        screenRefreshTimer = 1;
                        countdown = 5;
                        FILE *f = fopen("score.txt", "w");
                        fprintf(f, "%d", highScore);
                        fclose(f);
                        timer = 0;
                    }


                    prevX = playerX;
                    prevY = playerY;
 
                    timer -= delta_time_seconds;
                    screenRefreshTimer -= delta_time_seconds;
                }
                playerX = prevX;
                playerY = prevY;
                goalX = prevGoalX;
                goalY = prevGoalY;
            }
        }
        if (score > highScore) {
            highScore = score;
            newHighscore = 1;
        }

        
        ch = '=';
        direction[0] = 0; direction[1] = 0; 
        last_tick = current_tick;
    }

    return 0;
}