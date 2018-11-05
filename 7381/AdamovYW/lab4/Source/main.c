// По перечислению узлов дерева в порядке КЛП и ЛКП:
// а) восстановить дерево и вывести его изображение.
// б) перечислить узлы дерева в порядке ЛПК.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "binTree.h"

// Максимальный размер строки.
#define STR_LENGTH 501
// Направления для восстановления дерева по КЛП И ЛКП.
#define LEFT 1
#define UP 2
#define RIGHT 3


// Печать пробелов (для демонстрации работы алгоритма).
// Количество пробелов = количеству знаков строки:
// "Шаг N: ", где N - номер шага.
void printSpaces(int a){
    int count = 6;
    for (int i = 1; a%i < a; i*=10)
        count++;
    for (int i = 0; i < count; i++)
        putchar(' ');
}

// Вывод строк КЛП и ЛКП с указанием,
// какие узлы обрабатываются на текущем шаге
// (для демонстрации работы алгоритма).
void printCurrentStep(char* traversal_KLP, char* traversal_LKP, int index_KLP, int index_LKP, int counter){
    printSpaces(counter);
    printf("КЛП: ");
    for (int i = 0; i < strlen(traversal_KLP)-1; i++){
        if (i == index_KLP)
            printf("(%c)", traversal_KLP[i]);
        else
            printf("%c", traversal_KLP[i]);
    }
    putchar('\n');
    printSpaces(counter);
    printf("ЛКП: ");
    for (int i = 0; i < strlen(traversal_LKP)-1; i++){
        if (i == index_LKP)
            printf("(%c)", traversal_LKP[i]);
        else
            printf("%c", traversal_LKP[i]);
    }
    putchar('\n');
}



// Восстановление дерева из КЛП и ЛКП.
// возвращает: 1 - возникли ошибки, 0 - строки валидны
int treeRecovering(BinTree** binTree, char* traversal_KLP, char* traversal_LKP){
    int index_KLP = 0;
    int index_LKP = 0;
    int counter = 0; // счетчик для разных нужд
    int direction; // направление обхода для восстановления дерева
    int str_len; // длина строк обхода
    
    putchar('\n'); // Для красивого вывода :-)
    
    // Проверка на ревенство длин строк КЛП и ЛКП.
    if (strlen(traversal_KLP) != strlen(traversal_LKP)){
        printf("Ошибка: введены некорректные данные.\n");
        printf("Длина обхода КЛП - %zu, длина обхода ЛКП - %zu.\n\n", strlen(traversal_KLP)-1, strlen(traversal_LKP)-1);
        return 1;
    }
    str_len = strlen(traversal_KLP) - 1;
    
    // Проверка на то, что строки не пустые
    if (str_len == 0){
        printf("Вы ввели пустое дерево.\n\n");
        return 1;
    }
    
    // Проверка на использование недопустимых символов.
    for (int i = 0; i < str_len; i++){
        if (!isdigit(traversal_KLP[i]) && !isalpha(traversal_KLP[i])){
            if (!counter)
                printf("Ошибка: введены некорректные данные.\n");
            printf("Символ №%d в обходе КЛП - '%c'.\n", i+1, traversal_KLP[i]);
            counter++;
        }
        if (!isdigit(traversal_LKP[i]) && !isalpha(traversal_LKP[i])){
            if (!counter)
                printf("Ошибка: введены некорректные данные.\n");
            printf("Символ №%d в обходе ЛКП - '%c'.\n", i+1, traversal_LKP[i]);
            counter++;
        }
    }
    if (counter){
        printf("Строки должны состоять только из цифр и латинских букв.\n\n");
        return 1;
    }

    // Проверка на отсутствие повторяющихся узлов в каждом обходе.
    for (int i = 0; i < str_len; i++){
        for (int j = i; j < str_len; j++){
            if (traversal_KLP[i] == traversal_KLP[j] && i != j){
                if (!counter)
                    printf("Ошибка: введены некорректные данные.\n");
                printf("Узел '%c' встречается в обходе КЛП больше одного раза.\n", traversal_KLP[i]);
                counter++;
            }
            if (traversal_LKP[i] == traversal_LKP[j] && i != j){
                if (!counter)
                    printf("Ошибка: введены некорректные данные.\n");
                printf("Узел '%c' встречается в обходе ЛКП больше одного раза.\n", traversal_LKP[i]);
                counter++;
            }
        }
    }
    if (counter){
        putchar('\n'); // Для красивого вывода :-)
        return 1;
    }
    
    // Проверка на соответствие узлов в КЛП и ЛКП.
    for (int i = 0; i < str_len; i++){
        for (int j = 0; j < str_len; j++){
            if (traversal_KLP[i] == traversal_LKP[j]){
                break;
            }
            if (j == str_len - 1){
                if (!counter)
                    printf("Ошибка: введены некорректные данные.\n");
                printf("Узел '%c' встречается в обходе КЛП, но отсутствует в обходе ЛКП.\n", traversal_KLP[i]);
                counter++;
            }
        }
        for (int j = 0; j < str_len; j++){
            if (traversal_LKP[i] == traversal_KLP[j]){
                break;
            }
            if (j == str_len - 1){
                if (!counter)
                    printf("Ошибка: введены некорректные данные.\n");
                printf("Узел '%c' встречается в обходе ЛКП, но отсутствует в обходе КЛП.\n", traversal_LKP[i]);
                counter++;
            }
        }
    }
    if (counter){
        putchar('\n'); // Для красивого вывода :-)
        return 1;
    }
    
    
    // Создание дерева.
    direction = LEFT;
    counter = 1;
    printf("Алгоритм восстановления дерева по КЛП и ЛКП:\n\n");
    
    printf("Шаг %d:\n", counter);
    printCurrentStep(traversal_KLP, traversal_LKP, index_KLP, index_LKP, counter);
    printSpaces(counter);
    printf("'%c' - корень дерева.\n", traversal_KLP[index_KLP]);
    *binTree = initBinTree(traversal_KLP[index_KLP]);
    counter++;
    if (traversal_KLP[index_KLP] == traversal_LKP[index_LKP]){
        direction = UP;
    }
    index_KLP++;
    
    while(index_KLP < str_len){
        if (direction == LEFT){
            printf("Шаг %d:\n", counter);
            printCurrentStep(traversal_KLP, traversal_LKP, index_KLP, index_LKP, counter);
            printSpaces(counter);
            printf("'%c' - корень левого поддерева '%c'.\n", traversal_KLP[index_KLP], traversal_KLP[index_KLP-1]);
            findBinTree(*binTree, traversal_KLP[index_KLP-1])->leftTree = initBinTree(traversal_KLP[index_KLP]);
            if (traversal_KLP[index_KLP] == traversal_LKP[index_LKP]){
                direction = UP;
            }
            index_KLP++;
        } else if (direction == UP){
            for (int i = 0; i < index_KLP; i++){
                if (traversal_LKP[index_LKP] == traversal_KLP[i]){
                    index_LKP++;
                    break;
                }
                if (i == index_KLP-1){
                    direction = RIGHT;
                }
            }
        } else if (direction == RIGHT){
            printf("Шаг %d:\n", counter);
            printCurrentStep(traversal_KLP, traversal_LKP, index_KLP, index_LKP, counter);
            printSpaces(counter);
            printf("'%c' - корень правого поддерева '%c'.\n", traversal_KLP[index_KLP], traversal_LKP[index_LKP-1]);
            findBinTree(*binTree, traversal_LKP[index_LKP-1])->rightTree = initBinTree(traversal_KLP[index_KLP]);
            if (traversal_KLP[index_KLP] != traversal_LKP[index_LKP]){
                direction = LEFT;
            }
            else {
                for (int i = 0; i < index_KLP; i++){
                    if (traversal_KLP[i] == traversal_LKP[index_LKP+1]){
                        direction = UP;
                        break;
                    }
                }
                index_LKP++;
            }
            index_KLP++;
        }
        if (direction != UP){
            counter++;
        }
    }
   
    return 0;
}


// Вывод изображения дерева на экран.
// Создание сетки дерева для дальнейшей оптимизации рисунка.
void addUnitsInGrid(BinTree* binTree, char** grid, int level, int deep_level, int horizontalIndex){
    grid[level-1][horizontalIndex] = binTree->a;
    int a = 1;
    for (int i = 0; i < deep_level-level-1; i++)
        a*=2;
    if (level < deep_level){
        for (int i = 1; i <= a; i++){
            grid[level-1][horizontalIndex-i] = LEFT;
            grid[level-1][horizontalIndex+i] = RIGHT;
        }
    }
    if (leftBinTree(binTree) != NULL){
        addUnitsInGrid(leftBinTree(binTree), grid, level+1, deep_level, horizontalIndex - a);
    }
    if (rightBinTree(binTree) != NULL){
        addUnitsInGrid(rightBinTree(binTree), grid, level+1, deep_level, horizontalIndex + a);
    }
}
// Вывод изображения дерева.
void treeDrawing(BinTree* binTree){
    if (binTree == NULL){
        printf("Вы ввели пустое дерево.\n");
    }
    if (leftBinTree(binTree) == NULL && rightBinTree(binTree) == NULL){
        printf("%c\n\n", binTree->a);
        return;
    }
    // В начале "нарисую" дерево в двумерном массиве.
    int deep_level = binTreeDeepLevel(binTree); // глубина дерева
    int gridWidth = 1; // ширина сетки
    for (int i = 0; i < deep_level; i++)
        gridWidth*=2;
    gridWidth--;
    int horizontalTab = 0; // расстояние между узлами по горизонтали

    // Создам и заполню сетку нулями.
    char** grid = (char**)malloc(sizeof(char*)*deep_level);
    for (int i = 0; i < deep_level; i++){
        grid[i] = (char*)malloc(sizeof(char)*gridWidth);
        for (int j = 0; j < gridWidth; j++){
            grid[i][j] = 0;
        }
        horizontalTab = horizontalTab*2+1;
    }
    // Внесение в сетку узлов дерева и веток.
    addUnitsInGrid(binTree, grid, 1, deep_level, horizontalTab/2);
    // Оптимизация сетки.
    for (int j = 0; j < gridWidth; j++){
        for (int i = 0; i < deep_level; i++){
            if (grid[i][j] != 0 && grid[i][j] != LEFT && grid[i][j] != RIGHT)
                break;
            if (i == deep_level-1){
                for (int k = j; k < gridWidth-1; k++){
                    for (int l = 0; l < deep_level; l++){
                        grid[l][k] = grid[l][k+1];
                    }
                }
                gridWidth--;
                j--;
            }
        }
    }

    // Построение дерева по сетке.
    for (int i = 0; i < deep_level; i++){
        for (int j = 0; j < gridWidth; j++){
            if (grid[i][j] == 0)
                printf("   ");
            if (grid[i][j] == LEFT)
                printf("---");
            if (grid[i][j] == RIGHT){
                if (grid[i+1][j] != 0 && grid[i+1][j] != LEFT && grid[i+1][j] != RIGHT)
                    printf("-  ");
                else
                    printf("---");
            }
            if (grid[i][j] != 0 && grid[i][j] != LEFT && grid[i][j] != RIGHT){
                if (j < gridWidth-1 && grid[i][j+1] == RIGHT)
                    printf("%c--", grid[i][j]);
                else
                    printf("%c  ", grid[i][j]);
            }
        }
        putchar('\n');
        for (int j = 0; j < gridWidth; j++){
            if (grid[i][j] == 0 || (grid[i][j] != LEFT && grid[i][j] != RIGHT))
                printf("   ");
            if (grid[i][j] == LEFT || grid[i][j] == RIGHT){
                if (grid[i+1][j] != 0 && grid[i+1][j] != LEFT && grid[i+1][j] != RIGHT)
                    printf("|  ");
                else
                    printf("   ");
            }
        }
        putchar('\n');
    }

    // Освобождение памяти.
    for (int i = 0; i < deep_level; i++)
        free(grid[i]);
    free(grid);
}

// Перечисление узлов дерева в порядке ЛПК.
void print_traversal_LPK(BinTree* binTree){
    if (binTree != NULL){
        print_traversal_LPK(leftBinTree(binTree));
        print_traversal_LPK(rightBinTree(binTree));
        putchar(binTree->a);
    }
}


// Освобождение памяти.
void freeMemory(BinTree* binTree){
    if(binTree != NULL){
        freeMemory(leftBinTree(binTree));
        freeMemory(rightBinTree(binTree));
        free(binTree);
    }
}



int main(){
    char traversal_KLP[STR_LENGTH]; // обход дерева в порядке КЛП
    char traversal_LKP[STR_LENGTH]; // обход дерева в порядке ЛКП
    BinTree* binTree = NULL; // бинарное дерево
    
    // приветствие
    printf("\nПрограмма, используя перечисления узлов дерева в порядке КЛП и ЛКП:\n");
    printf("а) восстанавливает дерево и выводит его изображение.\n");
    printf("б) перечисляет узлы дерева в порядке ЛПК.\n");
    
    // считывание строк КЛП и ЛКП
    printf("\nПеречислите узлы дерева в порядке КЛП (не больше %d символов):\n", STR_LENGTH-1);
    fgets(traversal_KLP, STR_LENGTH, stdin);
    printf("Перечислите узлы дерева в порядке КЛП (не больше %d символов):\n", STR_LENGTH-1);
    fgets(traversal_LKP, STR_LENGTH, stdin);
    
    // Восстановление дерева.
    if (treeRecovering(&binTree, traversal_KLP, traversal_LKP) == 0){
        printf("\nДерево построено.\n");
        // Вывод изображения и обхода ЛПК.
        printf("\nИзображение дерева:\n\n");
        treeDrawing(binTree);
        printf("Обход ЛПК для данного дерева:\n");
        print_traversal_LPK(binTree);
        printf("\n\n");
    }
    
    // Освобождение памяти.
    freeMemory(binTree);
    
    return 0;
}