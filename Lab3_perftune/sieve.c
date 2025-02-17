#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define N 10000000

static bool is_prime[N];
static int primes[N];

int *sieve(register int n) {
  if (n < 2) {
    return primes;
  }
  register int ret = 0;
  int temp;
  primes[ret++] = 2;
  for (register int i = 3; i <= n; i += 2) {
    if (!is_prime[i]) {
      primes[ret++] = i;
    }
    temp = n / i;
    for (register int j = 0; primes[j] <= temp && j < ret; j++) {
      is_prime[primes[j] * i] = true;
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
  return primes;
}
