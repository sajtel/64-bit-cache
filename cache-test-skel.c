/*
Part 1 - Mystery Caches
*/

#include <stdlib.h>
#include <stdio.h>

#include "support/mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  int size  = 0;
  flush_cache();
  access_cache(0);
  while(access_cache(size)){

    size++;

  }

  return size;

}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  int x = 0;
  int index = 0;

  while(1){
    flush_cache();
    access_cache(x);

    int iterator = 1;

    while(iterator <= index){

      access_cache(iterator*block_size);
      iterator++;

    }

    if(access_cache(x)){

      index++;

    }else{

      break;

    }

  }

  return index*block_size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  /* YOUR CODE GOES HERE */
  int associativity = 0;
  int x = 0;

  flush_cache();
  access_cache(x);

  while(access_cache(x)){

    flush_cache();
    access_cache(x);

    int iterator = 1;

    while(iterator <= associativity+1){
      access_cache(iterator*cache_size);
      iterator++;
    }

    associativity++;

  }
  
  return associativity;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0, 0);

  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
