/*!
 * policy.c - policy functions for mako
 * Copyright (c) 2021, Christopher Jeffrey (MIT License).
 * https://github.com/chjj/mako
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <mako/policy.h>
#include "internal.h"

/*
 * Policy
 */

int64_t
btc_get_min_fee(size_t size, int64_t rate) {
  int64_t fee;

  CHECK(rate >= 0);

  if (size == 0)
    return 0;

  fee = (rate * (int64_t)size) / 1000;

  if (fee == 0 && rate > 0)
    fee = rate;

  return fee;
}

int64_t
btc_get_round_fee(size_t size, int64_t rate) {
  int64_t fee;

  CHECK(rate >= 0);

  if (size == 0)
    return 0;

  fee = rate * (((int64_t)size + 1000 - 1) / 1000);

  if (fee == 0 && rate > 0)
    fee = rate;

  return fee;
}

int64_t
btc_get_rate(size_t size, int64_t fee) {
  CHECK(fee >= 0);

  if (size == 0)
    return 0;

  return (fee * 1000) / (int64_t)size;
}
