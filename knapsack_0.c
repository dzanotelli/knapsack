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
#define INT_SENTINEL -1

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
int **permutations_keqn(int *elements);
int *list_without_item(int *items, int i);
int *concat_int_lists(int *first_list, int *second_list);

/* -------------------------------------------------------------------------- */
int main()
{
        /* The idea is:
         * 1/ compute all the permutations where k = n on the indexes
         * 2/ one permutaton by one, item by item, compute the sum of the values
         *    until the weight constraint is reached and save the payoff
         *    somewhere (discarding the trailing items which will exceed the
         *    knapsack capacity)
         * 3/ compare the computed payoffs and keep the highest
         */
        item **all_items = generate_items(OBJ_COUNT, OBJ_WEIGHT_MAX,
                                          OBJ_VALUE_MAX);

        int *indexes = malloc(sizeof(int) * (OBJ_COUNT+1));
        int **indexes_perms = NULL;
        int i;
        int j;

        /* run */
        printf("The knapsack problem\n");
        print_line(60);
        //printf("Available items:\n");
        //print_items(all_items);

        /* build the array of indexes, 0 to OBJ_COUNT-1 */
        for (i=0; i<OBJ_COUNT; i++) {
                indexes[i] = i;
                //printf("%d\n", i);
        }
        indexes[OBJ_COUNT] = INT_SENTINEL;

        /* print_line(40); */
        /* for (i=0; indexes[i] != INT_SENTINEL; i++) { */
        /*         printf("indexes %d\n", indexes[i]); */
        /* } */

        /* compute all the permutations on the indexes */
        indexes_perms = permutations_keqn(indexes);

        printf("ok ho le perm\n");

        int result_count = 0;
        int list_count = 0;
        while (*indexes_perms) {
                printf("result %d:\n", result_count++);
                list_count = 0;

                while (**indexes_perms != INT_SENTINEL) {
                        printf("\titem %d: %d\n",
                               list_count++,
                               **indexes_perms);
                        (*indexes_perms)++;
                }
                indexes_perms++;
        }

        /* free the memory */
        free(all_items);
        free(indexes);

        return 0;
}

item **generate_items(int count, int max_weight, int max_value)
{
        /* Generate *count* random items with a weight between 1 and
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
        /* Just print out *length* number of '-'.
         */
        int i = 0;
        while (i++ <= length) printf("-");
        printf("\n");
}

void print_items(item **items)
{
        /* Print a table with the items. Just three cols: id, weight, value.
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
        /* Return the factorial of *n*.
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
        /* Return the length of a list of integers. The last item of the list
         * must be INT_SENTINEL.
         */
        size_t length = 0;
        while (*items++ != INT_SENTINEL) length++;
        return length;
}

size_t intlistlistlen(int **items)
{
        /* Return the length of a list of lists of integers. The last item of
         * the list must be NULL.
         */
        size_t length = 0;
        while (*items++) length++;
        return length;
}


int *list_without_item(int *items, int i)
{
        /* Return *items* without the *i*-nth element.
         */
        int items_len = intlistlen(items);
        int *result = malloc(sizeof(int) * items_len);
        int j = 0;

        if (i > (items_len - 1)) {
                i = items_len - 1;
        }

        while ((*result++ = items[j]) != INT_SENTINEL) {
                if (j == i) result--;
                j++;
        }

        // rewind results
        while (j--) result--;

        return result;
}

int *concat_int_lists(int* list0, int* list1)
{
        /* Concat *list0* and *list1*, lists of integers.
         */
        size_t len0 = intlistlen(list0);
        size_t len1 = intlistlen(list1);
        int *result = malloc(sizeof(int) * (len0 + len1 + 1));
        int count = 0;

        // copy list 0
        while (*list0 != INT_SENTINEL) {
                *result++ = *list0++;
                count++;
        }
        // copy list 1
        while ((*result++ = *list1++) != INT_SENTINEL) {
                count++;
        }

        // rewind result
        count++;
        while (count--) {
                result--;
        }

        return result;
}

int** permutations_keqn(int *elements)
{
        /* Return a list of list of integers with all the possibile
         * permutantions of *elements* where k = n.
         */
        int n;
        int perm_max;
        int **result = NULL;
        int *list = NULL;
        int i;
        int j;
        int k;
        int *others;
        int **sub_perm;
        size_t sub_perm_len;
        int one_item_list[2] = {INT_SENTINEL, INT_SENTINEL};

        // compute the max permutations, where n = k
        n = intlistlen(elements);
        perm_max = factorial(n);
        //printf("max permutations: %d\n", perm_max);

        // termination condition
        if (intlistlen(elements) == 1) {
                //printf("recursion term condition!\n");

                // copy elements to list
                list = malloc(sizeof(int) * 2);
                list[0] = elements[0];
                list[1] = INT_SENTINEL;

                // save list as result number 0
                result = malloc(sizeof(int*) * 2);
                result[0] = list;
                result[1] = NULL;
                return result;
        }

        // recursion
        //printf("recursion ...\n");

        result = malloc(sizeof(int*) * (perm_max + 1));
        for (i = 0; i < n; i++) {
                others = list_without_item(elements, i);
                sub_perm = permutations_keqn(others);
                sub_perm_len = intlistlistlen(sub_perm);

                // add to results
                one_item_list[0] = elements[i];
                for (j=0; j<sub_perm_len; j++) {
                        //printf("[n=%d]: i=%d j=%d\n", n, i, j);

                        *result++ = concat_int_lists(one_item_list,
                                                     sub_perm[j]);
                }
        }
        *result = NULL;

        // rewind result
        //printf("alla fine i=%d e j=%d\n", i, j);
        for (k=0; k<i*j; k++) {
                result --;
        }

        return result;
}
