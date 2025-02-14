#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//==============================================================================
// Here the magic begins
void runApp(int size);

// malloc the space needed - simple
int *makeSpace(int size);

// func to free allocated space
void freeSpace(int *arr);

// func that goes over the input "1 by 1" and uses testInput on each
// RETURN 1 IF INVALID to parent func - runApp
int getNums(int *numbers, int size);

// checks for letters and symbols in input - '-' allowed
// RETURN 1 IF INVALID to parent func - getNums
int testInput(int *singleNum);

// gets the power of 2 of num
int getPowerOf2(int num);
//==============================================================================

void runApp(int size) {
    int *numbers = makeSpace(size);
    int totalPower = 0;
    // if allocation failed - free and exit program
    if (numbers == NULL) {
        freeSpace(numbers);
        exit(0);
    }
    printf("Enter numbers:\n");
    // flag if INPUT HANDLING FUNC find INVALID case
    // if INVALID - returns and finishes app
    // if VALID - continues to calculating powers of ints.
    int flag = getNums(numbers, size);
    if (flag) {
        freeSpace(numbers);
        return;
    }
    for (int i = 0; i < size; ++i) {
        totalPower = totalPower + getPowerOf2(numbers[i]);
    }
    printf("Total exponent sum is %d\n", totalPower);
    // free allocated space using my free func;
    freeSpace(numbers);
}

int *makeSpace(int size) {
    int *numbers = (int *) malloc(size * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    return numbers;
}

void freeSpace(int *arr) {
    free(arr);
}

int getNums(int *numbers, int size) {
    getchar();
    for (int i = 0; i < size; ++i) {
        int x = testInput(numbers + i);
        if (x) {
            return 1;
        }
    }
    return 0;
}

int testInput(int *singleNum) {
    char ch;
    int num = 0;
    int flag = 0;
    int mult = 1;
    while (scanf("%c", &ch) != EOF) {
        if (flag == 0 && num == 0 && ch == '-') {
            mult = -1;
            flag = 1;
            continue;
        }
        if (ch == '\n' || ch == ' ') {
            break;
        }
        if (ch < '0' || ch > '9') {
            printf("Invalid number\n");
            return 1;
        }
        num = num * 10 + (ch - '0');
    }
    *singleNum = mult * num;
    return 0;
}

int getPowerOf2(int num) {
    int temp = num;
    int counter = 0;
    if (num == 0) {
        return 0;
    }
    if (num == 1) {
        printf("The number %d is a power of 2: %d = 2^%d\n", num, num, 0);
        return 0;
    }
    while (temp % 2 == 0 && temp != 2) {
        temp = temp / 2;
        counter++;
    }
    if (temp == 2) {
        counter++;
        printf("The number %d is a power of 2: %d = 2^%d\n", num, num, counter);
        return counter;
    } else {
        return 0;
    }
}

int main(void) {
    printf("Enter size of input:\n");
    int size;
    scanf("%d", &size);
    if (size <= 0) {
        printf("Invalid size\n");
        return 0;
    }
    runApp(size);

    return 0;
}
