//
// Created by Ashwin Paudel on 2021-06-04.
//

#ifndef KRIPAYAOS_MEMORY_H
#define KRIPAYAOS_MEMORY_H

#include <Kernel/Common.h>
#include <Drivers/Display.h>



void memory_copy(uint8_t *source, uint8_t *dest, uint32_t nbytes);

void init_dynamic_mem();

void print_dynamic_node_size();

void print_dynamic_mem();

void *mem_alloc(size_t size);

void mem_free(void *p);

#endif //KRIPAYAOS_MEMORY_H
