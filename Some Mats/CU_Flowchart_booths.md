# Hardwared CU: Booths Algo Flowchart

This flowchart illustrates the State Table Method applied to a Control Unit (CU) specifically for Booth’s Multiplication Algorithm. It maps high-level operations to specific hardware control signals and states.

1. The Start and Initialization (State S_1)
The process begins with the "Start" signal.
 * Operations: Three registers are initialized: A \leftarrow 0 (Accumulator), Q \leftarrow 0 (Multiplier's extra bit), and a count \leftarrow n (number of bits).
 * State & Signals: This corresponds to State S_1. To execute these transfers, the Control Unit activates signals \{C_9, C_{10}\}. These are the specific wires that trigger the "clear" or "load" functions on those registers.
2. The Decision Point (Checking Q_0Q_{-1})
The diamond shape represents a conditional check of the two least significant bits used in Booth’s algorithm: Q_0 (last bit of the multiplier) and Q_{-1} (the extra bit initialized to 0).
 * Case 10: If the bits are 10, the flow goes left.
   * Action: A \leftarrow A - M (Subtract the multiplicand from the accumulator).
   * State & Signals: This is State S_3, activating signals \{C_2, C_3, C_4, C_5\} to perform the subtraction.
 * Case 01: If the bits are 01, the flow goes right.
   * Action: A \leftarrow A + M (Add the multiplicand to the accumulator).
   * State & Signals: This is State S_2, activating signals \{C_2, C_3, C_4\}.
 * Case 00 or 11: If the bits are identical, no addition or subtraction is needed. The flow goes straight down to the shift operation.
3. The Arithmetic Shift (State S_4)
Regardless of whether an add/subtract happened or the bits were equal, the algorithm moves to the ashr (Arithmetic Shift Right) step.
 * Action: The combined bits of A and Q are shifted right to prepare for the next cycle.
 * State & Signals: This is State S_4, activating signals \{C_0, C_1\}.
Key Concepts from the Image
 * Hardwired Control: The labels like S_i and \{C_n\} show that the Control Unit is essentially a "state machine." Each state (S) tells the hardware which control wires (C) to turn "ON" for that specific clock cycle.
 * State Table Link: The table at the top of your image defines the logic for this flowchart. For example, if you are in State S_1 and receive a specific input I_j (like the start button), the table tells the machine to move to the next state and which output signals (Z_{ij}) to fire.
 * Disadvantage: As noted on the right of your image, this method gets very messy (the table grows exponentially) as you add more states or more complex inputs.
Would you like me to explain what those specific control signals (like C_2 or C_9) usually represent in a typical CPU design?
