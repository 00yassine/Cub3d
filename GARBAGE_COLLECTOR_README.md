# Garbage Collector Implementation

## Overview

This project now uses a garbage collector system to manage all dynamic memory allocations, eliminating manual `free()` calls and preventing memory leaks.

## How It Works

### Core Function

```c
void *gc_malloc(size_t size, int mode);
```

**Parameters:**

- `size`: Size of memory to allocate (in bytes)
- `mode`:
  - `1` = Allocate memory and track it
  - `0` = Free all tracked memory

### Usage Examples

#### Allocating Memory

```c
// Instead of: char *str = malloc(100);
char *str = gc_malloc(100, 1);
```

#### Freeing All Memory

```c
// At program exit or cleanup
gc_malloc(0, 0);
```

## Files Modified

1. **src/garbage_collector.c** - NEW

   - Contains garbage collector implementation
   - Maintains linked list of all allocations

2. **includes/cub3d.h**

   - Added `t_gc_node` structure
   - Added `gc_malloc()` and `gc_free_all()` prototypes

3. **src/raycasting/src/1_init.c**

   - `extract_map_from_parsed_data()`: Uses `gc_malloc()` for map array
   - `fill_map_array()`: Uses `gc_malloc()` for map lines

4. **src/parsing/parce_the_map.c**

   - `parce()`: Uses `gc_malloc()` for t_map structure

5. **src/parsing/parsing_helper.c**

   - `ft_str_take()`: Uses `gc_malloc()` for texture paths

6. **main.c**

   - `load_map_from_file()`: Uses `gc_malloc()` for file content array
   - `main()`: Calls `gc_malloc(0, 0)` at exit

7. **src/cleanup.c**

   - `cleanup_data()`: Calls `gc_malloc(0, 0)` to free all memory
   - `cleanup_map()`: Calls `gc_malloc(0, 0)` to free all memory

8. **get_next_line/get_next_line.c**
   - All internal allocations now use `gc_malloc()`
   - `ft_joinfree()`, `ft_get_line()`, `ft_get_next()`, `read_file()` updated

## Memory Leak Results

### Before Garbage Collector

```
LEAK SUMMARY:
   definitely lost: 1,211 bytes in 39 blocks
```

### After Garbage Collector

```
LEAK SUMMARY:
   definitely lost: 0 bytes in 0 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 31,759 bytes in 400 blocks (X11/MLX libraries)
```

## Benefits

1. **No Memory Leaks**: All allocations are automatically tracked and freed
2. **Simplified Code**: No need for manual `free()` calls
3. **Error Recovery**: On error, call `gc_malloc(0, 0)` to clean everything
4. **Centralized Management**: All memory is managed in one place

## Important Notes

- The "still reachable" memory (31,759 bytes) is from X11 and MLX libraries, which is normal
- Always call `gc_malloc(0, 0)` before program exit
- Mode `1` = allocate, Mode `0` = free all
- Do not mix regular `malloc()` with `gc_malloc()` for tracked allocations

## Testing

Run valgrind to verify:

```bash
valgrind --leak-check=full --show-leak-kinds=definite,indirect,possible ./cub3d maps/map.cub
```

Expected result: **0 bytes definitely lost**
