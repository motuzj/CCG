// inspired by https://curl.se/libcurl/c/getinmemory.html and https://stackoverflow.com/a/5525631
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "network.h"

typedef struct {
    char *memory;
    size_t size;
} memory;

static size_t write_to_string(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    memory *mem = (memory *) userdata;

    char *new_mem = realloc(mem->memory, mem->size + realsize + 1);
    if (!new_mem) {
        fprintf(stderr, "Error: Not enough memory\n");
        return 0;
    }

    mem->memory = new_mem;
    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size = realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char *get_json(const char *url) {
    CURLcode ret;
    CURL *hnd;

    memory pagedata;

    pagedata.memory = malloc(1);
    pagedata.size = 0;

    hnd = curl_easy_init();
    //curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(hnd, CURLOPT_URL, url);
    //curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/8.2.1");
    curl_easy_setopt(hnd, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
    //curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
    //curl_easy_setopt(hnd, CURLOPT_FTP_SKIP_PASV_IP, 1L);
    curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &pagedata);

    ret = curl_easy_perform(hnd);

    curl_easy_cleanup(hnd);
    hnd = NULL;

    return pagedata.memory;
}
