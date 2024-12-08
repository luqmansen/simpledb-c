#pragma once


#ifndef BLOCK_H
#define BLOCK_H

#endif

typedef struct Block Block;


Block* Block_create(const char *filename, int blockNumber);
void Block_destroy(Block *block);
const char* Block_filename(Block *block);
int Block_number(Block *block);
int Block_equals(Block *block1, Block *block2);
void Block_toString(Block *block, char* buffer);
int Block_hashCode(Block *block);