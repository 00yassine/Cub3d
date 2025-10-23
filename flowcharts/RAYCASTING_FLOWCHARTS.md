# 🎨 Visual Raycasting Guide - Diagrams & Flowcharts

> **✨ NEW: Interactive SVG Flowcharts Available!**
> Professional, scalable flowcharts now available in the `flowcharts/` directory.
> Open `flowcharts/index.html` in your browser for an interactive experience!
>
> 📂 **SVG Files:**
>
> - `01_system_overview.svg` - Main loop visualization
> - `02_dda_algorithm.svg` - DDA ray casting algorithm
> - `03_texture_mapping.svg` - Texture rendering process
> - `04_problems_solutions.svg` - Common issues & fixes
> - `05_visualization.svg` - Complete raycasting scene
>
> 🌐 **View Online:** Open `flowcharts/index.html` in any browser
> 📖 **Documentation:** See `flowcharts/README.md` for details

---

## 📊 Complete System Flowchart (ASCII Version)

> 💡 **Tip:** For better visualization, check `flowcharts/01_system_overview.svg`

```
╔══════════════════════════════════════════════════════════════════════╗
║                     CUB3D RAYCASTING ENGINE                          ║
║                         Main Loop Flow                               ║
╚══════════════════════════════════════════════════════════════════════╝

                            ┌─────────┐
                            │  START  │
                            └────┬────┘
                                 │
                                 ▼
                    ┌────────────────────────┐
                    │   Initialize MLX       │
                    │   Load Textures        │
                    │   Setup Window         │
                    │   Parse Map            │
                    └────────────┬───────────┘
                                 │
                                 ▼
                    ┌────────────────────────┐
                    │   Setup Hooks:         │
                    │   • Key Press          │
                    │   • Key Release        │
                    │   • Mouse Move         │
                    │   • Window Close       │
                    │   • Loop Hook          │
                    └────────────┬───────────┘
                                 │
                                 ▼
         ╔═══════════════════════════════════════════════╗
         ║           MLX MAIN LOOP (60 FPS)              ║
         ║   ┌───────────────────────────────────────┐   ║
         ║   │                                       │   ║
         ║   │  1. INPUT PROCESSING                 │   ║
         ║   │  ┌─────────────────────────────────┐ │   ║
         ║   │  │ Check Input Flags               │ │   ║
         ║   │  │  • k_up, k_down (W/S)          │ │   ║
         ║   │  │  • k_left, k_right (arrows)    │ │   ║
         ║   │  │  • k_view_left/right (A/D)     │ │   ║
         ║   │  │  • speed (Shift)               │ │   ║
         ║   │  └─────────────┬───────────────────┘ │   ║
         ║   │                 │                      │   ║
         ║   │                 ▼                      │   ║
         ║   │  2. MOVEMENT UPDATE                   │   ║
         ║   │  ┌─────────────────────────────────┐ │   ║
         ║   │  │ Calculate New Position         │ │   ║
         ║   │  │  new_x = fpx + cos(θ)*speed   │ │   ║
         ║   │  │  new_y = fpy + sin(θ)*speed   │ │   ║
         ║   │  │                                 │ │   ║
         ║   │  │ ┌──────────────────────────┐   │ │   ║
         ║   │  │ │ Collision Check (X-axis) │   │ │   ║
         ║   │  │ │ if !is_wall(new_x, fpy)  │   │ │   ║
         ║   │  │ │    fpx = new_x ✓         │   │ │   ║
         ║   │  │ └──────────────────────────┘   │ │   ║
         ║   │  │                                 │ │   ║
         ║   │  │ ┌──────────────────────────┐   │ │   ║
         ║   │  │ │ Collision Check (Y-axis) │   │ │   ║
         ║   │  │ │ if !is_wall(fpx, new_y)  │   │ │   ║
         ║   │  │ │    fpy = new_y ✓         │   │ │   ║
         ║   │  │ └──────────────────────────┘   │ │   ║
         ║   │  └─────────────┬───────────────────┘ │   ║
         ║   │                 │                      │   ║
         ║   │                 ▼                      │   ║
         ║   │  3. ROTATION UPDATE                   │   ║
         ║   │  ┌─────────────────────────────────┐ │   ║
         ║   │  │ angle += ROT_SPEED * direction │ │   ║
         ║   │  │ Normalize to [0, 2π)           │ │   ║
         ║   │  └─────────────┬───────────────────┘ │   ║
         ║   │                 │                      │   ║
         ║   │                 ▼                      │   ║
         ║   │  4. CLEAR FRAME BUFFER                │   ║
         ║   │  ┌─────────────────────────────────┐ │   ║
         ║   │  │ memset(img_buffer, 0, size)    │ │   ║
         ║   │  └─────────────┬───────────────────┘ │   ║
         ║   │                 │                      │   ║
         ║   │                 ▼                      │   ║
         ║   │  ╔═══════════════════════════════╗   │   ║
         ║   │  ║  5. RAYCASTING (Main Part)    ║   │   ║
         ║   │  ╠═══════════════════════════════╣   │   ║
         ║   │  ║                               ║   │   ║
         ║   │  ║  FOR x = 0 to SCREEN_WIDTH:  ║   │   ║
         ║   │  ║  ┌─────────────────────────┐ ║   │   ║
         ║   │  ║  │ A. Calculate Ray Angle │ ║   │   ║
         ║   │  ║  │    cur_angle = player_ │ ║   │   ║
         ║   │  ║  │    angle - FOV/2 +     │ ║   │   ║
         ║   │  ║  │    x * (FOV/WIDTH)     │ ║   │   ║
         ║   │  ║  └───────────┬────────────┘ ║   │   ║
         ║   │  ║              │              ║   │   ║
         ║   │  ║              ▼              ║   │   ║
         ║   │  ║  ┌─────────────────────────┐ ║   │   ║
         ║   │  ║  │ B. Cast Ray (DDA)      │ ║   │   ║
         ║   │  ║  │                         │ ║   │   ║
         ║   │  ║  │  ┌──────────────────┐  │ ║   │   ║
         ║   │  ║  │  │ Horizontal Check │  │ ║   │   ║
         ║   │  ║  │  │ • Find Y gridline│  │ ║   │   ║
         ║   │  ║  │  │ • Step by TILE_H │  │ ║   │   ║
         ║   │  ║  │  │ • Until wall hit │  │ ║   │   ║
         ║   │  ║  │  │ • Record distance│  │ ║   │   ║
         ║   │  ║  │  └──────────────────┘  │ ║   │   ║
         ║   │  ║  │          ∩             │ ║   │   ║
         ║   │  ║  │  ┌──────────────────┐  │ ║   │   ║
         ║   │  ║  │  │ Vertical Check   │  │ ║   │   ║
         ║   │  ║  │  │ • Find X gridline│  │ ║   │   ║
         ║   │  ║  │  │ • Step by TILE_W │  │ ║   │   ║
         ║   │  ║  │  │ • Until wall hit │  │ ║   │   ║
         ║   │  ║  │  │ • Record distance│  │ ║   │   ║
         ║   │  ║  │  └──────────────────┘  │ ║   │   ║
         ║   │  ║  │          │             │ ║   │   ║
         ║   │  ║  │          ▼             │ ║   │   ║
         ║   │  ║  │  ┌──────────────────┐  │ ║   │   ║
         ║   │  ║  │  │ Choose Closest   │  │ ║   │   ║
         ║   │  ║  │  │ dist = min(h,v)  │  │ ║   │   ║
         ║   │  ║  │  └──────────────────┘  │ ║   │   ║
         ║   │  ║  └───────────┬────────────┘ ║   │   ║
         ║   │  ║              │              ║   │   ║
         ║   │  ║              ▼              ║   │   ║
         ║   │  ║  ┌─────────────────────────┐ ║   │   ║
         ║   │  ║  │ C. Fix Fisheye         │ ║   │   ║
         ║   │  ║  │    dist *= cos(Δθ)     │ ║   │   ║
         ║   │  ║  └───────────┬────────────┘ ║   │   ║
         ║   │  ║              │              ║   │   ║
         ║   │  ║              ▼              ║   │   ║
         ║   │  ║  ┌─────────────────────────┐ ║   │   ║
         ║   │  ║  │ D. Select Texture      │ ║   │   ║
         ║   │  ║  │    • North/South       │ ║   │   ║
         ║   │  ║  │    • East/West         │ ║   │   ║
         ║   │  ║  └───────────┬────────────┘ ║   │   ║
         ║   │  ║              │              ║   │   ║
         ║   │  ║              ▼              ║   │   ║
         ║   │  ║  ┌─────────────────────────┐ ║   │   ║
         ║   │  ║  │ E. Draw Column         │ ║   │   ║
         ║   │  ║  │                         │ ║   │   ║
         ║   │  ║  │  • Ceiling pixels      │ ║   │   ║
         ║   │  ║  │  • Textured wall       │ ║   │   ║
         ║   │  ║  │  • Floor pixels        │ ║   │   ║
         ║   │  ║  └─────────────────────────┘ ║   │   ║
         ║   │  ║                               ║   │   ║
         ║   │  ║  END FOR                      ║   │   ║
         ║   │  ╚═══════════════════════════════╝   │   ║
         ║   │                 │                      │   ║
         ║   │                 ▼                      │   ║
         ║   │  6. DRAW MINIMAP (optional)           │   ║
         ║   │  ┌─────────────────────────────────┐ │   ║
         ║   │  │ Draw 2D map overlay            │ │   ║
         ║   │  │ Show player position           │ │   ║
         ║   │  │ Show player direction          │ │   ║
         ║   │  └─────────────┬───────────────────┘ │   ║
         ║   │                 │                      │   ║
         ║   │                 ▼                      │   ║
         ║   │  7. DISPLAY FRAME                     │   ║
         ║   │  ┌─────────────────────────────────┐ │   ║
         ║   │  │ mlx_put_image_to_window()      │ │   ║
         ║   │  │ Show completed frame           │ │   ║
         ║   │  └─────────────────────────────────┘ │   ║
         ║   │                                       │   ║
         ║   └───────────────┬───────────────────────┘   ║
         ║                   │                           ║
         ║                   └─────────────┐             ║
         ║                                 │             ║
         ╚═════════════════════════════════╪═════════════╝
                                           │
                                           ▼
                                    ┌──────────┐
                                    │  REPEAT  │
                                    └──────────┘
```

---

## 🎯 DDA Algorithm Detailed Flow

```
╔════════════════════════════════════════════════════════════════════╗
║              DDA (Digital Differential Analysis)                   ║
║                   Ray-Wall Intersection                            ║
╚════════════════════════════════════════════════════════════════════╝

Input: Player Position (px, py), Ray Angle (θ)
Output: Hit Point (hx, hy), Distance, Wall Type

┌──────────────────────────────────────────────────────────────────┐
│                    HORIZONTAL RAY CASTING                        │
└──────────────────────────────────────────────────────────────────┘

STEP 1: Find First Horizontal Grid Intersection
───────────────────────────────────────────────

    Grid:  ───────────────  ← y = tile_y * TILE_SIZE
                            ← y = (tile_y+1) * TILE_SIZE
           ─────•─────────  ← First intersection
                ↑
              Player

    Code:
    ┌────────────────────────────────────────┐
    │ tile_y = floor(py / TILE_SIZE)        │
    │                                        │
    │ if (sin(θ) > 0):  // Ray going UP     │
    │    y = (tile_y + 1) * TILE_SIZE       │
    │ else:             // Ray going DOWN   │
    │    y = tile_y * TILE_SIZE             │
    │                                        │
    │ x = px + (y - py) / tan(θ)            │
    └────────────────────────────────────────┘


STEP 2: Calculate Step Size
────────────────────────────

    ┌────────────────────────────────────────┐
    │ step_y = TILE_SIZE (if going UP)      │
    │        = -TILE_SIZE (if going DOWN)   │
    │                                        │
    │ step_x = step_y / tan(θ)              │
    └────────────────────────────────────────┘


STEP 3: Step Through Grid Until Wall Hit
─────────────────────────────────────────

    ┌────────────────────────────────────────┐
    │ while (!is_wall(x, y ± ε)):           │
    │     x += step_x                        │
    │     y += step_y                        │
    │ end while                              │
    │                                        │
    │ // Now (x, y) is at wall              │
    └────────────────────────────────────────┘

    Visual:
    Player
      •
       ╲ Ray
        ╲
    ─────•───── Grid line (check)
          ╲
    ───────•─── Grid line (check)
            ╲
    ─────────█  Wall hit! (stop)


STEP 4: Calculate Distance
───────────────────────────

    ┌────────────────────────────────────────┐
    │ h_dist = √[(x-px)² + (y-py)²]         │
    └────────────────────────────────────────┘


┌──────────────────────────────────────────────────────────────────┐
│                     VERTICAL RAY CASTING                         │
└──────────────────────────────────────────────────────────────────┘

STEP 1: Find First Vertical Grid Intersection
──────────────────────────────────────────────

    Grid:       │           │
                │     •     │  ← First intersection
                │    ╱      │
                │   ╱       │
                │ Player    │
                │           │

    Code:
    ┌────────────────────────────────────────┐
    │ tile_x = floor(px / TILE_SIZE)        │
    │                                        │
    │ if (cos(θ) > 0):  // Ray going RIGHT │
    │    x = (tile_x + 1) * TILE_SIZE       │
    │ else:             // Ray going LEFT  │
    │    x = tile_x * TILE_SIZE             │
    │                                        │
    │ y = py + (x - px) * tan(θ)            │
    └────────────────────────────────────────┘


STEP 2-4: Similar to Horizontal (but with vertical steps)


┌──────────────────────────────────────────────────────────────────┐
│                    CHOOSE CLOSEST HIT                            │
└──────────────────────────────────────────────────────────────────┘

    ┌────────────────────────────────────────┐
    │ if (h_dist < v_dist):                 │
    │     hit = horizontal_hit              │
    │     is_vertical = 0                   │
    │ else:                                  │
    │     hit = vertical_hit                │
    │     is_vertical = 1                   │
    └────────────────────────────────────────┘

    Result: Closest wall intersection found!
```

---

## 🎨 Texture Mapping Process

```
╔════════════════════════════════════════════════════════════════════╗
║                      TEXTURE MAPPING                               ║
╚════════════════════════════════════════════════════════════════════╝

STEP 1: Calculate Texture X Coordinate
───────────────────────────────────────

Where on the wall did we hit?

    Wall Tile (64x64):
    ┌────────────────┐  0
    │                │
    │     Hit at     │
    │     x=45       │  ← We hit here
    │        ↓       │
    │        •       │
    └────────────────┘  64

    Code:
    ┌─────────────────────────────────────────────┐
    │ if (vertical wall):                         │
    │     offset = hit_y % TILE_SIZE              │
    │ else:                                        │
    │     offset = hit_x % TILE_SIZE              │
    │                                              │
    │ tex_x = (offset * texture_width) / TILE_SIZE│
    └─────────────────────────────────────────────┘


STEP 2: Calculate Wall Height on Screen
────────────────────────────────────────

    Formula: wall_height = (TILE_SIZE × SCREEN_HEIGHT) / distance

    Example:

    Close Wall (dist=100):       Far Wall (dist=400):
    wall_h = 64×800/100         wall_h = 64×800/400
           = 512 pixels                = 128 pixels

    Screen:                     Screen:
    ┌─────┐                     ┌─────┐
    │     │                     │     │
    │     │                     ├─────┤  ← Wall
    │     │                     │     │
    │     │                     │     │
    │     │                     │     │
    ├─────┤  ← Wall             │     │
    │     │                     │     │
    │     │                     │     │
    │     │                     │     │
    └─────┘                     └─────┘
     Tall                        Short


STEP 3: Calculate Draw Start/End
─────────────────────────────────

    ┌──────────────────────────────────────┐
    │ center = SCREEN_HEIGHT / 2           │
    │ draw_start = center - wall_height/2  │
    │ draw_end = center + wall_height/2    │
    │                                       │
    │ // Clamp to screen bounds            │
    │ if (draw_start < 0):                 │
    │     draw_start = 0                   │
    │ if (draw_end >= SCREEN_HEIGHT):      │
    │     draw_end = SCREEN_HEIGHT - 1     │
    └──────────────────────────────────────┘

    Screen (800px):
    ┌─────────┐  0
    │ Ceiling │  ← draw_start = 300
    ├─────────┤  300
    │         │
    │  WALL   │  ← Wall pixels
    │         │
    ├─────────┤  500  ← draw_end
    │  Floor  │
    └─────────┘  800


STEP 4: Map Texture Y to Screen Y
──────────────────────────────────

    Problem: Map 64-pixel texture to variable wall height

    Solution: Calculate step size

    ┌──────────────────────────────────────────┐
    │ step = texture_height / wall_height      │
    │                                           │
    │ tex_pos = (draw_start - center +         │
    │            wall_height/2) × step         │
    │                                           │
    │ for each screen_y from draw_start to     │
    │                          draw_end:       │
    │     tex_y = (int)tex_pos % tex_height   │
    │     color = texture[tex_y][tex_x]        │
    │     put_pixel(screen_x, screen_y, color) │
    │     tex_pos += step                      │
    └──────────────────────────────────────────┘

    Mapping:

    Texture (64px)      Screen (200px)
    ┌────────┐  0       ┌────────┐  300
    │  AAAA  │          │  AAAA  │
    │  BBBB  │  20      │  BBBB  │  360
    │  CCCC  │  40  →   │  CCCC  │  420
    │  DDDD  │          │  DDDD  │
    └────────┘  64      └────────┘  500

    Each texture line maps to multiple screen lines


STEP 5: Handle Texture Flipping
────────────────────────────────

    Without flip:               With flip:

    Looking RIGHT →            Looking LEFT ←
    ┌──────┐                   ┌──────┐
    │ ABC  │                   │ ABC  │
    │ ABC  │                   │ ABC  │
    └──────┘                   └──────┘
    Correct!                   Correct!

    ┌──────┐                   ┌──────┐
    │ CBA  │  ✗ Wrong!         │ ABC  │  ✓ Fixed!
    └──────┘                   └──────┘

    Code:
    ┌──────────────────────────────────────────┐
    │ if ((vertical && cos(angle) < 0) ||     │
    │     (!vertical && sin(angle) > 0)):     │
    │     tex_x = tex_width - tex_x - 1       │
    └──────────────────────────────────────────┘
```

---

## 🔧 Problem-Solution Flowcharts

### Problem 1: Fisheye Effect

```
┌────────────────────────────────────┐
│  PROBLEM: Fisheye Distortion       │
└────────────────────────────────────┘
              │
              ▼
    ┌─────────────────────┐
    │  Symptom:           │
    │  • Curved walls     │
    │  • Bulging center   │
    │  • Wrong distances  │
    └──────────┬──────────┘
               │
               ▼
    ┌─────────────────────┐
    │  Cause:             │
    │  Using raw ray      │
    │  distances instead  │
    │  of perpendicular   │
    │  distances          │
    └──────────┬──────────┘
               │
               ▼
    ┌─────────────────────────────────┐
    │  Visual:                        │
    │       Player                    │
    │          │╲                      │
    │          │ ╲ ray_dist (WRONG)   │
    │          │  ╲                    │
    │   perp_  │   ╲                   │
    │   dist   │    Wall               │
    │ (CORRECT)│                       │
    └──────────┬──────────────────────┘
               │
               ▼
    ┌─────────────────────────────────┐
    │  SOLUTION:                      │
    │                                 │
    │  corrected_dist =               │
    │     ray_dist ×                  │
    │     cos(ray_angle - player_angle)│
    └──────────┬──────────────────────┘
               │
               ▼
    ┌─────────────────────┐
    │  Result:            │
    │  ✓ Flat walls       │
    │  ✓ Correct depth    │
    │  ✓ No distortion    │
    └─────────────────────┘
```

### Problem 2: Wall Gaps

```
┌────────────────────────────────────┐
│  PROBLEM: Gaps Between Walls       │
└────────────────────────────────────┘
              │
              ▼
    ┌─────────────────────┐
    │  Symptom:           │
    │  • Thin black lines │
    │  • Seeing through   │
    │  • Flickering       │
    └──────────┬──────────┘
               │
               ▼
    ┌─────────────────────────┐
    │  Cause:                 │
    │  Floating point         │
    │  precision at grid      │
    │  boundaries             │
    │                         │
    │  Example:               │
    │  63.99999 vs 64.00001   │
    │  Different tiles!       │
    └──────────┬──────────────┘
               │
               ▼
    ┌─────────────────────────────────┐
    │  Visual:                        │
    │                                 │
    │  Grid boundary:                 │
    │      │                          │
    │      │ ← Might check wrong side │
    │  ────┼────                      │
    │      │                          │
    └──────────┬──────────────────────┘
               │
               ▼
    ┌─────────────────────────────────┐
    │  SOLUTION:                      │
    │                                 │
    │  Add small epsilon (1e-6):      │
    │                                 │
    │  if (going_up):                 │
    │      check(x, y + epsilon)      │
    │  else:                          │
    │      check(x, y - epsilon)      │
    │                                 │
    │  This ensures checking correct  │
    │  side of boundary               │
    └──────────┬──────────────────────┘
               │
               ▼
    ┌─────────────────────┐
    │  Result:            │
    │  ✓ No gaps          │
    │  ✓ Solid walls      │
    │  ✓ No flickering    │
    └─────────────────────┘
```

### Problem 3: Division by Zero

```
┌────────────────────────────────────┐
│  PROBLEM: Division by Zero         │
└────────────────────────────────────┘
              │
              ▼
    ┌─────────────────────┐
    │  Symptom:           │
    │  • Crash            │
    │  • Infinite loop    │
    │  • NaN values       │
    └──────────┬──────────┘
               │
               ▼
    ┌─────────────────────────┐
    │  Cause:                 │
    │  tan(π/2) = ∞          │
    │  cos(π/2) = 0          │
    │                         │
    │  Dividing by these      │
    │  causes problems        │
    └──────────┬──────────────┘
               │
               ▼
    ┌─────────────────────────────────┐
    │  Critical Angles:               │
    │                                 │
    │  π/2 (90°)  → Pointing UP       │
    │  3π/2 (270°)→ Pointing DOWN     │
    │  0 (0°)     → Pointing RIGHT    │
    │  π (180°)   → Pointing LEFT     │
    └──────────┬──────────────────────┘
               │
               ▼
    ┌─────────────────────────────────┐
    │  SOLUTION:                      │
    │                                 │
    │  Check before dividing:         │
    │                                 │
    │  if (fabs(tan(angle)) < 1e-9):  │
    │      step_x = 0  // Pure horiz  │
    │  else:                          │
    │      step_x = step_y/tan(angle) │
    │                                 │
    │  if (dist < epsilon):           │
    │      dist = epsilon             │
    └──────────┬──────────────────────┘
               │
               ▼
    ┌─────────────────────┐
    │  Result:            │
    │  ✓ No crashes       │
    │  ✓ Smooth rotation  │
    │  ✓ All angles work  │
    └─────────────────────┘
```

---

## 🎯 Quick Reference Diagrams

### Angle Reference

```
              90° (π/2)
              North ↑
                 0,1
                  │
                  │
180° (π) ─────────┼───────── 0°/360° (0/2π)
West              │            East
 -1,0             │            1,0
                  │
                  │
              0,-1
              South ↓
             270° (3π/2)
```

### Ray Angles for Screen

```
Screen Position:  LEFT    CENTER    RIGHT
                   │        │        │
Ray Angle:     θ-FOV/2     θ      θ+FOV/2

Example (FOV=60°, Player facing 90°):
                  60°      90°      120°
```

### Collision Detection

```
New Position Check:

┌──────────────────────────┐
│  Try move to (new_x, y)  │  ← Check X first
│  if safe:                │
│      x = new_x           │
└────────┬─────────────────┘
         │
         ▼
┌──────────────────────────┐
│  Try move to (x, new_y)  │  ← Then check Y
│  if safe:                │
│      y = new_y           │
└──────────────────────────┘

Why separate?
  → Allows sliding along walls
  → Smoother movement
  → Better game feel
```

### Texture Selection

```
Hit Type:       Direction:       Texture:
─────────────────────────────────────────
Vertical        cos(θ) > 0       EAST
Vertical        cos(θ) < 0       WEST
Horizontal      sin(θ) > 0       NORTH
Horizontal      sin(θ) < 0       SOUTH
```

---

## 📐 Mathematical Formulas

### Distance Calculation

```
Distance = √[(x₂-x₁)² + (y₂-y₁)²]

In code:
distance = hypot(hit_x - player_x, hit_y - player_y);
```

### Wall Height

```
wall_height = (TILE_SIZE × SCREEN_HEIGHT) / distance

Relationship:
┌──────────────────────────┐
│ distance ↑  → height ↓   │  (Far = Small)
│ distance ↓  → height ↑   │  (Close = Big)
└──────────────────────────┘
```

### Fisheye Correction

```
corrected_distance = raw_distance × cos(Δθ)

where: Δθ = ray_angle - player_angle
```

### Texture Mapping

```
tex_x = (hit_position % TILE_SIZE) × tex_width / TILE_SIZE
tex_y = screen_y × tex_height / wall_height

step = tex_height / wall_height
```

---

## 🎮 Input to Output Flow

```
┌──────────┐
│ Key: 'W' │
└─────┬────┘
      │
      ▼
┌───────────────┐
│ k_up = 1      │  (Flag set)
└───────┬───────┘
        │
        ▼
┌────────────────────────────┐
│ new_x = x + cos(θ)×speed   │  (Calculate)
│ new_y = y + sin(θ)×speed   │
└──────────┬─────────────────┘
           │
           ▼
┌────────────────────┐
│ Collision check    │  (Validate)
└──────────┬─────────┘
           │
           ▼
┌────────────────────┐
│ Update position    │  (Apply)
└──────────┬─────────┘
           │
           ▼
┌────────────────────┐
│ Raycast new view   │  (Render)
└──────────┬─────────┘
           │
           ▼
┌────────────────────┐
│ Display on screen  │  (Output)
└────────────────────┘
```

---

## 🏆 Complete Example: Single Ray

```
═══════════════════════════════════════════════════════════════
                    EXAMPLE: Casting One Ray
═══════════════════════════════════════════════════════════════

INPUT:
  Player position: (200, 200)
  Player angle: 45° (π/4 radians)
  Screen column: x = 400 (middle of 800px screen)

STEP 1: Calculate Ray Angle
────────────────────────────
  FOV = 60° = π/3
  step = π/3 / 800 = 0.00131
  ray_angle = π/4 - π/6 + 400×0.00131
            = 45° - 30° + 30°
            = 45°

STEP 2: Cast Ray (DDA)
───────────────────────
  Horizontal check:
    • First intersection: y=256, x=256
    • Step: y+=64, x+=64
    • Hit wall at: (384, 384)
    • Distance: √[(384-200)² + (384-200)²] = 260.2

  Vertical check:
    • First intersection: x=256, y=256
    • Step: x+=64, y+=64
    • Hit wall at: (320, 320)
    • Distance: √[(320-200)² + (320-200)²] = 169.7

  Closest: Vertical hit at (320, 320), dist=169.7

STEP 3: Fix Fisheye
────────────────────
  corrected_dist = 169.7 × cos(45° - 45°)
                 = 169.7 × cos(0°)
                 = 169.7 × 1
                 = 169.7

STEP 4: Select Texture
──────────────────────
  Vertical hit, cos(45°) > 0
  → Texture = EAST

STEP 5: Calculate Wall Height
──────────────────────────────
  wall_height = (64 × 800) / 169.7
              = 301 pixels

STEP 6: Draw Column
───────────────────
  draw_start = 400 - 301/2 = 249
  draw_end = 400 + 301/2 = 551

  Pixels 0-249:   Ceiling (blue)
  Pixels 249-551: Textured wall
  Pixels 551-800: Floor (gray)

OUTPUT:
  Column 400 drawn with 301-pixel tall wall!
═══════════════════════════════════════════════════════════════
```

---

**END OF VISUAL DOCUMENTATION**

_For detailed code explanations, see RAYCASTING_DOCUMENTATION.md_
