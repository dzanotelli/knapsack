/* (C) 2016 Daniele Zanotelli
 *
 * Solving the knapsack problem.
 *
 * The purpouse of this program is to give a first solution
 * without considering performance issues.
 */

#include <stdlib.h>
#include <stdio.h>

#define KNAPSACK_CAPACITY 10
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
int factorial (int number);
size_t intlistlen(int *elements);
size_t intlistlistlen(int **elements);
int **combinations(int *elements, size_t k);
int *cut_head(int *elements, size_t head_length);
int *concat(int *list0, int *list1);

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

int factorial(int n)
{
        /*
         * Return the factorial of *n*.
         */
        if (n == 0) {
                return 1;
        }
        else {
                return n * factorial(n-1);
        }
}

size_t intlistlen(int *items)
{
        /*
         * Return the length of a list of integers. The last item of the list
         * must be NULL.
         */
        size_t length = 0;
        while (items++) length++;
        return length;
}

size_t intlistlistlen(int **items)
{
        /*
         * Return the length of a list of lists of integers. The last item of
         * the list must be NULL.
         */
        size_t length = 0;
        while (items++) length++;
        return length;
}

int **combinations(int *items, size_t k)
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
        size_t n = intlistlen(items);
        size_t total;
        int **result;
        int *combo_tmp;
        int i;
        int j;
        int z;
        int *head;
        int *body;
        int **subcombo;
        size_t subcombo_len;
        size_t sub_k;

        /* checks */
        if (k > n) {
                printf("Warning: (k=%d) > (n=%d) ! Assuming k=n ...\n");
                k = n;
        }

        /* total amount of combinations, init result pointer */
        total = factorial(n) / factorial(k) * factorial(n-k);
        result = malloc(sizeof(int*) * (total + 1));

        /* condition of termination */
        if (n == 1 && k == 1) {
                result = malloc(sizeof(int*) * 2);
                *result++ = items;
                *result-- = NULL;

                return result;
        }
        /* else if (n > 1 && k == 1) { */
        /*         /\* copy the head *\/ */
        /*         head = malloc(sizeof(int) * 2); */
        /*         *head++ = *items; */
        /*         head = NULL; */
        /*         head--; */

        /*         /\* extract the body *\/ */
        /*         body = cut_head(items, 1); */

        /*         /\* compute the combinations of k=1 of the body *\/ */
        /*         subcombo = combinations(body, 1); */
        /*         subcombo_len = intlistlistlen(subcombo); */

        /*         /\* return the sub-combinations with head ahead *\/ */
        /*         for (i=0; i<subcombo_len; i++) { */
        /*                 result[i] = concat(head, subcombo[i]); */
        /*         } */
        /*         result[i+1] = NULL; */

        /*         return result; */
        /* } */
        else {
                z = 0;
                for (i=0; i<(intlistlen(items) - k); i++) {
                        /* copy the i-item as head */
                        head = malloc(sizeof(int) * 2);
                        *head++ = items[i];
                        head = NULL;
                        head--;

                        /* extract the body */
                        body = cut_head(items, i+1);

                        /* compute the combinations of k-1 of the body */
                        sub_k = k - 1;
                        if (sub_k == 0) sub_k = 1;
                        subcombo = combinations(body, sub_k);

                        /* return the sub-combinations with head ahead */
                        for (j=0; j<intlistlistlen(subcombo); j++) {
                                *result++ = concat(head, subcombo[j]);
                                z++;
                        }
                }
                /* set terminator and rewind result */
                *result = NULL;
                while (z--) result--;

                return result;
        }
}

int *cut_head(int *items, size_t head_len)
{
        /*
         * Cut *head_len* elements from the *items* head, and return the
         * remaining list.
         */
        int i = 0;
        size_t result_len = intlistlen(items) - head_len;
        int *result = malloc(sizeof(int) * (result_len + 1));

        while (i++ < head_len) {
                items++;
        }

        i = 0;
        while (*result++ = *items++) {
                i++;
        };

        /* rewind result */
        while (i--) result--;

        return result;
}

int *concat(int *head, int *tail)
{
        /*
         * Return a list built as *head* + *tail*.
         */
        int i = 0;
        size_t head_len = intlistlen(head);
        size_t tail_len = intlistlen(tail);
        int *result = malloc(sizeof(int) * (head_len + tail_len + 1));

        /* copy head */
        while (*result++ = *head++) i++;
        result--;

        /* copy tail */
        while (*result++ = *tail++) i++;

        /* rewind result */
        while (i--) result--;

        return result;
}
