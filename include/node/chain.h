/*!
 * chain.h - chain for libsatoshi
 * Copyright (c) 2021, Christopher Jeffrey (MIT License).
 * https://github.com/chjj/libsatoshi
 */

#ifndef BTC_CHAIN_H
#define BTC_CHAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>
#include "timedata.h"
#include "../satoshi/common.h"
#include "../satoshi/types.h"

/*
 * Constants
 */

enum btc_chain_flags {
  BTC_CHAIN_VERIFY_NONE = 0,
  BTC_CHAIN_VERIFY_POW  = 1 << 0,
  BTC_CHAIN_VERIFY_BODY = 1 << 1,
  BTC_CHAIN_DEFAULT_FLAGS = BTC_CHAIN_VERIFY_POW | BTC_CHAIN_VERIFY_BODY
};

enum btc_lock_flags {
  BTC_CHAIN_VERIFY_SEQUENCE  = 1 << 0,
  BTC_CHAIN_MEDIAN_TIME_PAST = 1 << 1,
  BTC_CHAIN_MANDATORY_LOCKTIME_FLAGS = 0,
  BTC_CHAIN_STANDARD_LOCKTIME_FLAGS = BTC_CHAIN_VERIFY_SEQUENCE
                                    | BTC_CHAIN_MEDIAN_TIME_PAST
};

enum btc_threshold_state {
  BTC_CHAIN_DEFINED,
  BTC_CHAIN_STARTED,
  BTC_CHAIN_LOCKED_IN,
  BTC_CHAIN_ACTIVE,
  BTC_CHAIN_FAILED
};

/*
 * Types
 */

typedef struct btc_deployment_state_s {
  unsigned int flags;
  unsigned int lock_flags;
  int bip34;
  int bip91;
  int bip148;
} btc_deployment_state_t;

typedef struct btc_chain_s btc_chain_t;

typedef void btc_connect_cb(const btc_entry_t *entry,
                            const btc_block_t *block,
                            btc_view_t *view,
                            void *arg);

typedef void btc_reorganize_cb(const btc_entry_t *old,
                               const btc_entry_t *new_,
                               void *arg);

typedef void btc_badorphan_cb(const btc_verify_error_t *err, int id, void *arg);

/*
 * Chain
 */

BTC_EXTERN btc_chain_t *
btc_chain_create(const struct btc_network_s *network);

BTC_EXTERN void
btc_chain_destroy(btc_chain_t *chain);

BTC_EXTERN void
btc_chain_set_logfile(btc_chain_t *chain, FILE *stream);

BTC_EXTERN void
btc_chain_set_timedata(btc_chain_t *chain, const btc_timedata_t *td);

BTC_EXTERN void
btc_chain_on_connect(btc_chain_t *chain, btc_connect_cb *handler);

BTC_EXTERN void
btc_chain_on_disconnect(btc_chain_t *chain, btc_connect_cb *handler);

BTC_EXTERN void
btc_chain_on_reorganize(btc_chain_t *chain, btc_reorganize_cb *handler);

BTC_EXTERN void
btc_chain_on_badorphan(btc_chain_t *chain, btc_badorphan_cb *handler);

BTC_EXTERN void
btc_chain_set_context(btc_chain_t *chain, void *arg);

BTC_EXTERN void
btc_chain_set_checkpoints(btc_chain_t *chain, int value);

BTC_EXTERN int
btc_chain_open(btc_chain_t *chain, const char *prefix, size_t map_size);

BTC_EXTERN void
btc_chain_close(btc_chain_t *chain);

BTC_EXTERN const btc_verify_error_t *
btc_chain_error(btc_chain_t *chain);

BTC_EXTERN int
btc_chain_verify_locks(btc_chain_t *chain,
                       const btc_entry_t *prev,
                       const btc_tx_t *tx,
                       btc_view_t *view,
                       unsigned int flags);

BTC_EXTERN int
btc_chain_add(btc_chain_t *chain,
              const btc_block_t *block,
              unsigned int flags,
              int id);

BTC_EXTERN uint32_t
btc_chain_get_current_target(btc_chain_t *chain);

BTC_EXTERN uint32_t
btc_chain_get_target(btc_chain_t *chain,
                     int64_t time,
                     const btc_entry_t *prev);

BTC_EXTERN const uint8_t *
btc_chain_get_orphan_root(btc_chain_t *chain, const uint8_t *hash);

BTC_EXTERN btc_entry_t *
btc_chain_find_locator(btc_chain_t *chain, const btc_vector_t *locator);

#ifdef __cplusplus
}
#endif

#endif /* BTC_CHAIN_H */