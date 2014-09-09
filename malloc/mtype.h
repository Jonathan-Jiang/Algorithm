#ifndef MTYPE_H
#define MTYPE_H

typedef struct s_block* m_block_ptr;
struct m_block {
    size_t size;    // size of this block
    m_block_ptr prev;   // pointer to previous block
    m_block_ptr next;   // pointer to next block
    int is_free;  // this block is free or not
    void* m_ptr;  // magic pointer, point to data
    char data[1];   // first byte of this block
};

struct m_block2 {
    size_t size;    // size of this block
    m_block_ptr prev;   // pointer to previous block
    m_block_ptr next;   // pointer to next block
    char is_free;  // this block is free or not
    char padding[3]; // 3 bytes padding for memory alignment
    void* m_ptr;  // magic pointer, point to data
    char data[1];   // first byte of this block
};

#endif
