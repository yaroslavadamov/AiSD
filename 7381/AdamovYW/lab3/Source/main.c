// Программа принимает строку и для каждой пары соответствующих открывающей
// и закрывающей скобок выводит номера их позиций в строке.

#include  <stdio.h>
#include <string.h>

#define M 100
#define N 501

// стек
typedef struct Stack{
    int arr[M];
    int topIndex;
} Stack;

// инициализация стека
Stack initStack(){
    Stack stack;
    stack.topIndex=0;
    return stack;
}

// извлечение элемента из стека
int pop(Stack * stack){
    stack->topIndex--;
    return stack->arr[stack->topIndex];
}

// добавление элемента в стек
void push(Stack * stack, int c){
    stack->arr[stack->topIndex] = c;
    stack->topIndex++;
}

// верхний элемент стека
int top(Stack * stack){
    return stack->arr[stack->topIndex - 1];
}

// проверка на наличие элементов в стеке
int isEmpty(Stack * stack){
    return !stack->topIndex;
}

// размер стека
int size(Stack * stack){
    return stack->topIndex;
}



// проверка строки на валидность
// возвращает 0, если ошибок нет
int error_checking(char * str){
    Stack stack = initStack(); // стек
    int presence_of_brackets = 0; // наличие скобок
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '('){
            presence_of_brackets = 1;
            if (size(&stack) == M){
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
    printf("\nСортировка по возрастания номеров позиций открывающих скобок:\n|");
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
    printf("\nСортировка по возрастания номеров позиций закрывающих скобок:\n|");
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '(')
            push(&stack, i+1);
        if (str[i] == ')'){
            printf(" %d  %d |", pop(&stack), i+1);
        }
    }
    printf("\n");
}


int main(void)
{
    char str[N]; // строка
    
    printf("\nПрограмма принимает строку и для каждой пары соответствующих открывающей\n");
    printf("и закрывающей скобок выводит номера их позиций в строке.\n");
    printf("\nВведите строку (не больше %d символов): ", N-1);
    fgets(str, N, stdin);
    
    if (error_checking(str) == 0)
        output_brackets_indexes(str);
    
    return 0;
}