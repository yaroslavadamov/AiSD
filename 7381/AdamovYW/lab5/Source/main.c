/*
    Вариант 9:
    1) По заданному файлу F (типа file of Elem), все элементы
    которого различны, построить БДП определённого типа;
    2) Записать в файл элементы построенного БДП в порядке их возрастания;
    вывести построенное БДП на экран.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LENGTH 81

// Направления для рисование стрелок при выводе изображения дерева.
enum Direction {
    LEFT = 1,
    RIGHT
};


typedef struct BST{
    char key;
    struct BST * left;
    struct BST * right;
} BST;


// Возврат левого поддерева.
BST* leftBST(BST * tree){
    if (tree != NULL)
        return tree->left;
    else
        return NULL;
}


// Возврат правого поддерева.
BST* rightBST(BST* tree){
    if (tree != NULL)
        return tree->right;
    else
        return NULL;
}


BST * initBST(char key){
    BST * tree = (BST*)malloc(sizeof(BST));
    tree->key = key;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}


int BST_DeepLevel(BST* tree){
    if (tree == NULL)
        return 0;
    int leftDeep = BST_DeepLevel(leftBST(tree));
    int rightDeep = BST_DeepLevel(rightBST(tree));
    return 1 + (leftDeep > rightDeep ? leftDeep : rightDeep);
}


// Печать пробелов для демонтсрации работы алгоритма.
void print_spaces(int counter){
    for(int i = 0; i < counter; i++){
        printf("    ");
    }
}

BST * BST_create(char * bst_str){
    if (strlen(bst_str) == 0){
        return NULL;
    }

    printf("\nАлгоритм построения БДП:\n\n");
    printf("Символ №1 - '%c':\n", bst_str[0]);
    printf("   '%c' - корень дерева.\n", bst_str[0]);
    BST * tree = initBST(bst_str[0]);

    for (int i = 1; i < strlen(bst_str); i++){
        printf("\nСимвол №%d - '%c':\n", i+1, bst_str[i]);
        if (i > 1){
            printf("Текущее дерево:\n");
            BST_draw(tree);
        }
        int counter = 1;
        BST * current_tree = tree;
        while(1){
            if (bst_str[i] < current_tree->key){
                print_spaces(counter);
                printf("'%c' < '%c'\n", bst_str[i], current_tree->key);
                if (current_tree->left == NULL){
                    print_spaces(counter);
                    printf("Левое поддерево узла '%c' - пусто.\n", current_tree->key);
                    print_spaces(counter);
                    printf("'%c' - левое поддерево '%c'.\n", bst_str[i], current_tree->key);
                    current_tree->left = initBST(bst_str[i]);
                    break;
                } else {
                    print_spaces(counter);
                    printf("'%c' - левое поддерево узла %c.\n", leftBST(tree)->key, current_tree->key);
                    counter ++;
                    current_tree = current_tree->left;
                }
            } else {
                print_spaces(counter);
                printf("'%c' > '%c'\n", bst_str[i], current_tree->key);
                if (current_tree->right == NULL){
                    print_spaces(counter);
                    printf("Правое поддерево узла '%c' - пусто.\n", current_tree->key);
                    print_spaces(counter);
                    printf("'%c' - правое поддерево '%c'.\n", bst_str[i], current_tree->key);
                    current_tree->right = initBST(bst_str[i]);
                    break;
                } else {
                    print_spaces(counter);
                    printf("'%c' - правое поддерево узла %c.\n", rightBST(tree)->key, current_tree->key);
                    counter ++;
                    current_tree = current_tree->right;
                }
            }
        }
    }

    return tree;
}


// Вывод изображения дерева на экран.

// Создание сетки дерева для дальнейшей оптимизации рисунка.
void addUnitsInGrid(BST* tree, char** grid, int level, int deep_level, int horizontalIndex){
    grid[level-1][horizontalIndex] = tree->key;
    int a = 1;
    for (int i = 0; i < deep_level-level-1; i++)
        a*=2;
    if (level < deep_level){
        for (int i = 1; i <= a; i++){
            grid[level-1][horizontalIndex-i] = LEFT;
            grid[level-1][horizontalIndex+i] = RIGHT;
        }
    }
    if (leftBST(tree) != NULL){
        addUnitsInGrid(leftBST(tree), grid, level+1, deep_level, horizontalIndex - a);
    }
    if (rightBST(tree) != NULL){
        addUnitsInGrid(rightBST(tree), grid, level+1, deep_level, horizontalIndex + a);
    }
}
// Вывод изображения дерева.
void BST_draw(BST* tree){
    if (tree == NULL){
        printf("Вы ввели пустое дерево.\n");
    }
    if (leftBST(tree) == NULL && rightBST(tree) == NULL){
        printf("%c\n\n", tree->key);
        return;
    }
    // В начале "нарисую" дерево в двумерном массиве.
    int deep_level = BST_DeepLevel(tree); // глубина дерева
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
    addUnitsInGrid(tree, grid, 1, deep_level, horizontalTab/2);
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

// Вывод результата.
void printResult(BST * tree, FILE * fileWrite){
    if(leftBST(tree) != NULL){
        printResult(leftBST(tree), fileWrite);
    }
    if (fileWrite != NULL){
        printf("%c", tree->key);
        fprintf(fileWrite, "%c", tree->key);
    }
    if (rightBST(tree) != NULL){
        printResult(rightBST(tree), fileWrite);
    }
}


// Очистка памяти.
void freeMemory(BST* tree){
    if(tree != NULL){
        freeMemory(leftBST(tree));
        freeMemory(rightBST(tree));
        free(tree);
    }
}


int main(){
    char fileName[STR_LENGTH];
    char bst_str[STR_LENGTH]; // входная страка из файла
    FILE * fileRead; // файл с данными
    FILE * fileWrite; // файл, куда будет записан результат
    BST * tree = NULL; // бинарное дерево поиска
    int counter = 0; // счетчик для разных нужд
    
    // Приветствие.
    printf("\nПрограмма считывает строку из файла и строит из полученных данных БДП,\n");
    printf("выводит его изображение на экран и записывает элементы БДП в порядке возрастания в файл.\n");

    // Считывание входных данных.
    printf("\nВведите имя файла (не больше %d символов): ", STR_LENGTH-1);
    fgets(fileName, STR_LENGTH, stdin);
    if (fileName[strlen(fileName)-1] == '\n'){
        fileName[strlen(fileName)-1] = '\0';
    }
    fileRead = fopen(fileName, "r");
    if (fileRead == NULL){
        printf("\nОшибка: файл не найден.\n");
        return 1;
    }
    fgets(bst_str, STR_LENGTH, fileRead);
    if (bst_str[strlen(bst_str)-1] == '\n'){
        bst_str[strlen(bst_str)-1] = '\0';
    }
    fclose(fileRead);

    // Проверки на ошибки.
    if (strlen(bst_str) == 0){
        printf("Вы ввели пустую строку.\n");
        return 0;
    }
    printf("\nВходная строка: %s\n", bst_str);
    // Проверка на использование недопустимых символов.
    for (int i = 0; i < strlen(bst_str); i++){
        if (!isdigit(bst_str[i]) && !isalpha(bst_str[i])){
            if (!counter)
                printf("\nВведены некорректные данные:\n");
            printf("Символ №%d - '%c'.\n", i+1, bst_str[i]);
            counter++;
        }
    }
    if (counter){
        printf("\nСтроки должны состоять только из цифр и латинских букв.\n");
        return 1;
    }
    // Проверка на отсутствие повторяющихся символов.
    for (int i = 0; i < strlen(bst_str); i++){
        for (int j = i; j >= 0; j--){
            if (bst_str[i] == bst_str[j] && i != j){
                break;
            }
            if (j == 0){
                for (int k = i; k < strlen(bst_str); k++){
                    if (bst_str[i] == bst_str[k] && i != k){
                        if (!counter){
                            printf("\nВведены некорректные данные:\n");
                            printf("'%c'", bst_str[i]);
                        } else {
                            printf(", '%c'", bst_str[i]);
                        }
                        counter++;
                        break;
                    }
                }
            }
        }
    }
    if (counter){
        if (counter > 1){
            printf(" встречаются больше одного раза.\n");
        } else {
            printf(" встречается больше одного раза.\n");
        }
        return 1;
    }

    tree = BST_create(bst_str);

    printf("\nДерево построено.\nИзображение дерева:\n\n");
    BST_draw(tree);

    printf("\nЭлементы БДП в порядке возрастания: ");
    fileWrite = fopen("result.txt", "w");
    printResult(tree, fileWrite);
    fclose(fileWrite);
    printf("\n(также записаны в файл result.txt).\n");

    freeMemory(tree);

    return 0;
}
