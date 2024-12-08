//
// Created by Luqman Setyo Nugroho on 07/12/24.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <block.h>


struct Block {
    char *filename;
    int blockNumber;
};

Block* Block_create(const char *filename, int blockNumber)
{
    Block *block = malloc(sizeof(Block));
    block->filename = strdup(filename);
    block->blockNumber = blockNumber;

    return block;
}

void Block_destroy(Block *block) {
    free(block->filename);
    free(block);
}

const char* Block_filename(Block *block) {
    return block->filename;
}

int Block_number(Block *block) {
    return block->blockNumber;
}

int Block_equals(Block *block1, Block *block2) {
    return strcmp(block1->filename, block2->filename) == 0 && block1->blockNumber == block2->blockNumber;
}

void Block_toString(Block *block, char* buffer) {
    snprintf(buffer, 256, "[main.file %s, block %d]", block->filename, block->blockNumber);
}

int Block_hashCode(Block *block) {
    char *str = malloc(256);
    Block_toString(block, str);

    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = 31 * hash + str[i];
    }
    free(str);
    return hash;
}
