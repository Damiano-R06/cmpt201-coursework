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

  printf("first block:        %p\n", (void *)first);
  printf("second block:       %p\n", (void *)second);
  printf("first block size:   %d\n", (int)first->size);
  printf("first block next:   %p\n", (void *)first->next);
  printf("second block size:  %d\n", (int)second->size);
  printf("second block next:  %p\n", (void *)second->next);

  for (size_t i = 0; i < data_size; i++) {
    printf("%d\n", first_data[i]);
  }

  for (size_t i = 0; i < data_size; i++) {
    printf("%d\n", second_data[i]);
  }
}
