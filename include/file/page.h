//
// Created by Luqman Setyo Nugroho on 08/12/24.
//

#ifndef PAGE_H
#define PAGE_H

#endif //PAGE_H

typedef struct Page Page;

Page* Page_create_from_bytes(const char *bytes, size_t size);
Page* Page_create_with_size(size_t blockSize);
void Page_destroy(Page *page);
int Page_get_int(Page *page, size_t offset);
void Page_set_int(Page *page, size_t offset, int value);
char* Page_get_bytes(Page *page, size_t offset, size_t *length) ;
void Page_set_bytes(Page *page, size_t offset, const char *bytes, size_t length);
char* Page_get_string(Page *page, size_t offset);
void Page_set_string(Page *page, size_t offset, const char *value_str);
char *Page_contents(Page *page);