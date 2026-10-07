# Data Structures and Algorithms Assignment

This repository contains comprehensive, production-grade implementations of **Stack** and **Circular Queue** data structures using fixed-size arrays without relying on any built-in data structure libraries. Implementations are provided in both **C** and **C++** along with detailed algorithmic analysis, edge case handling, and visual representations.

---

## Repository Structure

```text
DSA_ASSIGMENT/
├── .gitignore                      # Git ignore rules for build artifacts
├── Makefile                        # Build automation for Linux/macOS/MinGW
├── build.bat                       # One-click build script for Windows
├── README.md                       # Comprehensive documentation & analysis
├── q1_stack/
│   ├── stack.c                     # Q1: Stack implementation in C
│   └── stack.cpp                   # Q1: Stack implementation in C++
└── q2_circular_queue/
    ├── circular_queue.c            # Q2: Circular Queue implementation in C
    └── circular_queue.cpp          # Q2: Circular Queue implementation in C++
```

---

## Question 1: Stack Using an Array

### 1. Problem Statement
Design and implement a stack using an array without using any built-in stack library. Perform the following operations:
- `PUSH(x)`
- `POP()`
- `PEEK()`
- `DISPLAY()`

The program must handle both **Stack Overflow** and **Stack Underflow** conditions gracefully.

---

### 2. Implementation Details

A stack follows the **Last-In, First-Out (LIFO)** principle. The array-based implementation tracks the position of the latest element using a pointer index variable `top`.

1. **State Initialization:**
   - Stack array `data[MAX_CAPACITY]`
   - `top = -1` (denoting an empty stack)

2. **Operations:**
   - **`isEmpty()`**: Checks if `top == -1`.
   - **`isFull()`**: Checks if `top == MAX_CAPACITY - 1`.
   - **`PUSH(x)`**:
     - *Overflow Check*: If `isFull()`, reject insertion and notify user: `Stack Overflow`.
     - Otherwise, increment `top` (`top = top + 1`) and set `data[top] = x`.
   - **`POP()`**:
     - *Underflow Check*: If `isEmpty()`, reject removal and notify user: `Stack Underflow`.
     - Otherwise, extract `value = data[top]`, decrement `top` (`top = top - 1`), and return `value`.
   - **`PEEK()`**:
     - If `isEmpty()`, report that stack has no elements.
     - Otherwise, read and return `data[top]` without modifying `top`.
   - **`DISPLAY()`**:
     - If `isEmpty()`, display `Stack is empty`.
     - Otherwise, iterate from `top` down to `0` and print each element.

---

### 3. Complexity Analysis (Q1 Additional Task)

| Operation | Time Complexity | Auxiliary Space Complexity | Explanation |
| :--- | :---: | :---: | :--- |
| **`PUSH(x)`** | **$O(1)$** | **$O(1)$** | Direct index calculation and assignment to `data[++top]`. |
| **`POP()`** | **$O(1)$** | **$O(1)$** | Direct index decrement `top--` and value retrieval. |
| **`PEEK()`** | **$O(1)$** | **$O(1)$** | Direct array read at index `data[top]`. |
| **`DISPLAY()`** | **$O(N)$** | **$O(1)$** | Linear traversal of all $N$ elements currently in the stack ($N \le \text{MAX}$). |
| **`isEmpty()` / `isFull()`** | **$O(1)$** | **$O(1)$** | Single integer comparison. |

- **Total Space Complexity:** **$O(M)$**, where $M = \text{MAX\_CAPACITY}$ is the fixed array size allocated in static/stack memory.

---

### 4. Discussion: Fixed-Size Stack & Capacity Overflow (Q1 Additional Task)

#### What happens when stack size is fixed and the user attempts to insert more elements than its capacity?

1. **Stack Overflow Condition:**
   - When a stack has a fixed capacity $M$ and currently contains $M$ elements, `top` points to index $M - 1$.
   - Any subsequent attempt to execute `PUSH(x)` triggers a **Stack Overflow**.

2. **Risks in Unchecked Systems:**
   - If bounds checking is omitted (e.g. naive array access `arr[++top]`), the program writes past the allocated array bounds into adjacent memory.
   - This results in **Undefined Behavior**, including memory corruption, segmentation faults, application crashes, or severe security vulnerabilities (buffer overflow exploits).

3. **Defensive Handling in our Implementation:**
   - Before any insertion, `isFull()` verifies if `top == MAX_CAPACITY - 1`.
   - If true, execution halts for that operation, returning an explicit error message (`[ERROR] Stack Overflow`) and preserving memory safety without terminating the program abnormally.

4. **Static Array vs. Dynamic Resizing Alternatives:**
   - **Fixed-size array:** Fast, zero pointer overhead, predictable memory footprint, but rigid capacity.
   - **Dynamic Array (e.g. geometric doubling):** When full, allocate an array of double the size ($2M$), copy elements, and free the old array. This achieves **amortized $O(1)$ push time**, avoiding hard overflow at the cost of occasional $O(N)$ reallocations and higher peak memory usage.
   - **Linked List Stack:** Dynamic node allocation with no fixed limit (limited only by available system RAM), but incurs $O(N)$ pointer overhead and memory fragmentation.

---

## Question 2: Circular Queue Using an Array

### 1. Problem Statement
Implement a **Circular Queue** using an array supporting:
- `ENQUEUE(x)`
- `DEQUEUE()`
- `FRONT()`
- `DISPLAY()`

The implementation must correctly distinguish between a **full queue** and an **empty queue**.

---

### 2. Implementation Details

A Queue follows the **First-In, First-Out (FIFO)** principle. In a simple linear queue, when elements are dequeued, vacant slots at the front cannot be reused without expensive shifting. A **Circular Queue** solves this by connecting the last index back to the first index conceptually using modulo arithmetic.

1. **State Initialization:**
   - Array `items[QUEUE_CAPACITY]`
   - `front = -1`
   - `rear = -1`

2. **Differentiating Empty vs. Full Queue:**
   - **Empty Queue Condition:**
     $$\text{front} == -1$$
     *(When the last remaining element is dequeued, both `front` and `rear` are explicitly reset back to `-1`)*.
   - **Full Queue Condition:**
     $$(\text{rear} + 1) \pmod{\text{QUEUE\_CAPACITY}} == \text{front}$$
     *(The next position of `rear` circularly wraps around and coincides with `front`)*.
   - **Why this correctly distinguishes Empty from Full:**
     - When the queue is empty, `front == -1`.
     - In modulo arithmetic, $(\text{rear} + 1) \pmod N$ yields a non-negative integer in range $[0, N-1]$. It can **never** equal $-1$.
     - Therefore, `isFull()` evaluates to `false` when the queue is empty, and `isEmpty()` evaluates to `true`.
     - When the queue is full, `front` is a valid non-negative index, and $(\text{rear} + 1) \pmod N == \text{front}$ evaluates to `true`. There is zero ambiguity.

3. **Operations:**
   - **`ENQUEUE(x)`**:
     - Check `isFull()`. If full, trigger `Queue Overflow`.
     - If `isEmpty()`, set `front = 0; rear = 0;`.
     - Else, set `rear = (rear + 1) % QUEUE_CAPACITY`.
     - Store `items[rear] = x`.
   - **`DEQUEUE()`**:
     - Check `isEmpty()`. If empty, trigger `Queue Underflow`.
     - Retrieve `items[front]`.
     - If `front == rear` (single element remaining), reset `front = -1; rear = -1;`.
     - Else, advance `front = (front + 1) % QUEUE_CAPACITY`.
   - **`FRONT()`**:
     - Check `isEmpty()`. If empty, report queue is empty.
     - Else, return `items[front]`.
   - **`DISPLAY()`**:
     - Traverses circularly starting at `i = front` up to `rear` using `i = (i + 1) % QUEUE_CAPACITY`.

---

### 3. Comparison & Additional Tasks (Q2 Additional Task)

#### 1. Why a Circular Queue provides better utilization of memory
- In a **linear queue**, elements are removed from `front` and added at `rear`. Both pointers only increment forward. As elements are dequeued, indices $0, 1, \dots, \text{front}-1$ become unoccupied, but `rear` cannot place incoming elements into them because `rear` only moves to the right. Once `rear == CAPACITY - 1`, no more elements can be inserted, stranding all dequeued memory slots as unusable dead space.
- In a **circular queue**, when `rear` reaches the last physical index (`CAPACITY - 1`) and empty slots exist at indices $0, 1, \dots$, `rear` wraps around to `0` via the modulo formula `(rear + 1) % CAPACITY`. Every single allocated slot can be reused repeatedly, achieving **100% memory utilization**.

#### 2. Time Complexity of ENQUEUE and DEQUEUE
- **`ENQUEUE(x)`**: **$O(1)$** (Constant Time)
  - Evaluates condition `(rear + 1) % N == front` in $O(1)$.
  - Direct modulo increment and array index assignment `items[rear] = x` in $O(1)$.
- **`DEQUEUE()`**: **$O(1)$** (Constant Time)
  - Checks `front == -1` in $O(1)$.
  - Direct value retrieval and index increment `front = (front + 1) % N` in $O(1)$.
  *(Contrast with linear queues that shift elements to maintain index 0: shifting requires $O(N)$ time per dequeue).*

#### 3. Space Complexity of the Queue
- **Total Space Complexity:** **$O(N)$**, where $N = \text{QUEUE\_CAPACITY}$.
  - The array occupies a fixed block of contiguous memory of size $N \times \text{sizeof}(item)$.
- **Auxiliary Space per Operation:** **$O(1)$**
  - All operations (`ENQUEUE`, `DEQUEUE`, `FRONT`, `isFull`, `isEmpty`) require only a few primitive integer pointer variables (`front`, `rear`, `value`).

#### 4. The Problem in Linear Queue when REAR reaches the last index (False Overflow)
- **Problem Name:** **False Overflow** (also known as **Virtual Overflow** or **Memory Starvation**).
- **Explanation:**
  - Suppose a linear queue of size 5 has all 5 slots filled:
    ```text
    Indices: [0]  [1]  [2]  [3]  [4]
    Values:  [10] [20] [30] [40] [50]
             ^FRONT             ^REAR (rear = 4)
    ```
  - Now, perform 3 `DEQUEUE()` operations:
    ```text
    Indices: [0]  [1]  [2]  [3]  [4]
    Values:  [--] [--] [--] [40] [50]
                            ^FRONT   ^REAR (rear = 4)
    ```
  - In a simple linear queue, if a user now attempts to enqueue another element, the program checks if `rear == CAPACITY - 1` (here $4 == 4$).
  - The linear queue declares **"Queue Overflow"** even though positions 0, 1, and 2 are completely vacant!
  - **Resolution:** A Circular Queue eliminates this flaw completely by wrapping `rear` back to index 0:
    ```text
    Indices: [0]  [1]  [2]  [3]  [4]
    Values:  [60] [--] [--] [40] [50]
             ^REAR          ^FRONT
    ```

---

## Compilation and Execution Guide

### Prerequisites
- GCC / G++ (MinGW on Windows, GCC on Linux/macOS)

### 1. Windows (One-Click Build)
Run the included batch script:
```cmd
build.bat
```

Or compile manually using MinGW:
```cmd
# Compile Question 1 (C & C++)
gcc -Wall -Wextra -std=c99 q1_stack\stack.c -o q1_stack\stack_c.exe
g++ -Wall -Wextra -std=c++11 q1_stack\stack.cpp -o q1_stack\stack_cpp.exe

# Compile Question 2 (C & C++)
gcc -Wall -Wextra -std=c99 q2_circular_queue\circular_queue.c -o q2_circular_queue\queue_c.exe
g++ -Wall -Wextra -std=c++11 q2_circular_queue\circular_queue.cpp -o q2_circular_queue\queue_cpp.exe
```

### 2. Linux / macOS
Using `make`:
```bash
make
```

### 3. Running the Programs

#### Question 1: Stack
```bash
# Run C version
./q1_stack/stack_c.exe       # Windows
./q1_stack/stack_c           # Linux/macOS

# Run C++ version
./q1_stack/stack_cpp.exe     # Windows
./q1_stack/stack_cpp         # Linux/macOS
```

#### Question 2: Circular Queue
```bash
# Run C version
./q2_circular_queue/queue_c.exe   # Windows
./q2_circular_queue/queue_c       # Linux/macOS

# Run C++ version
./q2_circular_queue/queue_cpp.exe # Windows
./q2_circular_queue/queue_cpp     # Linux/macOS
```

---

## Verification and Test Scenarios

### Stack Test Run Demonstration
```text
Pushing elements: 10, 20, 30, 40, 50 -> Stack Full (5/5)
Attempting Push 60                  -> [ERROR] Stack Overflow! Capacity (5) reached.
Display                             -> [TOP: 50, 40, 30, 20, 10]
Peek                                -> 50
Pop                                 -> Popped 50
Pop until empty                     -> 40, 30, 20, 10 popped
Attempting Pop                      -> [ERROR] Stack Underflow! Cannot pop from empty stack.
```

### Circular Queue Test Run Demonstration
```text
Enqueue: 100, 200, 300, 400, 500   -> Queue Full [ 100 | 200 | 300 | 400 | 500 ]
Attempting Enqueue 600             -> [ERROR] Queue Overflow! Queue is full.
Dequeue 2 elements                 -> 100, 200 dequeued. Front moves to index [2].
                                      Slots: [ _ | _ | 300 | 400 | 500 ]
Enqueue 600, 700                   -> Wraps around to index [0] and [1]!
                                      Slots: [ 600 | 700 | 300 | 400 | 500 ]
                                      Front: index 2 (value 300), Rear: index 1 (value 700)
Attempting Enqueue 800             -> [ERROR] Queue Overflow! (Capacity reached)
```
