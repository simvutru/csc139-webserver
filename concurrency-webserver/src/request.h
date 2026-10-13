#ifndef __REQUEST_H__
#define MAXBUF (8192)

typedef struct {
    int conn_fd;
    int file_size;
    int is_static;
    char filename[MAXBUF];
    char cgiargs[MAXBUF];
} request_t;

void init_request(request_t *req);
void request_handle(request_t *req);
int parse_request_metadata(request_t *req); // parse request's metadata
#endif // __REQUEST_H__
