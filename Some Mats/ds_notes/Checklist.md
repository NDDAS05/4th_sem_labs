# Checklist: PDF 2

### **1. Instruction Set Fundamentals**
*   **Basic Components:** Understand the roles of the **Opcode field** (operation specification) and **Operand field** (data or address).
*   **Instruction Formats:** Study the difference between explicit and implicit operands.
*   **Machine Classifications:** Differentiate between processor types based on the number of addresses per instruction:
    *   **Three-address:** (e.g., `ADD Z, X, Y`)
    *   **Two-address:** (e.g., `ADD X, Y`)
    *   **One-address:** Uses an Accumulator (e.g., `ADD X`)
    *   **Zero-address:** Uses a Stack (e.g., `PUSH`, `POP`)

### **2. Addressing Modes**
*   **Basic Modes:** Be able to explain Immediate, Direct, and Indirect addressing.
*   **Advanced Modes:**
    *   **Relative Addressing:** Uses a displacement and PC; allows for code relocation.
    *   **Indexed Addressing:** Uses an index register for arrays; understand Predecrement and Postincrement (Autoindexing).
    *   **Stack Addressing:** Understand `PUSH` and `POP` operations and the role of the Stack Pointer (SP).

### **3. Opcode Optimization**
*   **Encoding Types:** Compare **Fixed-length opcodes** (easier decoding) vs. **Variable-length opcodes** (saves storage).
*   **Huffman Coding:** Study how to calculate optimal opcode lengths based on instruction probability to minimize average bit usage.

### **4. Processor Architecture**
*   **RISC vs. CISC:** Compare their characteristics:
    *   **RISC:** Simple/fixed instructions, single-cycle execution, hardwired control, heavy reliance on compilers.
    *   **CISC:** Complex/variable instructions, microprogrammed control, specialized tasks handled by hardware.
*   **Instruction Cycle:** Review the specific steps in the **Fetch** and **Execute** cycles and how control signals are generated.

### **5. Computer Arithmetic & Hardware**
*   **Addition & Subtraction:**
    *   Hardware logic for **Signed-Magnitude** vs. **Signed 2's Complement**.
    *   How **Overflow** is detected (especially using the `V` flag and carry bits).
*   **Multiplication:**
    *   Standard hardware implementation (Shift and Add).
    *   **Booth’s Algorithm:** Learn how it speeds up multiplication by handling strings of 0s and 1s in signed 2's complement numbers.
*   **Division:**
    *   Understand the division algorithm for fixed-point binary numbers (comparing partial remainders, shifting, and restoring).
    *   **Divide Overflow:** Conditions that trigger an overflow error.

### **6. Instruction Categories**
*   Familiarize yourself with the five major groups: **Arithmetic**, **Logical**, **Data Transfer**, **Program Control**, and **I-O** instructions.
