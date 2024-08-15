#pragma once
#include <iostream> 
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#define print printf
#define input scanf
#define clear system("cls")
#define pause system("pause")
using namespace std;
struct Random {
    typedef long long int LL;
    typedef unsigned long long int ULL;
    ULL Seed;
    const ULL Mod = 70185078087379;
    ULL GetTime(void) { return chrono::high_resolution_clock::now().time_since_epoch().count();}
    Random() { Sleep(1); Seed = GetTime(); Seed = Next(Seed); Seed = Next(Seed);}
    Random(ULL S) { Seed = Next(S);}
    ULL GetSeed() { return Seed; }
    ULL Next(ULL &T) {
        for(int i = 0; i < 20; i++) {
            T = (T * GetTime() + 11) % Mod;
            T = (T * 114514 + 11) % Mod;
            T = (T * 131415 + 11) % Mod;
            T = (T * 123456 + 11) % Mod;
            T = (T * GetTime() + 11) % Mod;
        }
        T = (T * GetTime()) % Mod;
        return T;
    }
    int IntRandom(int l, int r) {
        return (Next(Seed)) % (r - l + 1) + l;
    }
    double DoubleRandom(double l, double r) {
        return (Next(Seed) / (double)Mod) * (r - l) + l;
    }
    float FloatRandom(float l, float r) {
        return (Next(Seed) / (float)Mod) * (r - l) + l;
    }
    bool BoolRandom() {
        return Next(Seed) % 2 == 0;
    }
    LL LLRandom(LL l, LL r) {
        return Next(Seed) % (r - l + 1) + l;
    }
    ULL ULLRandom(ULL l, ULL r) {
        return Next(Seed) % (r - l + 1) + l;
    }
};
class PlayBoard {
    private:
        int Size;
        vector<vector<int> > Board;
        void UpMove(void) {
            for(int i = 1; i <= Size; i++) {
                for(int j = 1; j <= Size; j++) {
                    for(int k = i; k >= 1; k--) {
                        if(Board[k][j] == 0) {
                            Board[k][j] = Board[k - 1][j];
                            Board[k - 1][j] = 0;
                        }
                        else if(Board[k][j] == Board[k - 1][j]) {
                            Board[k][j] *= 2;
                            Board[k - 1][j] = 0;
                        }
                    }
                }
            }
        }
        void LeftMove(void) {
            for(int i = 1; i <= Size; i++) {
                for(int j = 1; j <= Size; j++) {
                    for(int k = j; k >= 1; k--) {
                        if(Board[i][k] == 0) {
                            Board[i][k] = Board[i][k - 1];
                            Board[i][k - 1] = 0;
                        }
                        else if(Board[i][k] == Board[i][k - 1]) {
                            Board[i][k] *= 2;
                            Board[i][k - 1] = 0;
                        }
                    }
                }
            }
        }
        void RightMove(void) {
            for(int i = 1; i <= Size; i++) {
                for(int j = Size; j >= 1; j--) {
                    for(int k = j; k <= Size; k++) {
                        if(Board[i][k] == 0) {
                            Board[i][k] = Board[i][k + 1];
                            Board[i][k + 1] = 0;
                        }
                        else if(Board[i][k] == Board[i][k + 1]) {
                            Board[i][k] *= 2;
                            Board[i][k + 1] = 0;
                        }
                    }
                }
            }
        }
        void DownMove(void) {
            for(int i = Size; i >= 1; i--) {
                for(int j = 1; j <= Size; j++) {
                    for(int k = i; k <= Size; k++) {
                        if(Board[k][j] == 0) {
                            Board[k][j] = Board[k + 1][j];
                            Board[k + 1][j] = 0;
                        }
                        else if(Board[k][j] == Board[k + 1][j]) {
                            Board[k][j] *= 2;
                            Board[k + 1][j] = 0;
                        }
                    }
                }
            }
        }
        void AddingNumder(void) {
            Random Rd;
            while(1) {
                int x = Rd.IntRandom(1, Size);
                int y = Rd.IntRandom(1, Size);
                if(Board[x][y] == 0) {
                    Board[x][y] = Rd.IntRandom(1, 2) == 1 ? 2 : 4;
                    break;
                }
            }
        }
    public:
        PlayBoard(int size) {
            Size = size;
            Board.resize(Size + 5, vector<int>(Size + 5, 0));
        }
        PlayBoard() {
            Size = 4;
            Board.resize(Size + 5, vector<int>(Size + 5, 0));
        }
        void Print() {
            for (int i = 1; i <= Size; ++i) {
                printf("*------");
            }
            printf("*\n");

            for (int i = 1; i <= Size; ++i) {
                printf("|");
                for (int j = 1; j <= Size; ++j) {
                    printf("%5d |", Board[i][j]);
                }
                printf("\n");

                for (int k = 1; k <= Size; ++k) {
                    printf("*------");
                }
                printf("*\n");
            }
        }
        vector<vector<int> > GetBoard() {
            return Board;
        }
        void Move(int direction) {
            // w: up, a: left, d: right, s: down
            // up/left/right/down arrow keys
            if(direction == 'w') {
                DownMove();
            }
            else if(direction == 'a') {
                RightMove();
            }
            else if(direction == 'd') {
                LeftMove();
            }
            else if(direction == 's') {
                UpMove();
            }
            else if(direction == 72) {
                DownMove();
            }
            else if(direction == 75) {
                RightMove();
            }
            else if(direction == 77) {
                LeftMove();
            }
            else if(direction == 80) {
                RightMove();
            }
            else {
                return;
            }
            AddingNumder();
            return;
        }
        bool IsWin(void) {
            for(int i = 1; i <= Size; i++) {
                for(int j = 1; j <= Size; j++) {
                    if(Board[i][j] == 2048) {
                        return true;
                    }
                }
            }
            return false;
        }
        bool IsLose(void) {
            for(int i = 1; i <= Size; i++) {
                for(int j = 1; j <= Size; j++) {
                    if(Board[i][j] == 0) {
                        return false;
                    }
                }
            }
            return true;
        }
};







/*
#include <iostream>
#include <vector>

void printBoard(const std::vector<std::vector<int>>& board) {
    for (const auto& row : board) {
        cout << "*----";
        for (int i = 1; i < size; i++) {
            std::cout << "*----";
        }
        std::cout << "*" << std::endl;

        std::cout << "|";
        for (int cell : row) {
            std::cout << " " << cell << " |";
        }
        std::cout << std::endl;
    }

    std::cout << "*----";
    for (size_t i = 1; i < board[0].size(); ++i) {
        std::cout << "*----";
    }
    std::cout << "*" << std::endl;
}

int main() {
    int n, m;
    std::cout << "Enter the number of rows (n): ";
    std::cin >> n;
    std::cout << "Enter the number of columns (m): ";
    std::cin >> m;

    std::vector<std::vector<int>> board(n, std::vector<int>(m, 0));

    printBoard(board);

    return 0;
}

*/