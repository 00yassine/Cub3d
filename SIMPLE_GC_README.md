# Simple Garbage Collector (GC) - Documentation

## Overview

هادي نسخة مبسطة و واضحة من Garbage Collector ديال cub3d. كتخدم بطريقة بسيطة و فعالة.

## How It Works

### Structure

```c
typedef struct s_gc_node
{
    void             *ptr;      // Pointer لي تم تخصيصه
    struct s_gc_node *next;     // Node التالي في القائمة
} t_gc_node;
```

القائمة كاملة محفوظة في متغير global:

```c
static t_gc_node *g_gc_head = NULL;
```

## Functions

### 1. `void *gc_malloc(size_t size)`

**الاستخدام:** بدل `malloc()` العادي
**الوظيفة:**

- كيخصص memory
- كيضيف pointer للقائمة ديال GC
- كيرجع pointer لي تخصص

**مثال:**

```c
char *str = gc_malloc(100);  // بدل malloc(100)
t_data *data = gc_malloc(sizeof(t_data));
```

### 2. `void gc_free(void *ptr)`

**الاستخدام:** بدل `free()` العادي (optional)
**الوظيفة:**

- كيحرر pointer معين
- كيحيدو من القائمة
- نادر ما كنستعملوه حيت gc_free_all كتنظف كلشي

### 3. `void gc_free_all(void)`

**الاستخدام:** فنهاية البرنامج أو عند Error
**الوظيفة:**

- كينظف جميع memory لي تخصصات
- كيحرر القائمة كاملة
- كيحط g_gc_head = NULL

**مثال:**

```c
// في حالة error
void print_error(char *msg)
{
    printf("%s", msg);
    gc_free_all();
    exit(1);
}

// في نهاية البرنامج
int main(void)
{
    // ... code ...
    gc_free_all();
    return (0);
}
```

## Advantages

### ✅ البساطة

- 3 functions فقط
- بلا parameters معقدة
- سهل الفهم

### ✅ الأمان

- كلشي كينظف automatically
- ما كاينش memory leaks
- بلا segfaults

### ✅ السهولة

- بدل `malloc()` ب `gc_malloc()`
- بلا stress من `free()`
- نادي `gc_free_all()` فالنهاية

## Changes Made

### قبل (معقد):

```c
void *gc_malloc(size_t size, int mode);
ptr = gc_malloc(100, 1);           // mode parameter
gc_malloc(0, 0);                   // للتنظيف
```

### بعد (بسيط):

```c
void *gc_malloc(size_t size);
ptr = gc_malloc(100);              // بسيط!
gc_free_all();                      // واضح!
```

## Usage Example

```c
int main(void)
{
    char *line;
    t_map *map;

    // استعمال gc_malloc بدل malloc
    line = gc_malloc(1000);
    map = gc_malloc(sizeof(t_map));

    // استعمال variables عادي
    // ...

    // تنظيف automatic
    gc_free_all();
    return (0);
}
```

## Implementation Details

### Linked List

- كل allocation كيزاد node جديد فالبداية
- القائمة كتكون فالذاكرة static (global)
- O(1) لإضافة node جديد
- O(n) لتحرير كلشي (gc_free_all)

### Memory Safety

- `gc_malloc` كيرجع NULL إذا فشل malloc
- `gc_free_all` كتحرر كلشي حتى إذا كان في errors
- بلا double-free problems

## Notes

⚠️ **هام:**

- ستعمل gc_malloc فقط لMemory لي بغيتي تنظفها automatically
- Memory ديال MLX (images, windows) تحرر manually
- النظام بسيط و كافي لـ cub3d

## Performance

- ✅ Fast allocation (O(1))
- ✅ Fast cleanup (O(n)) - مرة وحدة فالنهاية
- ✅ بلا overhead معقد
- ✅ Memory efficient

---

**Created:** October 30, 2025
**Version:** 1.0 - Simple & Clean
