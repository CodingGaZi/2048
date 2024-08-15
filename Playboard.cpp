#include "Playboard.h"
#include <iostream>
#include <windows.h>
using namespace std;
inline int Read() {
    int num = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) num = (num << 1) + (num << 3) + ch - '0';
    return num * f;
}
void SetColor(int FroeColor, int BlackColor) {
    /*  0 = 黑色   1 = 蓝色
        2 = 绿色   3 = 湖蓝色
        4 = 红色   5 = 紫色
        6 = 黄色   7 = 白色
        8 = 灰色   9 = 淡蓝色
        10 = 淡绿色  11 = 淡浅绿
        12 = 淡红色  13 = 淡紫色
        14 = 淡黄色  15 = 亮白色
    */
    SetConsoleTextAttribute(
    GetStdHandle(STD_OUTPUT_HANDLE),
    FroeColor + BlackColor * 0x10);
}
template<typename T>
void ColorOut(T t, int FroeColor, int BackColor = 0) {
    SetColor(FroeColor, BackColor);
    cout << t;
    SetColor(15, 0);
}
void FirstGraph(void) {
    char ch[][1000] = {
        "                          ",
        "   ***  ***     *** ***   ",
        "   *    * *       *  *    ",
        "   * ** ***      *   *    ",
        "   * *  * *     *    *    ",
        "   ***  * *     *** ***   ",
        "                          "
        //  "       Ga Zi Studio       "
    };
    for (int i = 0; i < 7; i++) {
        int len = strlen(ch[i]);
        for (int j = 0; j < len; j++) {
            if (ch[i][j] != '*') ColorOut(" ", 0, 1);
            else ColorOut(" ", 0, 3);
        }
        cout << endl;
    }
    ColorOut("       ", 0, 1);
    ColorOut("Ga", 3, 4);
    ColorOut(" ", 0, 4);
    ColorOut("Zi", 3, 4);
    ColorOut(" ", 0, 4);
    ColorOut("Studio", 3, 4);
    ColorOut("       ", 0, 1);
    cout << endl;
    cout << "2048 Game\n";
    Sleep(2000);
    system("CLS");
}
int Menu(void) {
    ColorOut("  2048 Game\n", 3, 0);
    ColorOut("1. 4 * 4 Game\n", 3, 0);
    ColorOut("2. 6 * 6 Game\n", 3, 0);
    ColorOut("3. 8 * 8 Game\n", 3, 0);
    ColorOut("4. Exit\n", 3, 0);
    int choice = Read();
    while (choice < 1 || choice > 4) {
        cout << "Invalid choice, please try again.\n";
        choice = Read();
    }
    if(choice == 4) {
        ColorOut("Thanks for playing!\n", 2, 0);
        Sleep(2000);
        system("CLS");
        exit(0);
    }
    return choice;
}
void Game(int Get) {
    system("CLS");
    int N;
    switch(Get) {
        case 1:
            N = 4;
            break;
        case 2:
            N = 6;
            break;
        case 3:
            N = 8;
            break;
        default:
            break;
    }
    PlayBoard Board(N);
    while(true) {
        Board.Print();
        if(Board.IsWin()) {
            ColorOut("Congratulations! You win!\n", 2, 0);
            ColorOut("Press ANY keys to Meum. \n", 4, 0);
	        getch();
            system("CLS");
            return;
        }
        else if(Board.IsLose()) {
            ColorOut("Sorry, you lose!\n", 4, 0);
            ColorOut("Press ANY keys to Meum. \n", 4, 0);
	        getch();
            system("CLS");
            return;
        }
        else {
            ColorOut("Press W, A, S, D to move, Q to quit.\n", 4, 0);
            ColorOut("Or press Up/Down/Left/Right to move.\n", 4, 0);
            ColorOut("Press E to Exit.\n", 4, 0);
            char ch = getch();
            if(ch == 'q' || ch == 'Q' || ch == 'E' || ch == 'e') {
                ColorOut("Thanks for playing!\n", 2, 0);
                Sleep(2000);
                system("CLS");
                return;
            }
            Board.Move(ch);
            system("CLS");
        }
    }
}
int main() {
    FirstGraph();
    while(true) {
        int choice = Menu();
        Game(choice);
    }
    return 0;
}