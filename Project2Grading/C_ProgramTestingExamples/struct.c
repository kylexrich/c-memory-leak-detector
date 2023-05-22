#include <stdlib.h>


struct S {
    char a;
    struct S *b;
};

int main() {
    struct S *ptr = malloc(sizeof(struct S));
    struct S *curr = ptr;
    for (int i = 0; i < 5; i ++) {
        curr->b = malloc(sizeof(struct S));
        curr = curr->b;
    }
    /* Above might be converted into:
        if (...) {
            curr->b = malloc(sizeof(struct S));
            curr = curr->b;
        }
        Which will actually cause it to be leak-free
    */

    free(ptr->b);
    free(ptr);

    return 0;
}