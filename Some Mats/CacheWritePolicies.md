# 📘 Cache Write Policies & Miss Handling

---

## 🔹 1. Write Through

### Definition:
Information is written to both:
- Cache block  
- Lower level memory block  

### Key Points:
- Read misses never result in writes to the lower level  
- Easier to implement  
- Lower level memory always has the most current copy of data  

### Drawback:
- CPU must wait until write in lower level is completed  
- This delay is called **write stall**

### Improvement:
- Write stall can be reduced using a **write buffer**
  - Allows processor to continue once data is written to buffer  
  - Overlaps processor execution with memory update  

---

## 🔹 2. Write Back

### Definition:
- Information is written **only to cache**
- Modified block is written to main memory **when it is replaced**

### Key Points:
- Uses **dirty bit** in each block to reduce frequency of writing back  
- Write occurs at the speed of cache memory  
- Multiple writes in a block require only **one write** to lower level memory  

### Advantages:
- Some writes do not go to memory → reduces memory bandwidth usage  
- More efficient for multiprocessor systems  

---

## 🔹 3. Actions on Write Miss

### ✔️ Write Allocate (Fetch on Write)
- Block is loaded on a write miss  
- Followed by write hit action  

### ✔️ No Write Allocate (Write Around)
- Block is modified in lower level memory  
- Block is **not loaded into cache**

---

## 🔹 4. Cache Miss Types

### Definition:
Cache miss occurs when required data is not found in cache.

### Types of Cache Misses:

#### 1. Compulsory Miss
- Occurs on **first access** to a memory block  

#### 2. Capacity Miss
- Occurs when cache cannot contain all required blocks  
- Blocks are discarded and later retrieved  

#### 3. Conflict Miss (Collision / Interference Miss)
- Occurs due to block placement strategy  
- Common in:
  - Direct mapped cache  
  - Set associative cache