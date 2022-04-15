#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <iomanip>

using std::vector;

void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

int main() {

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    vector<vector<int>> snowflakes;
    for (int i = 0; i < 60; i++) { // the console has a max of 54 rows (in full screen)
        vector<int> q;
        snowflakes.push_back(q);
    }

    vector<int> ground;
    vector<int> falls;
    for (int i = 0; i < 220; i++) { // the console has a max of 211 cols
        ground.push_back(2);
        falls.push_back(0);
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 31);
    
    while (1) {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        int randomPosSnowflake = rand() % (columns - 2) + 1;

        snowflakes[0].push_back(randomPosSnowflake);

        for (int i = 0; i < rows - 1; i++) {
            if (snowflakes[i].empty()) {
                std::cout << std::endl;
            }
            else {
                sort(snowflakes[i].begin(), snowflakes[i].end());
                auto iterator = find_if(snowflakes[i].begin(), snowflakes[i].end(), [columns](int val) {return val > columns; });
                if (iterator != snowflakes[i].end()) {
                    snowflakes[i].erase(iterator, snowflakes[i].end());
                }
                if (snowflakes[i].empty()) {
                    std::cout << std::endl;
                    continue;
                }

                std::cout << std::setw(snowflakes[i][0]) << "*";
                int j;
                for (j = 1; j < snowflakes[i].size(); j++) {
                    std::cout << std::setw(snowflakes[i][j] - snowflakes[i][j - 1]) << "*";
                }
                std::cout << std::setw(columns - snowflakes[i][j - 1]) << " " << std::endl;
            }
        }

        snowflakes[rows - 1].clear();

        for (int i = rows - 2; i >= 0; i--) {
            if (snowflakes[i].empty())
                continue;
            else {
                for (int value : snowflakes[i]) {
                    int pos = rand() % 3;
                    if (pos == 0) {
                        snowflakes[i + 1].push_back(value - 1);
                    }
                    else if(pos == 1) {
                        snowflakes[i + 1].push_back(value);
                    }
                    else {
                        snowflakes[i + 1].push_back(value + 1);
                    }
                }
                snowflakes[i].clear();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        clearscreen();
    }
    

    return 0;
}