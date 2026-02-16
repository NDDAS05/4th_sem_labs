# Addressing modes

Here is a detailed discussion of the various addressing modes.

**Addressing modes** describe the specific methods a processor uses to interpret the operand field of an instruction to locate the necessary data (the effective address).

### **Basic Addressing Modes**
These modes differ primarily in where the data is located relative to the instruction:

*   **Immediate Addressing:** The operand is a constant value located explicitly within the instruction itself. No memory address calculation is required to fetch the data.
*   **Direct Addressing:** The instruction contains the specific memory address of the operand. The processor performs one fetch operation to retrieve the data from that location.
*   **Indirect Addressing:** The instruction contains an address (W) that points to a memory location holding the **actual address** (X) of the operand.
    *   **Mechanism:** To get the data, the processor goes to address W, reads address X, and then goes to address X to get the operand.
    *   **Performance:** This is slower because it requires two memory fetch operations.
    *   **Benefit:** It allows the address of the operand to be changed dynamically by modifying the content of W.

### **Displacement and Register Modes**
These modes calculate the effective address by combining a register value with a constant or address field:

*   **Relative Addressing:** The effective address is calculated by adding a **displacement (D)** (found in the operand field) to the contents of a register (R).
    *   **Benefits:** This reduces instruction length because the full address doesn't need to be stored. It allows for **code relocation**, meaning a block of code can be moved to a different region of memory without invalidating the addresses within it.
*   **Indexed Addressing:** Designed efficiently for handling arrays or lists of data.
    *   **Mechanism:** The instruction contains the base address of the array (D), and an **Index Register (R)** contains the specific index ($i$). The effective address is calculated as $D + R$.
    *   **Benefit:** By simply changing the value in the index register, a single instruction can access any item in the data list.

### **Specialized Addressing Modes**
These modes are designed for specific data structures or sequential processing:

*   **Autoindexing (Predecrement/Postincrement):** These are variations of indexed addressing used to automatically step through sequential items in memory (like arrays).
    *   **Predecrement:** The register content is decremented **before** the instruction executes (e.g., $-(A3)$).
    *   **Postincrement:** The register content is incremented **after** the instruction executes (e.g., $(A3)+$).
*   **Stack Addressing:** This mode utilizes a pushdown stack in memory, managed by a **Stack Pointer (SP)** register.
    *   **Implicit Operands:** In a "Zero-address machine," operands are assumed to be at the top of the stack.
    *   **Operations:**
        *   **PUSH:** Writes a new item to the top of the stack and updates the SP.
        *   **POP:** Reads and removes the item at the top of the stack and updates the SP.

### **Summary of Operand Handling**
The choice of addressing mode often correlates with the machine architecture type:
*   **Three-address machines** allow explicit access to two source operands and one destination.
*   **One-address machines** (Accumulator-based) heavily imply the second operand is the accumulator.
*   **Zero-address machines** rely entirely on Stack addressing.
