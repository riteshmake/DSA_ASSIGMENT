/**
 * Assignment: Data Structures and Algorithms
 * Question 2: Circular Queue Implementation using Array (C++)
 * 
 * Features:
 *  - Encapsulated CircularQueue class
 *  - enqueue(x) with Queue Overflow handling
 *  - dequeue() with Queue Underflow handling
 *  - front() / peek
 *  - display() with circular traversal and array slot visualization
 *  - Distinct state checks for Empty vs Full
 *  - Interactive menu-driven console interface
 */

#include <iostream>
#include <limits>

constexpr int QUEUE_CAPACITY = 5;

class CircularQueue {
private:
    int items[QUEUE_CAPACITY];
    int frontIndex;
    int rearIndex;

public:
    CircularQueue() : frontIndex(-1), rearIndex(-1) {}

    /**
     * Empty condition:
     * When frontIndex is -1, the queue contains no elements.
     */
    bool isEmpty() const {
        return (frontIndex == -1);
    }

    /**
     * Full condition:
     * When (rear + 1) % QUEUE_CAPACITY == front, the rear pointer has wrapped
     * around and reached the position just before the front pointer.
     */
    bool isFull() const {
        return ((rearIndex + 1) % QUEUE_CAPACITY == frontIndex);
    }

    int size() const {
        if (isEmpty()) return 0;
        if (rearIndex >= frontIndex) {
            return rearIndex - frontIndex + 1;
        }
        return QUEUE_CAPACITY - (frontIndex - rearIndex - 1);
    }

    int capacity() const {
        return QUEUE_CAPACITY;
    }

    int getFrontIndex() const {
        return frontIndex;
    }

    int getRearIndex() const {
        return rearIndex;
    }

    /**
     * ENQUEUE(x): Inserts an element at rear.
     * Handles Queue Overflow condition.
     * 
     * Time Complexity:  O(1)
     * Space Complexity: O(1) auxiliary
     */
    bool enqueue(int value) {
        if (isFull()) {
            std::cout << "\n[ERROR] Queue Overflow! Cannot enqueue " << value 
                      << ". Queue is full (Capacity: " << QUEUE_CAPACITY 
                      << ", Front: " << frontIndex << ", Rear: " << rearIndex << ").\n";
            return false;
        }

        if (isEmpty()) {
            frontIndex = 0;
            rearIndex = 0;
        } else {
            rearIndex = (rearIndex + 1) % QUEUE_CAPACITY;
        }

        items[rearIndex] = value;
        std::cout << "\n[SUCCESS] Enqueued " << value << " at index [" << rearIndex 
                  << "]. (Front: " << frontIndex << ", Rear: " << rearIndex 
                  << ", Occupied: " << size() << "/" << QUEUE_CAPACITY << ")\n";
        return true;
    }

    /**
     * DEQUEUE(): Removes and returns the element at front.
     * Handles Queue Underflow condition.
     * 
     * Time Complexity:  O(1)
     * Space Complexity: O(1) auxiliary
     */
    bool dequeue(int &dequeuedValue) {
        if (isEmpty()) {
            std::cout << "\n[ERROR] Queue Underflow! Cannot dequeue from an empty queue.\n";
            return false;
        }

        dequeuedValue = items[frontIndex];
        std::cout << "\n[SUCCESS] Dequeued " << dequeuedValue 
                  << " from index [" << frontIndex << "].\n";

        if (frontIndex == rearIndex) {
            // Queue had only one element; reset to empty
            frontIndex = -1;
            rearIndex = -1;
            std::cout << "[INFO] Queue is now completely empty (frontIndex & rearIndex reset to -1).\n";
        } else {
            frontIndex = (frontIndex + 1) % QUEUE_CAPACITY;
            std::cout << "[INFO] New front index: " << frontIndex 
                      << ", Rear index: " << rearIndex 
                      << " (Remaining elements: " << size() << ")\n";
        }

        return true;
    }

    /**
     * FRONT(): Views the front element without removing it.
     * 
     * Time Complexity:  O(1)
     * Space Complexity: O(1) auxiliary
     */
    bool front(int &frontValue) const {
        if (isEmpty()) {
            std::cout << "\n[NOTICE] Queue is empty! No front element available.\n";
            return false;
        }
        frontValue = items[frontIndex];
        std::cout << "\n[INFO] Front element is: " << frontValue 
                  << " at index [" << frontIndex << "].\n";
        return true;
    }

    /**
     * DISPLAY(): Displays elements in logical order from front to rear,
     * plus physical array memory layout.
     * 
     * Time Complexity:  O(N) where N is the current size
     * Space Complexity: O(1) auxiliary
     */
    void display() const {
        if (isEmpty()) {
            std::cout << "\n[INFO] Queue is empty: [ ]\n";
            return;
        }

        std::cout << "\n--- Circular Queue State (Capacity: " << QUEUE_CAPACITY 
                  << ", Occupied: " << size() << ") ---\n";
        std::cout << "Logical Order\tArray Index\tValue\tRole\n";
        std::cout << "--------------------------------------------------------\n";

        int i = frontIndex;
        int order = 1;
        while (true) {
            std::string role = "";
            if (i == frontIndex && i == rearIndex) {
                role = "<-- FRONT & REAR";
            } else if (i == frontIndex) {
                role = "<-- FRONT";
            } else if (i == rearIndex) {
                role = "<-- REAR";
            }

            std::cout << "  #" << order << "          \t[" << i << "]        \t" 
                      << items[i] << "   \t" << role << "\n";

            if (i == rearIndex) {
                break;
            }
            i = (i + 1) % QUEUE_CAPACITY;
            order++;
        }
        std::cout << "--------------------------------------------------------\n";

        // Memory slots view
        std::cout << "Array Memory Slots [0.." << QUEUE_CAPACITY - 1 << "]:\n[";
        for (int k = 0; k < QUEUE_CAPACITY; ++k) {
            bool occupied = false;
            if (!isEmpty()) {
                if (frontIndex <= rearIndex) {
                    occupied = (k >= frontIndex && k <= rearIndex);
                } else {
                    occupied = (k >= frontIndex || k <= rearIndex);
                }
            }
            if (occupied) {
                std::cout << " " << items[k] << " ";
            } else {
                std::cout << " _ ";
            }
            if (k < QUEUE_CAPACITY - 1) std::cout << "|";
        }
        std::cout << "]\n";
    }
};

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    CircularQueue q;
    int choice = 0;
    int value = 0;

    std::cout << "=========================================================\n";
    std::cout << "  DSA ASSIGNMENT - Q2: CIRCULAR QUEUE USING ARRAY (C++)  \n";
    std::cout << "  Queue Capacity: " << QUEUE_CAPACITY << "\n";
    std::cout << "=========================================================\n";

    while (true) {
        std::cout << "\n---------------- CIRCULAR QUEUE MENU ----------------\n";
        std::cout << " 1. ENQUEUE(x)  - Insert element into queue\n";
        std::cout << " 2. DEQUEUE()   - Remove element from queue\n";
        std::cout << " 3. FRONT()     - View front element\n";
        std::cout << " 4. DISPLAY()   - Display elements & memory layout\n";
        std::cout << " 5. CHECK STATUS (isEmpty / isFull / Front / Rear)\n";
        std::cout << " 6. EXIT\n";
        std::cout << "-----------------------------------------------------\n";
        std::cout << "Enter your choice (1-6): ";

        if (!(std::cin >> choice)) {
            std::cout << "\n[ERROR] Invalid input. Please enter a valid number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: {
                std::cout << "Enter integer value to enqueue: ";
                if (!(std::cin >> value)) {
                    std::cout << "\n[ERROR] Invalid input. Integer required.\n";
                    clearInput();
                } else {
                    q.enqueue(value);
                }
                break;
            }
            case 2: {
                int dequeuedVal = 0;
                q.dequeue(dequeuedVal);
                break;
            }
            case 3: {
                int frontVal = 0;
                q.front(frontVal);
                break;
            }
            case 4:
                q.display();
                break;
            case 5:
                std::cout << "\n--- Circular Queue Status ---\n";
                std::cout << "Is Empty: " << (q.isEmpty() ? "YES" : "NO") << "\n";
                std::cout << "Is Full : " << (q.isFull() ? "YES" : "NO") << "\n";
                std::cout << "Front Index: " << q.getFrontIndex() << "\n";
                std::cout << "Rear  Index: " << q.getRearIndex() << "\n";
                std::cout << "Current Count: " << q.size() << " / " << q.capacity() << "\n";
                break;
            case 6:
                std::cout << "\nExiting Circular Queue Program. Goodbye!\n";
                return 0;
            default:
                std::cout << "\n[ERROR] Choice out of range. Please choose between 1 and 6.\n";
                break;
        }
    }

    return 0;
}
