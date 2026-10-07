#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define HEAP_INCREASE 256
#define BLOCK_SIZE (HEAP_INCREASE / 2)

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BLOCK_SIZE];
  ssize_t len = snprintf(buf, BLOCK_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  write(STDOUT_FILENO, buf, len);
}

int main(void) {
  void *heap = sbrk(HEAP_INCREASE); // gives address of old break

  struct header *first = heap;
  struct header *second = first + (BLOCK_SIZE / sizeof(struct header));

  first->size = BLOCK_SIZE;
  first->next = NULL;
  second->size = BLOCK_SIZE;
  second->next = first;

  size_t data_size = BLOCK_SIZE - sizeof(struct header);

  char *first_data = (char *)(first + 1);
  char *second_data = (char *)(second + 1);

  memset(first_data, 0, data_size);
  memset(second_data, 1, data_size);

  print_out("first block:        %p\n", &first, sizeof(&first));
  print_out("second block:       %p\n", &second, sizeof(&second));
  print_out("first block size:   %d\n", &first->size, sizeof(&first->size));
  print_out("first block next:   %p\n", &first->next, sizeof(&first->next));
  print_out("second block size:  %d\n", &second->size, sizeof(&second->size));
  print_out("second block next:  %p\n", &second->next, sizeof(&second->next));

  for (size_t i = 0; i < data_size; i++) {
    print_out("%hhu\n", &first_data[i], sizeof(&first_data[i]));
  }

  for (size_t i = 0; i < data_size; i++) {
    print_out("%hhu\n", &second_data[i], sizeof(&second_data[i]));
  }
}
