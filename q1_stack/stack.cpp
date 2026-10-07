/**
 * Assignment: Data Structures and Algorithms
 * Question 1: Stack Implementation using Array (C++)
 * 
 * Features:
 *  - Encapsulated Stack class with private data members
 *  - push(x) with Stack Overflow handling
 *  - pop() with Stack Underflow handling
 *  - peek()
 *  - display()
 *  - Interactive menu-driven console interface
 */

#include <iostream>
#include <limits>

constexpr int MAX_CAPACITY = 5;

class Stack {
private:
    int data[MAX_CAPACITY];
    int topIndex;

public:
    Stack() : topIndex(-1) {}

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == MAX_CAPACITY - 1;
    }

    int size() const {
        return topIndex + 1;
    }

    int capacity() const {
        return MAX_CAPACITY;
    }

    /**
     * PUSH(x): Adds an element to the top of the stack.
     * Handles Stack Overflow condition.
     * 
     * Time Complexity:  O(1)
     * Space Complexity: O(1) auxiliary
     */
    bool push(int value) {
        if (isFull()) {
            std::cout << "\n[ERROR] Stack Overflow! Cannot push " << value 
                      << ". Maximum capacity (" << MAX_CAPACITY << ") reached.\n";
            return false;
        }
        data[++topIndex] = value;
        std::cout << "\n[SUCCESS] Successfully pushed " << value 
                  << " onto the stack. (Current size: " << size() << "/" << MAX_CAPACITY << ")\n";
        return true;
    }

    /**
     * POP(): Removes and retrieves the top element.
     * Handles Stack Underflow condition.
     * 
     * Time Complexity:  O(1)
     * Space Complexity: O(1) auxiliary
     */
    bool pop(int &poppedValue) {
        if (isEmpty()) {
            std::cout << "\n[ERROR] Stack Underflow! Cannot pop from an empty stack.\n";
            return false;
        }
        poppedValue = data[topIndex--];
        std::cout << "\n[SUCCESS] Successfully popped " << poppedValue 
                  << " from the stack. (Remaining elements: " << size() << ")\n";
        return true;
    }

    /**
     * PEEK(): Inspects the top element without removing it.
     * 
     * Time Complexity:  O(1)
     * Space Complexity: O(1) auxiliary
     */
    bool peek(int &topValue) const {
        if (isEmpty()) {
            std::cout << "\n[NOTICE] Stack is empty! No element to peek.\n";
            return false;
        }
        topValue = data[topIndex];
        std::cout << "\n[INFO] Top element is: " << topValue 
                  << " (Index: " << topIndex << ")\n";
        return true;
    }

    /**
     * DISPLAY(): Displays all elements from top to bottom.
     * 
     * Time Complexity:  O(N) where N is the current size
     * Space Complexity: O(1) auxiliary
     */
    void display() const {
        if (isEmpty()) {
            std::cout << "\n[INFO] Stack is empty: [ ]\n";
            return;
        }

        std::cout << "\n--- Current Stack (Capacity: " << MAX_CAPACITY 
                  << ", Occupied: " << size() << ") ---\n";
        std::cout << "Position\tIndex\tValue\n";
        std::cout << "----------------------------------------\n";
        for (int i = topIndex; i >= 0; --i) {
            if (i == topIndex) {
                std::cout << "[TOP] -> \t[" << i << "]\t" << data[i] << "\n";
            } else {
                std::cout << "         \t[" << i << "]\t" << data[i] << "\n";
            }
        }
        std::cout << "----------------------------------------\n";
    }
};

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Stack stack;
    int choice = 0;
    int value = 0;

    std::cout << "==================================================\n";
    std::cout << "   DSA ASSIGNMENT - Q1: STACK USING ARRAY (C++)   \n";
    std::cout << "   Stack Capacity: " << MAX_CAPACITY << "\n";
    std::cout << "==================================================\n";

    while (true) {
        std::cout << "\n------------- STACK OPERATIONS -------------\n";
        std::cout << " 1. PUSH(x)   - Insert element\n";
        std::cout << " 2. POP()     - Remove top element\n";
        std::cout << " 3. PEEK()    - View top element\n";
        std::cout << " 4. DISPLAY() - Display all elements\n";
        std::cout << " 5. CHECK STATUS (isEmpty / isFull / Size)\n";
        std::cout << " 6. EXIT\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "Enter your choice (1-6): ";

        if (!(std::cin >> choice)) {
            std::cout << "\n[ERROR] Invalid input. Please enter a valid number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: {
                std::cout << "Enter integer value to push: ";
                if (!(std::cin >> value)) {
                    std::cout << "\n[ERROR] Invalid input. Integer required.\n";
                    clearInput();
                } else {
                    stack.push(value);
                }
                break;
            }
            case 2: {
                int poppedVal = 0;
                stack.pop(poppedVal);
                break;
            }
            case 3: {
                int topVal = 0;
                stack.peek(topVal);
                break;
            }
            case 4:
                stack.display();
                break;
            case 5:
                std::cout << "\n--- Stack Status ---\n";
                std::cout << "Is Empty: " << (stack.isEmpty() ? "YES" : "NO") << "\n";
                std::cout << "Is Full : " << (stack.isFull() ? "YES" : "NO") << "\n";
                std::cout << "Current Size: " << stack.size() << " / " << stack.capacity() << "\n";
                break;
            case 6:
                std::cout << "\nExiting Stack Program. Goodbye!\n";
                return 0;
            default:
                std::cout << "\n[ERROR] Choice out of range. Please choose between 1 and 6.\n";
                break;
        }
    }

    return 0;
}
