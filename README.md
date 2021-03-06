*"We are like butterflies who flutter for a day and think it is forever." - Carl Sagan (Ch 2, [Cosmos](https://www.amazon.com/Cosmos-Carl-Sagan/dp/0375508325))*

Implementation of some common data structures and algorithms using C++11. This is mostly a recreational activity. The main purpose is to learn and to have fun.

Implementations from C++ standard library and other notable libraries (e.g. `boost`) are almost always more preferable for production quality software. I don't think this will have much value ever other than learning and having fun. You have been warned.

The [references section](https://github.com/taskinoor/algorithms/blob/master/REFERENCES.md) must be consulted first before checking out a particular code.

Unit tests are present for each data structure and algorithm. Main codes are inside `alg` directory (and inside `alg` namespace), unit test codes are inside `tests` directory (and inside `algtest` namespace). There is a single `makefile` inside `tests` which can build all at once.

**List of data structures and algorithms:**

* Data Structure
	* Deque
	* Extendable Array (Vector)
	* Linked List (Doubly)
	* Stack (Fixed size)
	* Queue (Fixed size)
	* Heap (Binary)
	* Priority Queue
	* Tree
		* Binary Tree
		* Binary Search Tree
		* Order Statistic Tree
		* Red Black Tree
		* Traversal (Binary)
			* Preorder
			* Postorder
			* Inorder
			* Euler Tour
* Sorting
	* Heapsort
	* Merge Sort
	* Quicksort
		* Lomuto Partition
		* Randomized Partition
		* Hoare partition
	* Bubble Sort
	* Insertion Sort
	* Selection Sort
* Searching
	* Binary Search
	* Linear Search
	* Range Queries (on BST)
* Divide and Conquer
	* Maximum Subarray
	* Strassen's Matrix Multiplication
* Dynamic Programming
	* Maximum Subarray
* Numeric
	* Matrix (Basic Operations)
* Puzzle
	* Josephus problem (1. Using Queue, 2. Using Order Statistic Tree)


**Development environments:**
* Ubuntu 16.04.2 (WSL)
* GCC 7.3.0
* Valgrind 3.13.0

**Running all tests:**
```
$ cd algorithms/tests/
$ make
$ ./runner.out --gtest_shuffle
$ valgrind ./runner.out --gtest_shuffle
```
