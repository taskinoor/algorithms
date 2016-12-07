Implementation of some common data structures and algorithms using C++ (including C++11). The main purpose of this is to learn, and that's why every implementation contains reference from where it can be learned.

There are unit tests for each data structure and algorithm. Main codes are inside `alg` directory (and inside `alg` namespace), unit test codes are inside `tests` directory (and inside `algtest` namespace). There is a single `makefile` inside `tests` which can build all at once.

[Google Test Framework](https://github.com/google/googletest) is used as unit testing framework. All codes are compiled using `g++ 4.8.4` on `Ubuntu 14.04` with warnings on (`-Wall -Wextra`). `valgrind 3.10.1` is used to check for memory related issues. The whole development environment can be found in [this Vagrant box](https://github.com/taskinoor/dev-box).

Here is the list of data structures and algorithms implemented so far:

* Data Structure
	* Deque
	* Extendable Array
	* Linked List (Doubly)
	* Queue (Fixed size)
	* Stack (Fixed size)
	* Tree
		* Binary Tree
		* Binary Search Tree
		* Order Statistic Tree
		* Red Black Tree
		* Traversal (Binary)
			* Preorder (non-recursive iterator using stack)
			* Postorder (non-recursive iterator using stack)
			* Inorder (non-recursive iterator using stack)
			* Euler Tour (recursive)
* Dynamic Programming
	* Maximum Subarray
* Miscellaneous
	* Josephus problem (1. Using Queue, 2. Using Order Statistic Tree)
* Searching
	* Binary Search
	* Linear Search
	* Range Queries (on BST)
* Sorting
	* Bubble Sort
	* Insertion Sort
	* Merge Sort
	* Selection Sort
