#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include "ballsortpuzzle.h"
#include <stdbool.h>

void string_suffle(char string[]){
    int len = strlen(string);
    char c;
    for(int i = 0; i < len; i++){
        int tmp = rand() % len;
        c = string[i];
        string[i] = string[tmp]; 
        string[tmp] = c; 
    }
}

void generator(const int rows, const int columns, char field[rows][columns]){

    int emptyCol1 = rand() % columns;
    int emptyCol2 = rand() % columns;
    while(emptyCol1 == emptyCol2){
        emptyCol2 = rand() % columns;
    }

    char symbols[12] = {
        '+','*' ,'@','^','&','$','#','%','-','=','!','?' 
    };

    char string[rows * (columns - 2) + 1];

    int strIndex = 0;
    for(int i = 0; i < columns - 2; i++){
        for(int j = 0; j < rows; j++){
            string[strIndex] = symbols[i];
            strIndex++;
        } 

    }
    
    string[strIndex] = '\0';
    string_suffle(string);
    printf("%s\n", string);

    strIndex = 0;
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            if(i == emptyCol1 || i == emptyCol2){
                field[j][i] = ' ';
                continue;
            }
            field[j][i] = string[strIndex];
            strIndex++;
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y){
    char tmpX;
    if(field[rows - 1][x - 1] == ' ' || field[0][y - 1] != ' '){
        printf("Cannot use this columns\n");
        return;
    }

    int rememberRowIndex;
     for (int i = 0; i < rows; i++) {
        if (field[i][x - 1] != ' ') {
            tmpX = field[i][x - 1];
            rememberRowIndex = i;
            break;
        }
    }

    if (field[rows - 1][y - 1] == ' ') {
        field[rows - 1][y - 1] = tmpX;
        field[rememberRowIndex][x - 1] = ' ';
    } else {
        for (int i = rows - 2; i >= 0; i--) {
            if (field[i][y - 1] == ' ' && field[i + 1][y - 1] == tmpX) {
                field[i][y - 1] = tmpX;
                field[rememberRowIndex][x - 1] = ' ';
                break;
            } else if (field[i][y - 1] == ' ' && field[i + 1][y - 1] != tmpX) {
                printf("Symbols not equal\n");
                break;
            }
        }
    }
}

bool check(const int rows, const int columns, char field[rows][columns]) {
    for (int i = 0; i < columns; i++) {
        bool isEmpty = true;
        for (int j = 0; j < rows; j++) {
            if (field[j][i] != ' ') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) continue; 

        char symbol = field[0][i];
        if (symbol == ' ') return false;

        for (int j = 0; j < rows; j++) {
            if (field[j][i] != symbol) {
                return false;
            }
        }
    }

    return true;
}

void game_field(const int rows, const int columns, char field[rows][columns]) {
    for (int row = 0; row < rows; row++) {
        printf("%d ", row + 1); 

        for (int col = 0; col < columns; col++) {
            printf("| %c ", field[row][col]);
        }
        printf("|\n");
    }

    printf("  ");
    for (int col = 0; col < columns; col++) {
        printf("----");
    }
    printf("-\n");

    printf("  ");
    for (int col = 0; col < columns; col++) {
        printf(" %d  ", col + 1);
    }
    printf("\n");
}

void ball_sort_puzzle() {
    const int rows = 4;
    const int cols = 6;
    char field[rows][cols];
    int x, y;

    srand(time(NULL));
    generator(rows, cols, field);

    while (!check(rows, cols, field)) {
        game_field(rows, cols, field);

        printf("Enter what: ");
        if (scanf("%d", &x) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        printf("Enter where: ");
        if (scanf("%d", &y) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (x == y || x < 1 || x > cols || y < 1 || y > cols) {
            printf("Wrong column numbers! Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        down_possible(rows, cols, field, x, y);
    }

    game_field(rows, cols, field);
    printf("Congratulations! You win!\n");
}