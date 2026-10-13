#ifndef __QUEUE_H__

void min_queue_push(request_t **q, int current_size, request_t *req);
request_t *min_queue_pop(request_t **q, int current_size);
#endif // __QUEUE_H__
