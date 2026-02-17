# Sequence Counter Method for Control Unit Timing

### Definition

The sequence counter method is a technique used in the control unit of a CPU to generate timing signals required to perform the steps of an instruction cycle in proper sequence.

* It uses a mod-k counter and a decoder.

* Each count corresponds to one timing signal (phase signal).

* These timing signals activate specific control lines required for each step of instruction execution.



---

### Basic Components

1. **Sequence Counter (Mod-k counter)**

Counts clock pulses from 0 to k–1.

Each count represents one step in the instruction cycle.



2. **Decoder (1-of-k decoder)**

Converts counter output into k timing signals:




$\phi_0, \phi_1, \phi_2, \dots, \phi_{k-1}$

3. **Clock**

Provides pulses to advance the counter.



4. **Flip-Flop (FF)**

Controls start (Begin) and stop (End) of sequence counter.



5. **Logic Circuit**

Combines timing signals and control inputs to generate required control signals.





---

### Working Principle

**Step-by-Step Operation**

1. **When `Begin = 1` and `End = 0`**

* Flip-flop output becomes `1` .

* Clock is enabled to the sequence counter.

* Counter starts **counting clock pulses.**



2. **At each clock pulse:**

* Counter advances by 1.

* Decoder activates corresponding timing signal:




`phi_i`  becomes active at count `i`

3. **Each timing signal activates control signals required for that step.**


4. **When instruction completes:**

* End signal becomes 1.

* Counter is reset.

* Next instruction cycle begins.

---

### Timing Signal Generation

At `i` -th clock pulse:

{Counter value} = i

{Decoder output} = phi_i

phi_i -> Activates control signals for step i

Thus, sequence counter generates ordered timing signals.


---

## Example: Mod-16 Sequence Counter


Counter counts from:

0 to 15

Decoder generates timing signals:


\phi_0, \phi_1, \phi_2, \dots, \phi_{15}

Each signal corresponds to one micro-operation.


---

## CPU Instruction Cycle Using Sequence Counter

Each instruction cycle consists of several steps:

Step 1: Transfer PC to MAR

MAR <- PC

Timing signal: 


---

Step 2: Fetch instruction from Memory

IR <- M[MAR]

Timing signal: 


---

Step 3: Increment PC and Decode Instruction

PC <- PC + 1

Timing signal: 


---

Step 4: Transfer Operand Address to MAR

MAR <- IR(address)

Timing signal: 


---

Step 5: Fetch Operand from Memory

DR <- M[MAR]

Timing signal: 


---

Step 6: Execute Instruction

Example:

AC <-AC + DR

Timing signal: 


---

Control Signal Generation

Control signals are generated using:

C_{out} = f(\phi_i, C_{in})

Where:

 * Phi_i = Timing signal

 * C_in = Control inputs (opcode, flags, etc.)

 * C_out= Control signals to CPU components


Logic circuit combines:

* Timing signals

* Instruction opcode

* Status flags


to produce correct control signals.


---

### Role of Begin and End Signals

Begin Signal

* Starts sequence counter

* Enables clock input


End Signal

* Stops sequence counter

* Resets counter to 0

* Prepares CPU for next instruction



---

## Mathematical Representation

Let:

Sequence counter output:

Q = (q_n, q_{n-1}, \dots, q_0)

Decoder output:

\phi_i = 1 \quad \text{if counter value = i}

Control signals:

C_{out} = Logic(\phi_i, opcode, flags)


---

Block Diagram Explanation (Written Form)

The sequence counter method consists of:

Flip-flop to enable or disable counting

Mod-k sequence counter

Decoder to generate timing signals

Logic circuit to generate control signals

Reset circuit to restart instruction cycle


Clock pulses drive the sequence counter, and decoder generates timing signals which activate control signals in proper sequence.


---

Advantages

1. Simple and easy to design


2. Provides ordered timing signals


3. Suitable for hardwired control unit


4. Fast operation




---

Disadvantages

1. Requires more hardware for large instruction sets


2. Less flexible compared to microprogrammed control


3. Difficult to modify instruction sequence




---

Key Points to Remember (Exam Revision)

Sequence counter generates timing signals.

Mod-k counter produces k states.

Decoder converts count into timing signals.

Each timing signal activates one step of instruction cycle.

Logic circuit combines timing signals and control inputs.

End signal resets counter.



---

Short Exam Definition (2-Mark Answer)

The sequence counter method uses a mod-k counter and decoder to generate timing signals (ϕ₀, ϕ₁, …, ϕₖ) for controlling the sequence of micro-operations in an instruction cycle. Each clock pulse advances the counter, activating one timing signal at a time. These signals are used to generate control signals for CPU operations.


---

Long Answer Conclusion

Thus, the sequence counter method is an important technique used in hardwired control units to generate properly timed control signals required for executing instructions step by step in a CPU.


---

# Sequence Counter Method – 1 Page Revision Sheet

## Definition
Sequence counter method uses a Mod-k counter and decoder to generate timing signals (ϕ0, ϕ1, …, ϕk) that control the step-by-step execution of instructions in CPU.

Each clock pulse → Counter increments → Decoder activates one timing signal → Control signals generated.

---

## Basic Components

1. Sequence Counter (Mod-k counter)
   - Counts from 0 to k-1
   - Each count = one timing step

2. Decoder (1-of-k decoder)
   - Converts counter output into timing signals
   - Outputs: ϕ0, ϕ1, ϕ2, …, ϕk-1
   - Only one active at a time

3. Clock
   - Provides pulses to advance counter

4. Flip-Flop (Start/Stop control)
   - Begin = Start counter
   - End = Stop and reset counter

5. Logic Circuit
   - Combines timing signals and control inputs
   - Generates required control signals

---

## Working Principle

Begin = 1, End = 0 → Counter starts counting

At ith clock pulse:
Counter value = i  
Decoder output = ϕi active  

ϕi activates control signals for step i

End signal → Counter reset → Next instruction cycle begins

---

## Timing Signal Generation

Counter → Decoder → Timing signals:

ϕ0, ϕ1, ϕ2, …, ϕk-1

Each signal corresponds to one micro-operation.

Example:
ϕ0 → Fetch step  
ϕ1 → Decode step  
ϕ2 → Execute step  

---

## Instruction Cycle Steps with Timing Signals

ϕ0 : MAR ← PC  
ϕ1 : IR ← M[MAR]   (Fetch instruction)  
ϕ2 : PC ← PC + 1   (Increment PC)  
ϕ3 : MAR ← IR(address)  
ϕ4 : DR ← M[MAR]   (Fetch operand)  
ϕ5 : Execute instruction  

Each step controlled by one timing signal.

---

## Control Signal Generation Equation

Cout = f(ϕi, Cin)

Where:
ϕi = Timing signal  
Cin = Opcode, flags, control inputs  
Cout = Control signals  

Logic circuit combines timing signal + instruction information.

---

## Block Flow (Important for Diagram)

Clock → Sequence Counter → Decoder → Timing signals (ϕ0…ϕk)

Timing signals + Control inputs → Logic circuit → Control signals

End signal → Reset counter

---

## Example: Mod-16 Counter

Counts: 0 to 15

Decoder outputs:
ϕ0, ϕ1, ϕ2, …, ϕ15

Each used for one control step.

---

## Advantages

• Simple design  
• Fast operation  
• Generates proper sequence  
• Suitable for hardwired control unit  

---

## Disadvantages

• Less flexible  
• Hard to modify  
• Hardware increases for large instruction sets  

---

## Exam Definition (Write This)

Sequence counter method uses a Mod-k counter and decoder to generate timing signals that control the sequence of micro-operations in an instruction cycle. Each clock pulse advances the counter and activates one timing signal which generates control signals required for CPU operations.

---

## Keywords to Remember

Sequence counter  
Mod-k counter  
Decoder  
Timing signals (ϕi)  
Control signals  
Instruction cycle  
Begin and End signal  
Logic circuit