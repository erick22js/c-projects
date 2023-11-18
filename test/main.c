#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float g1 = 15;
int g2 = 2;
float g3 = 0;

int main(){
    time_t lt, nt;
    float l1= 15;
    int l2 = 2;
    float l3 = 0;

    printf("Started!\n\n");

    // Test global variables
    lt = time(NULL);
    for (int i=0; i<1000000000; i++){
        g1 += g2*g3;
        g2++;
        g3 *= 2;
    }
    nt = time(NULL);
    g1 = difftime(nt, lt);
    printf("Global in %f seconds...\n\n", g1);

    // Test local variables
    lt = time(NULL);
    for (int i=0; i<1000000000; i++){
        l1 += l2*l3;
        l2++;
        l3 *= 2;
    }
    nt = time(NULL);
    l1 = difftime(nt, lt);
    printf("Local in %f seconds...\n\n", l1);
    printf("%d %d\n", nt, lt);

    return 0;
}
