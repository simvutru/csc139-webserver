#include <stdio.h>

#define MAXBUF 8192
#define MAX_QUEUE_SIZE 100

typedef struct {
    int conn_fd;
    int file_size;
    int is_static;
    char filename[MAXBUF];
    char cgiargs[MAXBUF];
} request_t;

/* Array of pointers to requests, plus an element counter */
request_t *array[MAX_QUEUE_SIZE];
int queue_size = 0;

/* Helper to swap two request pointers */
static void swap_ptr(request_t **a, request_t **b) {
    request_t *tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Sift up: restores min-heap order upward after insertion */
static void sift_up(request_t **q, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (q[idx]->file_size < q[parent]->file_size) {
            swap_ptr(&q[idx], &q[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

/* Sift down: restores min-heap order downward after extracting root */
static void sift_down(request_t **q, int n, int idx) {
    while (2 * idx + 1 < n) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (q[left]->file_size < q[smallest]->file_size) {
            smallest = left;
        }
        if (right < n && q[right]->file_size < q[smallest]->file_size) {
            smallest = right;
        }

        if (smallest != idx) {
            swap_ptr(&q[idx], &q[smallest]);
            idx = smallest;
        } else {
            break;
        }
    }
}

/* Insert at index 'current_size' and sift up */
void min_queue_push(request_t **q, int current_size, request_t *req) {
    q[current_size] = req;
    sift_up(q, current_size);
}

/* Extract root, replace with last element, and sift down */
request_t *min_queue_pop(request_t **q, int current_size) {
    if (current_size <= 0) return NULL;

    request_t *min_req = q[0];
    int remaining = current_size - 1;

    if (remaining > 0) {
        q[0] = q[remaining];
        sift_down(q, remaining, 0);
    }
    return min_req;
}
