/*
 * File:   rpl_instance.h
 * Author: am
 *
 * Created on June 21, 2013, 11:50 AM
 */

#ifndef RPL_INSTANCE_H
#define	RPL_INSTANCE_H

#include <stdbool.h>
#include <stdint.h>
#include "hash_container.h"

typedef struct di_dodag di_dodag_t;

typedef enum tag_di_rpl_mop_e {
	RDMOP_NoDownwardRoute,
	RDMOP_NonStoring,
	RDMOP_StoringWithoutMulticast,
	RDMOP_StoringWithMulticast
} di_rpl_mop_e;

typedef struct {
	int16_t rpl_instance;				//Via DIO, DAO
} di_rpl_instance_ref_t;

typedef struct di_rpl_instance_key {
	di_rpl_instance_ref_t ref;
	uint32_t version;
} di_rpl_instance_key_t;

typedef struct di_rpl_instance di_rpl_instance_t;

size_t rpl_instance_sizeof();

void rpl_instance_init(void* data, void *key, size_t key_size);
di_rpl_instance_t* rpl_instance_dup(di_rpl_instance_t* rpl_instance);

void rpl_instance_set_key(di_rpl_instance_t* rpl_instance, const di_rpl_instance_key_t* key);
void rpl_instance_set_mop(di_rpl_instance_t* rpl_instance, di_rpl_mop_e mop);
void rpl_instance_set_user_data(di_rpl_instance_t* rpl_instance, void *user_data);
void rpl_instance_add_dodag(di_rpl_instance_t* rpl_instance, di_dodag_t *dodag);
void rpl_instance_del_dodag(di_rpl_instance_t* rpl_instance, di_dodag_t *dodag);

const di_rpl_instance_key_t* rpl_instance_get_key(const di_rpl_instance_t* rpl_instance);
di_rpl_mop_e rpl_instance_get_mop(const di_rpl_instance_t* rpl_instance);
void *rpl_instance_get_user_data(const di_rpl_instance_t* rpl_instance);

#endif	/* RPL_INSTANCE_H */

