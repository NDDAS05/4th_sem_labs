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

---

# AI Explanation

# 🧠 Big Picture First

Think of:
* **Cache** = fast notebook (near CPU)
* **Main memory** = big slow book (RAM)

Whenever CPU writes data → we must decide:
👉 *"Should I update both notebook + book immediately, or only notebook for now?"*
That’s where **Write Through** and **Write Back** come in.

---

## 🔹 1. Write Through (Simple but Slow)

**💡 Idea:**
Whenever CPU writes: ➡️ Update cache + main memory immediately

**🧠 Analogy:**
You update your notebook and immediately rewrite the same thing in your main book

**✅ Why it's good:**
* Memory always has the latest data (no confusion)
* Easy to implement

**❌ Problem:**
* Writing to RAM is slow
* CPU has to wait → called **write stall**

**🔧 Solution:**
* Use a **write buffer**
* CPU dumps data in buffer → continues work
* Buffer writes to memory in background
👉 So CPU doesn’t waste time waiting

---

## 🔹 2. Write Back (Fast but Slightly Complex)

**💡 Idea:**
➡️ Write only to cache ➡️ Update main memory later (when block is replaced)

**🧠 Analogy:**
You update your notebook, and only when the page is full/replaced, you copy it to the main book

**🔥 Key Concept: Dirty Bit**
* Each block has a **dirty bit**
* If modified → marked dirty
* Only dirty blocks are written to memory later

**✅ Advantages:**
* Writes happen at cache speed (fast)
* Multiple writes → only one memory write
* Saves memory bandwidth

**❌ Problem:**
* Memory may have old data temporarily
* Slightly complex to manage

---

## 🔹 3. Write Miss (Important Exam Concept)

👉 **Situation:** CPU wants to write, but data is not in cache
Now 2 strategies:

### ✔️ Write Allocate (Fetch on Write)

**💡 Idea:**
* First bring block into cache
* Then write

**🧠 Analogy:**
You don’t have the page → you fetch it → then write

**✅ Used with:**
* Write Back

### ✔️ No Write Allocate (Write Around)

**💡 Idea:**
* Write directly to main memory
* Do NOT load into cache

**🧠 Analogy:**
You write directly in the big book, skip notebook

**✅ Used with:**
* Write Through

---

## 🔹 4. Cache Miss Types (Very Important)

👉 **Cache miss** = Data not found in cache

### 1. Compulsory Miss (Cold Start)
* First time accessing data
* Cache is empty
**🧠 Example:** Opening a file for the first time

### 2. Capacity Miss
* Cache is too small
* Old data removed, needed again later
**🧠 Example:** Your notebook is small → you erase something → later you need it again

### 3. Conflict Miss
* Happens due to placement restriction
**🧠 Example:** Two different items forced to same position → keep replacing each other
👉 **Happens in:**
* Direct mapped cache
* Set associative cache

---

## ⚡ Quick Summary (Exam Recall)

| Concept | Key Idea |
| :--- | :--- |
| **Write Through** | Write to cache + memory immediately |
| **Write Back** | Write to cache, memory later |
| **Write Allocate** | Load block on write miss |
| **No Write Allocate** | Write directly to memory |
| **Compulsory Miss** | First-time access |
| **Capacity Miss** | Cache too small |
| **Conflict Miss** | Placement issue |

---

## 🧠 Final Understanding Trick

👉 **If question asks:**
* *"Which is faster?"* → **Write Back**
* *"Which is simpler?"* → **Write Through**
* *"Which keeps memory always updated?"* → **Write Through**
* *"Which saves bandwidth?"* → **Write Back**
