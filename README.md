# Malloc

The objective of the project is to faithfully recreate the malloc system of the library standard C.
This repository, contains the complete project code and many tests.
The project’s difficulty comes from using the 'MMAP' function and creating three stacks.

Bonuses done

- Memory Hexdump. (show_alloc_mem_ex)
- Thread Safe functions.
- Memory défragmentation.

## Usage

- Clone Repository
```bash
git clone https://github.com/vvaucoul/Malloc && cd Malloc
```

- Compilation
```bash
make
```

- Tests Compilation
```bash
make tests
```

> Replace Malloc system (pay attention to this one)
```bash
#!/bin/sh
export LD_LIBRARY_PATH=$PWD
export LD_INSERT_LIBRARIES="libft_malloc.so"
export LD_FORCE_FLAT_NAMESPACE=1
$@
```

## Functions

```C
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void show_alloc_mem(void);
void show_alloc_mem_ex(void);
```

## Ressources

- [GetPageSize](https://man7.org/linux/man-pages/man2/getpagesize.2.html)
- [MMAP](https://man7.org/linux/man-pages/man2/mmap.2.html)
- [Medium - Malloc](https://medium.com/a-42-journey/how-to-create-your-own-malloc-library-b86fedd39b96)
- [TechFacts](https://tharikasblogs.blogspot.com/p/how-to-write-your-own-malloc-and-free.html) 
