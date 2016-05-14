/* (C) 2016 Daniele Zanotelli
 *
 * Solving the knapsack problem.
 *
 * The purpouse of this program is to give a first solution
 * without considering performance issues.
 */

#include <stdlib.h>
#include <stdio.h>

#define KNAPSACK_CAPCITY 10
#define OBJ_COUNT 10
#define OBJ_VALUE_MAX 10
#define OBJ_WEIGHT_MAX 10

typedef struct {
        int weight;
        int value;
} item;

item **generate_items(int total_objects, int max_weight, int max_value);
void print_line(int line_length);
void print_items(item **items_to_print);

/* -------------------------------------------------------------------------- */
int main()
{
        /* variable definition */
        item **all_items = generate_items(OBJ_COUNT, OBJ_WEIGHT_MAX,
                                          OBJ_VALUE_MAX);

        /* run */
        printf("The knapsack problem\n");
        print_line(60);
        printf("Available items:\n");
        print_items(all_items);


        /* free the memory */
        free(all_items);
}

item **generate_items(int count, int max_weight, int max_value)
{
        /*
         * Generate *count* random items with a weight between 1 and
         * *max_weight* and a value between 1 and *max_value*
         */
        int i;
        item **items = malloc(sizeof(item*) * (count+1));
        item *temp_item;

        for (i=0; i<count; i++) {
                temp_item = malloc(sizeof(item));
                temp_item->value = (rand() % (max_value)) +1 ;
                temp_item->weight = (rand() % (max_weight)) +1;
                items[i] = temp_item;
        }
        items[i] = NULL;

        return items;
}

void print_line(int length)
{
        /*
         * Just print out *length* number of '-'.
         */
        int i = 0;
        while (i++ <= length) printf("-");
        printf("\n");
}

void print_items(item **items)
{
        /*
         * Print a table with the items. Just three cols: id, weight, value.
         */
        int i = 0;

        printf("id\tweight\tvalue\n");
        print_line(60);

        while (*items) {
                printf("%d\t%d\t%d\n", i, (*items)->weight, (*items)->value);
                i++;
                items++;
        }
}

unsigned int factorial(int n)
{
        /*
         * Return the factorial of *n*.
         */
        else if (n == 0) {
                return 1;
        }
        else {
                return n * factorial(n-1);
        }
}

int **combinations(int *items, unsigned int k)
{
        /*
         * Return a pointer to an array of int with all the possible
         * combinations.
         *
         * arguments:
         * ----------
         * *items*
         *     a pointer to a list of int, the last item must be NULL
         *     The input list of integers which compute the combinations on.
         *     This list must be long count(items)+1 since the last item
         *     must be valorized to NULL (it marks the end of the list).
         * *k*
         *     unsigned int
         *     The length of each combination subsets.
         */
        int n;
        int total;
        int **result;
        int *combo_tmp;
        int i;

        /* FIXME
         * n = count(items)
         */

        /* checks */
        if (k > n) {
                printf("Error: (k=%d) > (n=%d) ! Assuming k=n ...\n");
                k = n;
        }

        /* total amount of combinations, init result pointer */
        total = factorial(n) / factorial(k) * factorial(n-k);
        result = malloc(sizeof(int*) * (total+1));

        /* condition of termination */
        if (items_count == 1 && k == 1) {
                /* FIXME: return list with 1 elment = items */
        }
        else if (items_count > 1 && k == 1) {
                /* FIXME
                 * return item[0] + combination(items[1:], 1) (list)
                 */
        }
        else {
                /* FIXME:
                 * for i=0; i<count(items)-k; i++
                 *      return items[i] + combinations(items[i:], k-1) (list)
                 */
        }
}
