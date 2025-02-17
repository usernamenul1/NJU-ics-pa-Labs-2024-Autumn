#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);
uint32_t mem_uncache_read(uintptr_t addr);
void mem_uncache_write(uintptr_t addr, uint32_t data, uint32_t wmask);

static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions

uint32_t cache_read(uintptr_t addr) {
  return mem_uncache_read(addr);
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
  mem_uncache_write(addr, data, wmask);
}

void init_cache(int total_size_width, int associativity_width) {}

void display_statistic(void) {}
