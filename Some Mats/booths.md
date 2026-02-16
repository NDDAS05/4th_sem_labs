# Booths Algorithm

Here is a complete, exam-style breakdown of Booth's Multiplication Algorithm, covering every concept, formula, diagram, and trace step provided in the slide.

---

### **Topic: Booth's Multiplication Algorithm**

**1. Core Concept and Mathematical Basis**
Booth's algorithm is designed to **speed up the multiplication process** and directly handle binary integers in **signed 2's complement representation** without needing to check signs or convert numbers beforehand.

* **The Principle of Strings:** The algorithm takes advantage of the fact that a string of 0's in the multiplier requires no addition, just shifting. More importantly, a continuous string of 1's can be optimized.
* **The Mathematical Rule:** A string of 1's in the multiplier extending from bit weight  down to weight  can be treated as a single subtraction and a single addition using the formula: ****.
* **Example from the slide:** Take the number , which is `001110` in binary.
* It has a string of 1's from position  down to  (so  and ).
* Using the formula: .
* In decimal: .


* **Application to Multiplication:** If  is the multiplicand and  is the multiplier, the operation  can be executed as . Instead of performing three separate additions for the three '1's in `001110`, the hardware can obtain the product by shifting  left four times, and subtracting  shifted left by 1 bit. *(Note: The hardware achieves this relative shifting by shifting the partial product to the right instead).*

**2. Hardware Implementation**
The hardware block diagram utilizes the following components:

* **BR Register:** Holds the Multiplicand.
* **QR Register:** Holds the Multiplier. The Least Significant Bit (LSB) of the multiplier in this register is denoted as ****.
* **AC Register:** The accumulator, initialized to 0, which holds the upper half of the partial product.
* ** (Extra Flip-Flop):** A single extra bit appended to the right of the QR register. It helps the hardware "look back" at the previous bit to detect the beginning and end of a string of 1's.
* **Sequence Counter (SC):** Initialized to the number of bits in the multiplier () and decrements down to 0 to control the loop.
* **Complementer and Parallel Adder:** Used to add or subtract BR from AC.

**3. The Operational Algorithm (Flowchart)**

* **Initialization:** Multiplicand is loaded into BR. Multiplier is loaded into QR. Accumulator . Extra bit . Sequence counter .
* **The Decision Loop:** The hardware looks at the 2-bit pair formed by **** to decide what to do.
* **Case `10` (Start of a string of 1's):** Subtract the multiplicand. The operation is  (which adds the 2's complement of BR).
* **Case `01` (End of a string of 1's):** Add the multiplicand. The operation is .
* **Case `11` (Middle of a string of 1's):** Do nothing mathematically.
* **Case `00` (Middle of a string of 0's):** Do nothing mathematically.


* **Arithmetic Shift Right (`ashr`):** Regardless of which path was taken above, the combined registers (AC and QR) are subjected to an Arithmetic Shift Right. Unlike a logical shift, an arithmetic shift **preserves the sign bit** (the leftmost bit of AC is copied into itself, shifting the rest down).  shifts into .
* **Decrement & Check:** Decrease SC by 1. If , loop back to check the new . If , the operation ends. The final 2's complement product is in the combined **AC QR** registers.

---

### **4. Complete Execution Trace (Table Breakdown)**

**Problem:** Multiply 

* **Multiplicand (BR):** . In 5-bit 2's complement,  is `01001`, so  is **`10111`**.
* **Multiplier (QR):** . In 5-bit 2's complement,  is `01101`, so  is **`10011`**.
* **Helper Value ():** For subtractions, we need the 2's complement of BR. The 2's complement of `10111` is **`01001`**.

**Step-by-Step Trace:**

* **Initialization:**  is `00000`.  is `10011`.  is `0`.  is `101` (binary for 5).
* *Look at :* It is **`10`**.


* **Cycle 1 (Condition `10`):**
* *Operation:* Subtract BR (which means add ). .
* *Shift (`ashr`):* Shift AC and QR right. The leftmost bit of AC (`0`) duplicates.  becomes `00100`,  becomes `11001`. The old  (`1`) falls into .
* *Update:*  (4). *New  is **`11`**.*


* **Cycle 2 (Condition `11`):**
* *Operation:* Do nothing.
* *Shift (`ashr`):* Shift right. Leftmost bit of AC (`0`) duplicates.  becomes `00010`,  becomes `01100`. The old  (`1`) goes to .
* *Update:*  (3). *New  is **`01`**.*


* **Cycle 3 (Condition `01`):**
* *Operation:* Add BR. .
* *Shift (`ashr`):* Shift right. Notice the leftmost bit of AC is now `1`. During arithmetic shift, the `1` duplicates to preserve the negative sign.  becomes `11100`,  becomes `10110`. Old  (`0`) goes to .
* *Update:*  (2). *New  is **`00`**.*


* **Cycle 4 (Condition `00`):**
* *Operation:* Do nothing.
* *Shift (`ashr`):* Shift right. The `1` duplicates again.  becomes `11110`,  becomes `01011`. Old  (`0`) goes to .
* *Update:*  (1). *New  is **`10`**.*


* **Cycle 5 (Condition `10`):**
* *Operation:* Subtract BR (add ). . The 6th bit (carry) is discarded, leaving .
* *Shift (`ashr`):* Shift right. Leftmost bit (`0`) duplicates.  becomes **`00011`**,  becomes **`10101`**.  becomes `1`.
* *Update:*  (0).



**END.** The sequence counter is 0.
The final product in combined AC and QR is `00011 10101`. Converting this 10-bit binary number to decimal yields ****, confirming the algorithm correctly multiplied two negative numbers to produce a positive result.

---

This is the absolute most important part of Booth’s Algorithm. The  mechanism is the "brain" that makes the shortcut work.

To understand the logic, you have to remember two things:

1. **We read the multiplier from right to left** (from the Least Significant Bit to the Most Significant Bit).
2. ** is the *current* bit** we are looking at.
3. ** is the *previous* bit** we just looked at (which is stored in that extra flip-flop).

Together,  act as a "sliding window" of 2 bits that scans across the multiplier to detect **strings of 1s**.

Here is the complete breakdown of the math secret behind it, and what each 2-bit combination represents.

---

### The Mathematical Secret

Normally, if you have a binary number like `01110` (which is 14 in decimal), you would multiply by adding the multiplicand three times for each `1` you see:

* .

Booth's trick relies on the mathematical rule that a continuous string of 1s can be calculated by just **one addition and one subtraction**:

* .

So, instead of doing three separate additions, Booth's algorithm just says: **"Subtract when the string of 1s begins, do nothing in the middle, and Add when the string of 1s ends."**

---

### What 00, 01, 10, and 11 Represent

As the  window slides from right to left across the multiplier, it looks for transitions.

#### 1. The `10` Case: The Beginning of a String of 1s

* ** (Current):** `1`
* ** (Previous):** `0`
* **What it means:** Moving right to left, we just transitioned from seeing `0`s to seeing a `1`. We have found the *start* of a string of 1s.
* **Action (SUBTRACT):** This corresponds to the  part of Booth's formula. The hardware subtracts the multiplicand from the accumulator.

#### 2. The `11` Case: The Middle of a String of 1s

* ** (Current):** `1`
* ** (Previous):** `1`
* **What it means:** We are currently inside a block of continuous `1`s.
* **Action (DO NOTHING):** Because we already subtracted at the start of this string, we don't need to do any math here. The hardware just shifts the registers to the right to move to the next bit position. This is where the algorithm saves time.

#### 3. The `01` Case: The End of a String of 1s

* ** (Current):** `0`
* ** (Previous):** `1`
* **What it means:** Moving right to left, we just transitioned from seeing `1`s to seeing a `0`. We have reached the *end* of the string of 1s.
* **Action (ADD):** This corresponds to the  part of Booth's formula. The hardware adds the multiplicand back into the accumulator to "close" the string.

#### 4. The `00` Case: A String of 0s

* ** (Current):** `0`
* ** (Previous):** `0`
* **What it means:** We are in a continuous block of `0`s.
* **Action (DO NOTHING):** Multiplying by 0 is 0. The hardware just shifts the registers to the right.

---

### Quick Visual Example

Let's scan the multiplier `001110` from right to left (remembering we pad an imaginary `0` at the very beginning for ):

1. Current is `0`, Previous is `0`  **`00`**  Shift.
2. Current is `1`, Previous is `0`  **`10`**  Start of 1s! **Subtract**.
3. Current is `1`, Previous is `1`  **`11`**  Middle of 1s. Shift.
4. Current is `1`, Previous is `1`  **`11`**  Middle of 1s. Shift.
5. Current is `0`, Previous is `1`  **`01`**  End of 1s! **Add**.
6. Current is `0`, Previous is `0`  **`00`**  Shift.


---


Here is the complete step-by-step trace for **** using Booth's Algorithm.

We will use a 5-bit system () just like the example in the slide.

*  in binary is `01001`. Therefore,  in 2's complement is **`10111`**.
*  in binary is **`00111`**.

### **Initial Setup**

* **Multiplicand ():** `10111` ()
* **2's Complement of Multiplicand ():** `01001` (This is , used when we need to subtract).
* **Multiplier ():** `00111` ()
* **Accumulator ():** `00000`
* **Extra bit ():** `0`
* **Sequence Counter ():** 

---

### **Execution Trace Table**

| Operation |  |  (Sub) or  (Add) |  |  |  |  |
| --- | --- | --- | --- | --- | --- | --- |
| **Initialization** |  |  | `00000` | `00111` | `0` | 5 |
| **Cycle 1** | **`10`** | **Subtract BR** (Add `01001`) | `01001` |  |  |  |
|  |  | **ashr** (Shift right) | `00100` | `10011` | `1` | 4 |
| **Cycle 2** | **`11`** | **Do nothing** |  |  |  |  |
|  |  | **ashr** (Shift right) | `00010` | `01001` | `1` | 3 |
| **Cycle 3** | **`11`** | **Do nothing** |  |  |  |  |
|  |  | **ashr** (Shift right) | `00001` | `00100` | `1` | 2 |
| **Cycle 4** | **`01`** | **Add BR** (Add `10111`) | `11000` |  |  |  |
|  |  | **ashr** (Shift right) | `11100` | `00010` | `0` | 1 |
| **Cycle 5** | **`00`** | **Do nothing** |  |  |  |  |
|  |  | **ashr** (Shift right) | `11110` | `00001` | `0` | 0 |

---

### **Detailed Step-by-Step Breakdown**

* **Initialization:**  is `00000`,  is `00111`,  is `0`.
* *Look at the last bit of QR and : `10*`


* **Cycle 1 (Condition `10`):** We hit the start of a string of 1s.
* **Operation:** Subtract  (which means add `01001`). .
* **Shift (`ashr`):** Shift the combined `01001 00111 0` right. The leftmost `0` in  duplicates.  becomes `00100`,  becomes `10011`. The `1` falls into .
* *Look at new : `11*`


* **Cycle 2 (Condition `11`):** We are in the middle of a string of 1s.
* **Operation:** Do nothing.
* **Shift (`ashr`):** Shift right.  becomes `00010`,  becomes `01001`. The `1` falls into .
* *Look at new : `11*`


* **Cycle 3 (Condition `11`):** Still in the middle of a string of 1s.
* **Operation:** Do nothing.
* **Shift (`ashr`):** Shift right.  becomes `00001`,  becomes `00100`. The `1` falls into .
* *Look at new : `01*`


* **Cycle 4 (Condition `01`):** We reached the end of the string of 1s.
* **Operation:** Add . .
* **Shift (`ashr`):** Shift right. *Crucial step:* The leftmost bit of  is now `1`. During arithmetic shift, this `1` duplicates to preserve the negative sign.  becomes `11100`,  becomes `00010`. The `0` falls into .
* *Look at new : `00*`


* **Cycle 5 (Condition `00`):** String of 0s.
* **Operation:** Do nothing.
* **Shift (`ashr`):** Shift right. The `1` duplicates again.  becomes `11110`,  becomes `00001`. The `0` falls into .
*  reaches 0. Operation Ends.



### **Final Result Verification**

The final 10-bit product in the combined  and  registers is **`11110 00001`**.

Since the leftmost bit is `1`, the hardware knows this is a negative number in 2's complement. Let's convert it back to decimal to verify:

1. Find the 1's complement (invert the bits): `00001 11110`
2. Add 1 to get the true magnitude: `00001 11111`
3. Calculate binary to decimal: , plus  from the 6th bit position = ****.

The result is `-63` , which is exactly correct since .

---

No, it was **not** the case in the previous algorithm. You have just identified the primary difference between a **Logical Shift** and an **Arithmetic Shift**!

Here is exactly how the two shifting methods differ and why the hardware uses them:

### 1. The Previous Algorithm: Logical Shift Right (`Shr EAQ`)

In the first sign-magnitude algorithm, the hardware performed a **Logical Shift Right**.

* **How it works:** It treats the `E`, `A`, and `Q` registers as one continuous 11-bit chain (1 bit for E, 5 for A, 5 for Q). Everything shifts to the right by one position.
* **The Leftmost Bit:** The MSB of `A` is **not** replicated. Instead, the value sitting inside the `E` flip-flop (the carry bit) is pushed into the MSB of `A`. Then, a `0` is pushed into `E`.
* **Proof from the Trace:** Look at Cycle 2 of the first trace table we did:
* Before shift: , 
* After `Shr EAQ`: , 
* Notice how the `1` from  moved into the leftmost spot of . It did not duplicate the `0` that was originally at the front of .



### 2. Booth's Algorithm: Arithmetic Shift Right (`ashr`)

Booth's algorithm performs an **Arithmetic Shift Right** on just the `AC` and `QR` registers (there is no `E` register used for the shift).

* **How it works:** It shifts the bits to the right, but it forces the Most Significant Bit (the sign bit) of `AC` to stay exactly what it was while also shifting it down.
* **Why it must do this:** Booth's algorithm uses 2's complement arithmetic. In 2's complement, the leftmost bit *must* remain a `1` if the number is negative, or a `0` if the number is positive. If you shifted a `0` into a negative number (like logical shift does), you would accidentally turn a negative number into a positive number mid-calculation!
* **Proof from the Trace:** Look at Cycle 4 of the Booth trace table:
* Before shift:  (Negative)
* After `ashr`: 
* The leftmost `1` duplicated itself to keep the overall partial product negative.



**Summary:** Sign-Magnitude uses **Logical Shift** because the signs are handled totally separately in the  and  flip-flops.

* Booth's uses **Arithmetic Shift** because the sign is baked directly into the number, so the hardware must duplicate the sign bit to protect it from being overwritten.
