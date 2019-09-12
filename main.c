//
//  main.c
//  c-sandbox
//
//  Created by Vlad Zhavoronkov on 9/13/19.
//  Copyright © 2019 Vlad Zhavoronkov. All rights reserved.
//

#include <stdio.h>
#include <time.h>

#define NUMBER_OF_ITERATIONS 100000000
#define REPEAT_COUNT 5
#define TRUE 1
#define FALSE 0

typedef struct MeasureLog {
    double time;
    long numberOfAssigments;
} MeasureLog;

MeasureLog measureWithoutChecks(void);
MeasureLog measureWithChecks(void);
static void setBooleans(void);

int booleans[NUMBER_OF_ITERATIONS];

int main(int argc, const char * argv[]) {
    setBooleans();
    MeasureLog measureWithIfs = measureWithChecks();
    MeasureLog measureWithoutIfs = measureWithoutChecks();
    printf("with ifs: %f\n", measureWithIfs.time);
    printf("number of assignments: %ld\n", measureWithIfs.numberOfAssigments);
    
    printf("without: %f\n", measureWithoutIfs.time);
    printf("number of assignments: %ld\n", measureWithoutIfs.numberOfAssigments);
    
    return 0;
}

MeasureLog measureWithChecks() {
    MeasureLog output;
    clock_t begin = clock();
    long numberOfAssigments = 0;
    
    int booleanVar = 0;
    for (long i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        if (booleanVar != booleans[i]) {
            numberOfAssigments++;
            booleanVar = booleans[i];
        }
    }
    
    clock_t end = clock();
    output.time = (double)(end - begin) / CLOCKS_PER_SEC;
    output.numberOfAssigments = numberOfAssigments;
    
    return output;
}

MeasureLog measureWithoutChecks() {
    MeasureLog output;
    clock_t begin = clock();
    long numberOfAssigments = 0;
    
    int booleanVar = 0;
    for (long i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        numberOfAssigments++;
        booleanVar = booleans[i];
    }
    
    clock_t end = clock();
    output.time = (double)(end - begin) / CLOCKS_PER_SEC;
    output.numberOfAssigments = numberOfAssigments;
    
    return output;
}

void setBooleans() {
    int repeatCount = REPEAT_COUNT;
    int boolean = TRUE;
    for (long i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        if (!repeatCount) {
            repeatCount = REPEAT_COUNT;
            boolean = boolean ? FALSE : TRUE;
        }
        booleans[i] = boolean;
        repeatCount--;
    }
}
