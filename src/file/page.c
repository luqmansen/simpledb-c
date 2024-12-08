//
// Created by Luqman Setyo Nugroho on 08/12/24.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "file/page.h"


struct Page {
  char *data;
  size_t size;
};

Page* Page_create_from_bytes(const char *bytes, size_t size) {

  Page *page = malloc(sizeof(Page));
  page->data = malloc(size);
  memcpy(page->data, bytes, size);
  page->size = size;

  return page;
}

Page* Page_create_with_size(size_t blockSize) {
  Page* page = malloc(sizeof(Page));
  page->data = malloc(blockSize);
  page->size = blockSize;


  return page;
}

void Page_destroy(Page *page) {
  free(page->data);
  free(page);
}

int Page_get_int(Page *page, size_t offset) {
  int value;
  memcpy(&value, page->data + offset, sizeof(int));
  return value;
}

void Page_set_int(Page *page, size_t offset, int value) {

  memcpy(page->data + offset, &value, sizeof(int));
}

char* Page_get_bytes(Page *page, size_t offset, size_t *length) {
  int len;

  // copy the length of the wanted bytes
  memcpy(&len, page->data + offset, sizeof(int));
  // make sure it's not exceeding the page size
  assert(len <= page->size - offset - sizeof(int));
  *length = len; // set the output length

  char *bytes = malloc(len);
  memcpy(bytes, page->data + offset + sizeof(int), len);
  return bytes;
}

void Page_set_bytes(Page *page, size_t offset, const char *bytes, size_t length) {
  memcpy(page->data + offset, &length, sizeof(int));

  // char *address = page->data +offset + sizeof(int);
  memcpy(page->data +offset + sizeof(int), bytes, length);
}

int Page_max_length(int strlen) {
  return strlen + sizeof(int);
}

char* Page_get_string(Page *page, size_t offset) {
  size_t length;
  char *bytes = Page_get_bytes(page, offset, &length);
  //In C, strings are null-terminated, meaning they end with
  //a special null character ('\0'). When you allocate memory
  //for a string, you need to allocate an extra byte to store
  //this null terminator. This ensures that functions that
  //operate on strings, such as strlen and printf, can correctly
  //identify the end of the string.
  char *str = malloc(length + 1);
  memcpy(str, bytes, length);
  str[length] = '\0'; // Adds null terminator

  free(bytes);

  return str;
}

void Page_set_string(Page *page, size_t offset, const char *value_str) {
  size_t length = strlen(value_str);
  Page_set_bytes(page, offset, value_str, length);
}

char *Page_contents(Page *page) {
  char *contents = malloc(page->size);
  memcpy(contents, page->data, page->size);

  return contents;
}