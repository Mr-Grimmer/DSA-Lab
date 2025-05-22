#include <stdio.h>

int find_last_person_2d_array(int n, int k) {
    int people[n][2];  // [][0] = person number, [][1] = status (1 alive, 0 executed)
    for(int i = 0; i < n; i++) {
        people[i][0] = i + 1;
        people[i][1] = 1;
    }

    int count = n;  // number of people alive
    int index = 0;  // start counting from first person
    int skip;

    while (count > 1) {
        skip = 0;
        // skip k alive people
        while (skip < k) {
            if (people[index][1] == 1) {
                skip++;
            }
            if (skip == k) break;
            index = (index + 1) % n;
        }
        // execute the person at current index
        while (people[index][1] == 0) {
            index = (index + 1) % n;
        }
        people[index][1] = 0; // mark executed
        count--;
        index = (index + 1) % n; // move to next person
    }

    // find last alive person
    for (int i = 0; i < n; i++) {
        if (people[i][1] == 1) {
            return people[i][0];
        }
    }
    return -1; // error case
}

int main() {
    int n, k;
    printf("Enter number of people and skip count: ");
    scanf("%d%d", &n, &k);

    int last_person = find_last_person_2d_array(n, k);
    printf("The last person remaining is: %d\n", last_person);
    return 0;
}
