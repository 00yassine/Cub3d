# 🎨 Cub3D Raycasting Flowcharts (SVG)

Beautiful, interactive SVG flowcharts explaining the raycasting engine step-by-step.

## 📋 Available Flowcharts

### 1. System Overview (`01_system_overview.svg`)

**Complete main loop visualization**

- MLX initialization
- Hook setup
- 60 FPS game loop
- Input → Movement → Rendering → Display
- Memory cleanup

**View it:** Open in browser or VS Code

```bash
open flowcharts/01_system_overview.svg
# or
code flowcharts/01_system_overview.svg
```

---

### 2. DDA Algorithm (`02_dda_algorithm.svg`)

**Detailed ray-wall intersection detection**

- Horizontal ray casting
- Vertical ray casting
- Ray marching through grid
- Distance calculation
- Fisheye correction
- Visual grid demonstration

**Key Concepts:**

- Digital Differential Analysis
- Grid-based collision
- Step calculation
- Distance comparison

---

### 3. Texture Mapping (`03_texture_mapping.svg`)

**From 3D world coordinates to 2D screen**

- Wall height calculation
- Draw limits computation
- Texture selection (N/S/E/W)
- texture_x calculation
- Y-axis texture mapping
- Column-by-column rendering

**Visual Examples:**

- Screen columns → Texture pixels
- Texture sample demonstration
- Final textured wall preview

---

### 4. Problems & Solutions (`04_problems_solutions.svg`)

**Common issues and their fixes**

❌ **Problems Covered:**

1. **Fisheye Effect** - Curved walls
2. **Division by Zero** - Crash at cardinal angles
3. **Wall Gaps** - Thin lines between walls
4. **Wrong Texture** - Flipped/rotated textures
5. **Collision Issues** - Player stuck on corners
6. **Memory Leaks** - Resources not freed

✅ **Solutions Provided:**

- Code snippets
- Mathematical formulas
- Implementation tips
- Best practices

---

### 5. Full Visualization (`05_visualization.svg`)

**Complete raycasting scene**

- Top-down map view (8×8 grid)
- Player position and FOV
- Multiple rays cast
- Distance measurements
- Resulting 3D view
- Step-by-step explanation

**Perfect for understanding:**

- How rays map to screen columns
- Distance → Wall height relationship
- FOV and perspective
- Complete ray-to-pixel pipeline

---

## 🚀 How to Use

### View in Browser

```bash
# Open individual flowchart
firefox flowcharts/01_system_overview.svg

# Or use any browser
google-chrome flowcharts/02_dda_algorithm.svg
```

### View in VS Code

1. Open VS Code
2. Navigate to `flowcharts/` folder
3. Click on any `.svg` file
4. VS Code will render it beautifully!

### View All at Once

```bash
# Open entire folder in browser (create HTML index)
cd flowcharts
python3 -m http.server 8000
# Then open: http://localhost:8000
```

### Include in Markdown

```markdown
![System Overview](flowcharts/01_system_overview.svg)
![DDA Algorithm](flowcharts/02_dda_algorithm.svg)
```

---

## 📚 Learning Path

**For Beginners:**

1. Start with `05_visualization.svg` → Get the big picture
2. Read `01_system_overview.svg` → Understand the loop
3. Study `02_dda_algorithm.svg` → Learn ray casting
4. Review `03_texture_mapping.svg` → See rendering
5. Check `04_problems_solutions.svg` → Avoid common mistakes

**For Debugging:**

1. Identify your issue in `04_problems_solutions.svg`
2. Check relevant algorithm in `02_dda_algorithm.svg` or `03_texture_mapping.svg`
3. Verify logic against `01_system_overview.svg`

**For Code Review:**

1. Use as reference while reading source code
2. Compare implementation with flowcharts
3. Verify math formulas

---

## 🎨 SVG Features

✅ **Scalable** - Zoom in/out without quality loss
✅ **Interactive** - Hover for tooltips (in some viewers)
✅ **Print-friendly** - Perfect for documentation
✅ **Lightweight** - Small file size
✅ **Professional** - Color-coded for clarity

**Color Legend:**

- 🔵 Blue - Initialization/Setup
- 🟢 Green - Processing/Calculations
- 🟠 Orange - Decisions/Conditions
- 🟣 Purple - Complex calculations
- 🔴 Red - Problems/Errors
- ✅ Green Checkmark - Solutions

---

## 📖 Related Documentation

- **RAYCASTING_DOCUMENTATION.md** - Detailed text explanations
- **RAYCASTING_FLOWCHARTS.md** - ASCII art version
- **MEMORY_TESTING.md** - Memory leak testing
- **final_leak_report.md** - Test results

---

## 🔧 Technical Details

**Format:** SVG (Scalable Vector Graphics)
**Dimensions:** Responsive (viewBox-based)
**Compatibility:**

- ✅ Modern browsers (Chrome, Firefox, Safari, Edge)
- ✅ VS Code
- ✅ GitHub (renders inline)
- ✅ Markdown viewers
- ✅ Image editors (Inkscape, Illustrator)

**Fonts Used:**

- Arial - Body text
- Courier New - Code snippets

---

## 💡 Tips

### Export to PNG

```bash
# Using Inkscape
inkscape flowcharts/01_system_overview.svg --export-png=output.png --export-dpi=300

# Using ImageMagick
convert -density 300 flowcharts/01_system_overview.svg output.png
```

### Create PDF

```bash
# Using Inkscape
inkscape flowcharts/*.svg --export-pdf=raycasting_flowcharts.pdf

# Or use browser print to PDF
```

### Edit SVG

- Open in Inkscape (free)
- Open in Adobe Illustrator
- Edit XML directly (it's just text!)

---

## 🎯 Quick Reference

| Flowchart                 | Focus          | Best For            |
| ------------------------- | -------------- | ------------------- |
| 01_system_overview.svg    | Main loop      | Understanding flow  |
| 02_dda_algorithm.svg      | Ray casting    | Algorithm deep-dive |
| 03_texture_mapping.svg    | Rendering      | Visual output       |
| 04_problems_solutions.svg | Debugging      | Fixing issues       |
| 05_visualization.svg      | Complete scene | Big picture         |

---

## 📝 Notes

- All diagrams based on actual source code
- Tested with 1200×800 screen resolution
- TILE_SIZE = 64 pixels
- FOV = 60 degrees
- Works with MinilibX library

---

## 🌟 Contributing

Found an issue or want to improve a flowchart?

1. Edit the SVG file (it's XML)
2. Test in browser
3. Commit with clear message

---

## 📄 License

Part of Cub3D project documentation.
Use freely for learning and reference.

---

**Created with ❤️ for 42 students learning raycasting**

_Last updated: October 2025_
