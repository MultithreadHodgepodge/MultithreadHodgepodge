static inline int smaller(const void *a, const void *b) {
        return *(int *)a -*(int *)b;
}
static inline int bigger(const void *a, const void *b) {
        return *(int *)b -*(int *)a;
}