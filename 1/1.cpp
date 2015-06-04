#include <cstdio>

#define MAX 15

int bitstring1[MAX];
int bitstring2[MAX];
int match1[MAX];
int match2[MAX];

int fix (int bitstring[], int index, int match) {
    if (bitstring[index] != match) {
        for (int i = index - 1; i >= 0; i--) {
            if (bitstring[i] == match) { 
                int distance = index - i;
                bitstring[i] = !match;
                bitstring[index] = match; 
                return distance;
            }
        }
        // its possible we get here, it means its not doable yo.
        return -1;
    } else {
        return 0;
    }
}

int main() {

    int n, m;
    while (scanf ("%d%d\n", &n, &m) != EOF) {

        for (int i = 0; i < n; i++) {
            scanf("%d", &bitstring1[i]);
            bitstring2[i] = bitstring1[i];
        }

        int x = 0;
        int match1Val = 0;
        int match2Val = 1;
        for (int i = 0; i < m; i++) {
            int p;
            scanf("%d", &p);
            for (int j = 0; j < p; j++) {
                match1[x+j] = match1Val;
                match2[x+j] = match2Val;
            }
            match1Val = !match1Val;
            match2Val = !match2Val;

            x += p;
        }

        // debug prints yo
        //for (int i = 0; i < n; i++) {
        //    printf("%d", bitstring1[i]);
        //}
        //printf ("\n");
        //for (int i = 0; i < n; i++) {
        //    printf("%d", match1[i]);
        //}
        //printf ("\n");
        //for (int i = 0; i < n; i++) {
        //    printf("%d", match2[i]);
        //}
        //printf ("\n");

        // now, make a new thingy
        // try match 1 first it starts with 0.
        int counter1 = 0;
        bool invalid1 = false;
 //       for (int j = 0; j < n; j++) {
 //           printf ("%d ", bitstring1[j]);
 //       }
 //       printf ("\n");
        for (int i = n - 1; i >= 0; i--) {
            
            int temp = fix (bitstring1, i, match1[i]);
//            printf ("Temp1 is %d\n", temp);
            if (temp != -1) {
                counter1 += temp;
            } else {
                invalid1 = true;
                break;
            }
//            for (int j = 0; j < n; j++) {
//                printf ("%d ", bitstring1[j]);
//            }
//            printf ("\n");
        }
        
        int counter2 = 0;
        bool invalid2 = false;
//        for (int j = 0; j < n; j++) {
//            printf ("%d ", bitstring2[j]);
//        }
//        printf ("\n");
        for (int i = n - 1; i >= 0; i--) {
            
            int temp = fix (bitstring2, i, match2[i]);
//            printf ("Temp2 is %d\n", temp);
            if (temp != -1) {
                counter2 += temp;
            } else {
                invalid2 = true;
                break;
            }
            
//            for (int j = 0; j < n; j++) {
//                printf ("%d ", bitstring2[j]);
//            }
//            printf ("\n");
        }
        
        if (invalid1 == false && counter1 < counter2) {
            printf ("%d\n", counter1);
        } else if (invalid2 == true) {
            printf ("%d\n", counter1);
        } else if (invalid1 == true) {
            printf ("%d\n", counter2);
        } else {
            printf ("%d\n", counter2);
        }
    }
    return 0;
}
