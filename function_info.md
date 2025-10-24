# Cub3D — Function & Math Reference

A concise, clean reference for MiniLibX (MLX) usage, math helpers, constants, core data structures, and the full execution flow of the engine.

## MLX (MiniLibX) API

### mlx_init(void)

- Purpose: Initialize the MLX graphics system by connecting to the X11 display server and allocating the internal MLX context used by all subsequent calls.
- Parameters: None
- Returns: void\* — MLX context handle; NULL on failure (e.g., DISPLAY not set, X server unavailable).
- Detailed description: This must be the first MLX call. Internally, it opens a connection to the running X server and prepares resources. If it fails, you cannot create windows or images. Common failure reasons include missing GUI environment, invalid DISPLAY, or permission issues when running remotely.
- Side effects: Opens an X11 connection that remains active for the process lifetime.
- Threading: MLX is not thread-safe; call MLX APIs from the main thread.
- Example:
  - `void *mlx = mlx_init(); if (!mlx) { /* handle error & exit */ }`

### mlx_new_window(void *mlx_ptr, int width, int height, char *title)

- Purpose: Create a top-level X11 window that will display your rendered frames.
- Parameters:
  - mlx_ptr: MLX context returned by `mlx_init()`; must be non-NULL.
  - width: Positive window width in pixels (e.g., 1200).
  - height: Positive window height in pixels (e.g., 800).
  - title: Null-terminated C string to show in the window title bar.
- Returns: void\* — window handle; NULL on failure (invalid context, out of resources).
- Detailed description: Allocates a window and registers it with the window manager. You should keep this handle to register input hooks and to present frames. On Linux, closing the window via the WM triggers event 17 (DestroyNotify); hook it to cleanly exit.
- Pitfalls: Creating many windows increases resource usage. Fullscreen isn’t directly supported; use a large window instead.
- Example:
  - `void *win = mlx_new_window(mlx, 1200, 800, "Cub3D"); if (!win) { /* handle error */ }`

### mlx_new_image(void \*mlx_ptr, int width, int height)

- Purpose: Create an off-screen image (framebuffer) that you draw into before presenting to the window.
- Parameters:
  - mlx_ptr: MLX context.
  - width: Positive image width in pixels.
  - height: Positive image height in pixels.
- Returns: void\* — image handle; NULL on failure (invalid args or memory/graphics resource exhaustion).
- Detailed description: The created image is typically CPU-backed and accessible via `mlx_get_data_addr()`. You draw your entire frame into this buffer each loop, then copy it to the window in a single call to avoid flicker and improve performance.
- Performance: Prefer a persistent image reused every frame. Avoid `mlx_pixel_put` in tight loops — direct buffer writes are faster.
- Example:
  - `void *img = mlx_new_image(mlx, 1200, 800);`

### mlx_get_data_addr(void *img_ptr, int *bpp, int *line_len, int *endian)

- Purpose: Obtain the raw pixel buffer pointer and layout metadata for an MLX image so you can write pixels directly.
- Parameters:
  - img_ptr: Image handle from `mlx_new_image()` or a loaded image; non-NULL.
  - bpp: OUT — bits per pixel (commonly 32). Compute bytes per pixel as `bpp/8`.
  - line_len: OUT — number of bytes in one scanline (stride). May exceed `width * (bpp/8)` due to padding.
  - endian: OUT — 0 for little-endian, non-zero for big-endian storage of multi-byte pixels.
- Returns: char\* — pointer to the first byte of the image buffer; NULL on error.
- Detailed description: Pixel address for (x,y) is `addr + y * line_len + x * (bpp/8)`. MLX on Linux often uses 32-bit pixels in BGRA/ARGB order — verify channel order before composing colors.
- Safety: Always bounds-check x,y; out-of-bounds writes corrupt memory.
- Example:
  - `char *addr = mlx_get_data_addr(img, &bpp, &stride, &endian);`

### mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void \*img_ptr, int x, int y)

- Purpose: Copy (blit) the pixels of an image into the target window at the given top-left offset.
- Parameters:
  - mlx_ptr: MLX context.
  - win_ptr: Destination window created by `mlx_new_window()`.
  - img_ptr: Source image created by `mlx_new_image()` or via a loader (e.g., XPM).
  - x, y: Destination position (top-left) inside the window.
- Returns: int — typically 0 on success; non-zero on failure (treat any non-zero as error).
- Detailed description: Present your completed frame by blitting the off-screen image buffer to the screen. The image remains valid after the call and can be reused for the next frame.
- Pitfalls: Ensure all handles belong to the same MLX context.
- Example:
  - `mlx_put_image_to_window(mlx, win, img, 0, 0);`

### mlx_hook(void *win_ptr, int event, int mask, int (*f)(), void \*param)

- Purpose: Register a callback for a specific X11 event on a window (keyboard, mouse, close, etc.).
- Parameters:
  - win_ptr: Window handle to receive events.
  - event: X11 event type (common: 2 = KeyPress, 3 = KeyRelease, 17 = DestroyNotify/close).
  - mask: Event mask enabling delivery (e.g., `1L<<0` for KeyPress; `1L<<1` for KeyRelease). For 17, mask is often 0.
  - f: Callback pointer. For key events: `int f(int keycode, void *param)`. For DestroyNotify, some MLX builds call `int f(void *param)`.
  - param: User data forwarded to the callback.
- Returns: int — 0 on success (varies by implementation). Treat non-zero as failure.
- Detailed description: Without the correct mask, your callback won’t fire. Use this to toggle input flags on press/release and to handle window close (event 17) to clean up and exit.
- Example:
  - `mlx_hook(win, 2, 1L<<0, key_press, data);`
  - `mlx_hook(win, 3, 1L<<1, key_release, data);`
  - `mlx_hook(win, 17, 0, close_window, data);`

### mlx_loop_hook(void *mlx_ptr, int (*f)(), void \*param)

- Purpose: Register a function to run every MLX loop iteration (your per-frame update).
- Parameters:
  - mlx_ptr: MLX context.
  - f: Callback function (commonly `int f(void *param)`); return value is generally ignored.
  - param: User data (engine state pointer, etc.).
- Returns: int — 0 on success (may vary across MLX builds).
- Detailed description: Ideal place to poll input flags, update physics, clear the image, render the 3D scene and minimap, then present with `mlx_put_image_to_window()`.
- Example:
  - `mlx_loop_hook(mlx, update_loop, data);`

### mlx_loop(void \*mlx_ptr)

- Purpose: Enter the MLX main loop to dispatch events and repeatedly call your loop hook.
- Parameters: `mlx_ptr` — MLX context created by `mlx_init()`.
- Returns: int — implementation-defined exit status (most apps do not use it).
- Detailed description: This function blocks and processes X11 events (keyboard, mouse, expose, destroy). Set up all hooks before calling it. To terminate, handle the close event or call `exit()` from a callback.
- Example:
  - `mlx_loop(mlx);`

### mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height)

- Purpose: Load an XPM file from disk and create an MLX image usable as a texture.
- Parameters:
  - mlx_ptr: MLX context.
  - filename: Path to a valid `.xpm` file.
  - width, height: OUT — receive the loaded image’s width and height in pixels.
- Returns: void\* — image handle; NULL on failure (file not found, invalid XPM, out of memory).
- Detailed description: After loading, get pixel access via `mlx_get_data_addr()` for sampling during textured wall rendering. Transparency in XPM (if present) may need special handling depending on your blending approach.
- Example:
  - `void *tex = mlx_xpm_file_to_image(mlx, "textures/wood.xpm", &w, &h);`

## Math Library (math.h)

- cos(double angle): cosine of an angle (radians).

  - Parameters: `angle` in radians (ℝ). If you have degrees, convert: `r = deg * M_PI / 180.0`.
  - Returns: `double` in [-1, 1].
  - Notes: Stable across wide ranges; periodic with 2π. Combine with `sin` for unit direction vectors.
  - Used in: X component of forward/strafe movement; fisheye correction; ray directions.
  - Example: `new_x = player_x + cos(player_angle) * speed;`

- sin(double angle): sine of an angle (radians).

  - Parameters: `angle` in radians.
  - Returns: `double` in [-1, 1].
  - Notes: Periodic with 2π. Together with `cos`, gives a unit vector `(cos a, sin a)`.
  - Used in: Y component of movement; ray direction; rotating vectors.
  - Example: `new_y = player_y + sin(player_angle) * speed;`

- tan(double angle): tangent function = `sin(angle)/cos(angle)`.

  - Parameters: `angle` ∈ ℝ \ `{π/2 + kπ}` (points of discontinuity).
  - Returns: `double` potentially very large near discontinuities.
  - Edge cases: Avoid exact `π/2 + kπ` to prevent division by zero; clamp angles slightly off the singularities when computing intersections.
  - Used in: Horizontal/vertical intercept math when casting rays on a grid.
  - Example: `x = px + (y - py) / tan(ray_angle);`

- fmod(double x, double y): floating-point remainder `x - trunc(x/y) * y`.

  - Parameters: `y != 0`.
  - Returns: Remainder with the same sign as `x`; magnitude `< |y|`.
  - Edge cases: If `y == 0`, result is NaN. For texture mapping, ensure positive wrap: `u = fmod(val, TS); if (u < 0) u += TS;`.
  - Used in: Wrapping hit coordinates into `[0, TS)` for texture sampling.
  - Example: `double u = fmod(hit_x, TS); if (u < 0) u += TS; tex_x = u * tex_w / TS;`

- hypot(double x, double y): Robust Euclidean distance `sqrt(x*x + y*y)`.

  - Parameters: finite doubles; handles large magnitudes safely.
  - Returns: Non-negative `double` — vector length.
  - Advantages: Avoids overflow/underflow better than manual `sqrt` of squares.
  - Used in: Player-to-hit distance; length of displacement vectors.
  - Example: `dist = hypot(hit_x - px, hit_y - py);`

- atan2(double y, double x): Angle of vector (x, y) with correct quadrant.

  - Parameters: `x, y` finite doubles (both 0 returns 0 or implementation-defined small value).
  - Returns: Angle in radians in (-π, π]; continuous across axes.
  - Used in: Computing facing angle to targets; normalizing ray/player angles.
  - Example: `angle = atan2(target_y - py, target_x - px);`

- sqrt(double x): Non-negative square root.

  - Parameters: `x >= 0` for real result; negative returns NaN.
  - Returns: `double` ≥ 0.
  - Used in: Distance formulas (prefer `hypot` for two-component vectors).
  - Example: `dist = sqrt(dx * dx + dy * dy);`

- floor(double x): Round down to the greatest integer ≤ x (returned as `double`).

  - Parameters: finite double.
  - Returns: `double` integral value; cast to `int` for indices.
  - Used in: Converting world coordinates to tile indices; ensure bounds checks.
  - Example: `map_x = (int)floor(world_x / TS);`

- ceil(double x): Round up to the smallest integer ≥ x (returned as `double`).
  - Parameters: finite double.
  - Returns: `double` integral value; cast to `int` for pixel limits.
  - Used in: Ensuring coverage when computing draw end coordinates.
  - Example: `end_pix = (int)ceil(wall_end);`

## C Runtime Utilities

- abs(int x): absolute value (stdlib.h)

  - Parameters: any signed 32-bit int.
  - Returns: Non-negative int equal to |x|.
  - Edge cases: `abs(INT_MIN)` may overflow (two’s complement) and is undefined/implementation-defined. Prefer `labs(long)` / `llabs(long long)` for wider ranges.
  - Used in: Manhattan distances, difference magnitudes, clamping logic.

- malloc(size_t size): allocate dynamic memory (stdlib.h)

  - Parameters: `size` bytes to allocate. `size==0` may return NULL or a unique pointer; don’t dereference without checking.
  - Returns: `void*` pointer to uninitialized memory; NULL on failure.
  - Best practices: Always NULL-check; zero-initialize explicitly if required (`ft_bzero`/`calloc`). Keep ownership clear to avoid leaks.
  - Used in: Map buffers, arrays of texture structs, engine state.

- free(void \*ptr): free allocated memory (stdlib.h)

  - Parameters: `ptr` previously returned by an allocator; NULL is allowed (no-op).
  - Returns: void.
  - Best practices: After `free(ptr)`, set `ptr = NULL` to avoid use-after-free. Do not double-free.
  - Used in: Cleanup on normal exit and error paths; texture/map teardown.

- memset(void \*ptr, int value, size_t num): fill memory (string.h)
  - Parameters: `ptr` destination; `value` replicated as a byte; `num` number of bytes.
  - Returns: `void*` — the destination pointer.
  - Performance: Optimized in libc; ideal for clearing image buffers each frame (e.g., fill with 0 for black). For MLX images, verify pixel format if relying on alpha.
  - Used in: Clear frame buffer, initialize arrays/structs to a known state.

## Key Constants and Math Details

- TS (Tile Size): 64 — pixels per map cell
- FOV: 1.0 radians (≈ 57.3°)
- SCREEN_WIDTH: 1200 — also number of rays (per column)
- SCREEN_HEIGHT: 800
- MOVE_SPEED: 2.0 — pixels per frame
- ROT_SPEED: 0.02 — radians per frame

Math used:

- Ray casting:
  - Horizontal intercept: `x = px + (y - py) / tan(angle)`
  - Vertical intercept: `y = py + (x - px) * tan(angle)`
  - Distance: `hypot(hit_x - px, hit_y - py)`
  - Fisheye correction: `dist * cos(ray_angle - player_angle)`
- 3D projection:
  - Wall height: `(TS * SCREEN_HEIGHT) / distance`
  - Texture X: `fmod(hit_coord, TS) * tex_w / TS`
  - Texture step: `tex_h / wall_h`
  - Texture Y: `(int)tex_pos % tex_h`
- Movement:
  - Forward: `x += cos(angle) * speed`, `y += sin(angle) * speed`
  - Strafe: use `angle ± π/2`
  - Rotation: `angle += delta`
- Minimap:
  - Screen X: `(world_x - px) / scale + cx`
  - Screen Y: `(world_y - py) / scale + cy`
  - Scale factor: `TS / SCALE_FACTOR (64/8 = 8)`

## Performance Notes

- Raycasting performance:
  - Time: O(n × m), n = screen width (rays), m = avg ray length (grid steps)
  - Space: O(1)
  - Rays per frame: ≈ 1200; average steps: ~10–20
- Rendering:
  - Pixels/frame: 1200 × 800 = 960,000
  - Texture samples: ~400,000 (wall pixels)
  - Memory writes: ~3.84 MB/frame (@ 4 bytes/pixel)
  - Target: 60 FPS (~16.67 ms/frame)
- Optimizations:
  - DDA grid traversal, fisheye correction, texture preloading, direct pixel writes, early stop on wall hit

## Core Data Structures (conceptual)

- t_data — Main Game State

  - map: `char**` — 2D map array ('1' wall, '0' empty, 'N/S/E/W' spawn)
  - player: `t_player` — position and angle
  - mlx_ptr, win_ptr: MLX handles
  - img: image handle; img_adr: `char*` — direct pixel buffer
  - tex[4]: `t_tex` — textures (N/S/E/W)
  - floor, ceiling: `t_color` — RGB colors
  - input: `t_input` — current input flags
  - rows, cols: map dimensions

- t_player — Player State

  - fpx, fpy: `double` — precise position
  - x, y: `int` — grid/integer position (for collision)
  - angle: `double` — radians (0 = East, π/2 = South)

- t_hit — Ray Hit Info

  - dist: `double` — distance to wall
  - hit_x, hit_y: `double` — intersection point
  - is_vertical: `int` — 1 = vertical wall, 0 = horizontal
  - tex_id: `int` — 0=N, 1=S, 2=E, 3=W
  - ray_angle: `double` — angle of the ray

- t_input — Input State

  - k_up, k_down: `int` — forward/back
  - k_left, k_right: `int` — rotate
  - k_view_left, k_view_right: `int` — strafe

- t_tex — Texture Data

  - img: image handle; addr: `char*` — raw pixels
  - width, height: `int`
  - bpp, line_len: `int`

- t_color — RGB Color
  - r, g, b: `int` (0–255)
  - Hex: `(r << 16) | (g << 8) | b`

## Execution Flow

1. Program Startup (main.c)

- Parse command line arguments
- `parce()` to read/validate `.cub` file
- `start()` with parsed map data
- Exit and cleanup

2. Engine Initialization (start.c)

- `init_data_from_map()`
- Create MLX context, window, and image
- `mlx_loop()` starts event handling

3. Data Setup (1_init.c)

- `extract_map_from_parsed_data()` → 2D array
- `count_map_dimensions()` → map size
- `mlx_init()` → graphics library
- `mlx_new_window()` → display window
- `mlx_new_image()` → image buffer
- `init_player_pos()` → spawn point/direction
- Setup hooks: `key_press`, `key_release`, `mouse_move`, `close_window`
- `init_textures()` → load wall textures
- `mlx_loop_hook(update_loop)` → register main loop

4. Game Loop (5_update_player_pos.c)

- `handle_movement()` — WASD input
- `handle_rotation()` — arrows/mouse
- `clear_img()` — reset image buffer
- `draw_3d()` — render scene
- `draw_minimap()` — overlay
- `mlx_put_image_to_window()` — display frame

5. Input Processing (4_input.c)

- `key_press()` set flags = 1
- `key_release()` set flags = 0
- `mouse_move()` update angle
- `close_window()` cleanup and exit

6. Movement Processing (5_update_player_pos.c)

- Check flags (k_up, k_down, k_view_left, k_view_right)
- Compute movement angle (forward/back/strafe)
- `move(angle)` computes new position via trig
- `is_wall()` collision check before commit
- Update `player.fpx`, `player.fpy` if safe

7. 3D Rendering (7_draw_3d.c)

- Ray step: `FOV / SCREEN_WIDTH`
- Start: `player.angle - FOV/2`
- For x in [0..SCREEN_WIDTH-1]:
  - `get_distance()` cast ray
  - Fisheye: `dist *= cos(ray_angle - player_angle)`
  - Determine texture ID by face
  - `draw_wall_3d()` render column
  - Increment angle

8. Raycasting (6_get_distance.c)

- `get_horizontal_intercept()` — first horiz grid
- `get_vertical_intercept()` — first vert grid
- Step through grid via `get_next_intercept()`
- `is_wall()` check at each intersection
- Distances by `hypot()`; return closest `t_hit`

9. Wall Rendering (7_draw_3d.c)

- Wall height: `(TS * SCREEN_HEIGHT) / distance`
- Draw bounds: start/end on screen
- Draw ceiling color
- Texture coordinates (tex_x, tex_step, tex_y)
- For each wall pixel: sample texture and `my_mlx_pixel_put()`
- Draw floor color

10. Minimap (2_draw_2D_map.c)

- For each map tile:
  - Screen position relative to player
  - Check if inside minimap bounds
  - Draw square (wall vs empty)
- `draw_player()` — red dot at center

11. Frame Display

- `mlx_put_image_to_window()` blit framebuffer
- Loop continues at target ~60 FPS

---

Notes:

- Replace file/function names if your project uses different naming.
- Ensure `-lm` is linked for math functions (cos, sin, tan, fmod, hypot, atan2, sqrt, floor, ceil).
