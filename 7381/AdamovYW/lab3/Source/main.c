#include  <stdio.h>
#include <string.h>

#define STACKSIZE 100
#define N 501

// стек
typedef struct Stack{
    int arr[STACKSIZE];
    int topIndex;
} Stack;

// инициализация стека
Stack initStack(){
    Stack stack;
    stack.topIndex=0;
    return stack;
}

// проверка на наличие элементов в стеке
int isEmpty(Stack * stack){
    return !stack->topIndex;
}

// размер стека
int size(Stack * stack){
    return stack->topIndex;
}

// добавление элемента в стек
void push(Stack * stack, int c){
    if (size(stack) < STACKSIZE){
        stack->arr[stack->topIndex] = c;
        stack->topIndex++;
    } else {
        printf("Ошибка: стек заполнен. Новый элемент не был добавлен.");
    }
}

// извлечение элемента из стека
int pop(Stack * stack){
    if (!isEmpty(stack)){
        stack->topIndex--;
        return stack->arr[stack->topIndex];
    } else {
        printf("Ошибка: стек пуст.");
        return 0;
    }
}

// верхний элемент стека
int top(Stack * stack){
    if (!isEmpty(stack)){
        return stack->arr[stack->topIndex - 1];
    } else {
        printf("Ошибка: стек пуст.");
        return 0;
    }
}


// проверка строки на валидность
// возвращает 0, если ошибок нет
int error_checking(char * str){
    Stack stack = initStack(); // стек
    int presence_of_brackets = 0; // наличие скобок
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '('){
            presence_of_brackets = 1;
            if (size(&stack) == STACKSIZE){
                printf("\nОшибка: стек переполнен.\n");
                printf("Вы используете слишком большое количество скобок.\n");
                return 1;
            }
            push(&stack, i+1);
        }
        if (str[i] == ')'){
            if (size(&stack) == 0){
                printf("\nОшибка: символ №%d - ')', парная открывающая скобка отсутствует.\n", i+1);
                return 1;
            }
            pop(&stack);
        }
    }
    if (!isEmpty(&stack)){
        printf("\nОшибка: символ №%d - '(', парная закрывающая скобка отсутствует.", pop(&stack));
        return 1;
    }
    if (presence_of_brackets == 0){
        printf("\nВ строке отсутствуют скобки.");
        return 1;
    }
    
    return 0;
}

// вывод индексов пар скобок
void output_brackets_indexes(char * str){
    Stack stack = initStack(); // стек
    
    printf("\nСортировка по возрастания номеров позиций открывающих скобок.\n");
    // демонстрация работы алгоритма
    printf("Ход работы алгоритма:\n");
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '('){
            printf("  Символ №%d - '('. Поиск парной скобки:\n", i+1);
            for (int j = strlen(str)-1; j >= 0; j--){
                if (str[j] == ')'){
                    printf("    Символ №%d - ')', push %d\n", j+1, j+1);
                    push(&stack, j+1);
                }
                if (str[j] == '('){
                    if (j > i){
                        printf("    Символ №%d - '(', pop (%d)\n", j+1, pop(&stack));
                    } else{
                        printf("    Символ №%d - '(', pop (%d), пара скобок: | %d  %d |\n", j+1, pop(&stack), j+1, top(&stack));
                        //printf(" %d  %d |", i+1, pop(&stack));
                        break;
                    }
                }
            }
        }
    }
    // вывод результата
    printf("Результат:\n|");
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '('){
            for (int j = strlen(str)-1; j >= 0; j--){
                if (str[j] == ')')
                    push(&stack, j+1);
                if (str[j] == '('){
                    if (j > i){
                        pop(&stack);
                    } else{
                        printf(" %d  %d |", i+1, pop(&stack));
                        break;
                    }
                }
            }
        }
    }
    
    
    printf("\n\nСортировка по возрастания номеров позиций закрывающих скобок.\n");
    // демонстрация работы алгоритма
    printf("Ход работы алгоритма:\n");
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '('){
            printf("  Символ №%d - '(', push %d\n", i+1, i+1);
            push(&stack, i+1);
        }
        if (str[i] == ')'){
            printf("  Символ №%d - ')', pop (%d), пара скобок: | %d  %d |\n", i+1, pop(&stack), top(&stack), i+1);
        }
    }
    // вывод результата
    printf("Результат:\n|");
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '(')
            push(&stack, i+1);
        if (str[i] == ')'){
            printf(" %d  %d |", pop(&stack), i+1);
        }
    }
    printf("\n\n");
}


int main(void)
{
    char str[N]; // строка
    
    printf("\nПрограмма принимает строку и для каждой пары соответствующих открывающей\n");
    printf("и закрывающей скобок выводит номера их позиций в строке.\n");
    printf("\nВведите строку (не больше %d символов):\n", N-1);
    fgets(str, N, stdin);
    
    if (error_checking(str) == 0)
        output_brackets_indexes(str);
    
    return 0;
}
