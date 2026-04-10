# Task Management System v2 — Binary Search Tree

An enhanced console-based Task Management System written in C, 
built as part of the COMP2421 Data Structures course at Birzeit University.
This version upgrades the linked list implementation to a Binary Search Tree (BST)
for improved search and sort performance.

## What it does
- Load tasks from a file (`tasks.txt`) into a BST ordered by Task ID
- Add and delete tasks while maintaining BST structure
- Search for tasks by Task Name
- Mark tasks as performed without removing them from the tree
- View unperformed tasks sorted by Task Name (in-order traversal)
- View performed tasks sorted by Task ID
- Restructure the BST based on Task Name, Date, or Duration
- Display tree statistics: height, size, number of leaves, internal nodes

## Data Structure Used
- **Binary Search Tree (BST)** — all operations (insert, delete, search)
  are implemented with time and space complexity in mind

## Time Complexities
| Operation | Average Case | Worst Case |
|-----------|-------------|------------|
| Search    | O(log n)    | O(n)       |
| Insert    | O(log n)    | O(n)       |
| Delete    | O(log n)    | O(n)       |

## How to Run

### Compile
gcc task_manager_bst.c -o task_manager_bst

### Run
./task_manager_bst

Make sure `tasks.txt` is in the same folder before running.

## Input Format
Each line in `tasks.txt` follows this format:
ID#TaskName#Date#Duration(hours)

Example:
10#meeting#22/3/2025#1.5
101#attend lecture#25/3/2025#3

## Menu Options
1. Load Tasks File
2. Add a New Task
3. Delete a Task
4. Search for a Task (by Task Name)
5. Perform a Task
6. View Unperformed Tasks (sorted by Task Name)
7. View Performed Tasks (sorted by Task ID)
8. Restructure the Tasks BST
9. View BST Info (height, size, leaves, internal nodes)
10. Exit

## Course Info
- Course: COMP2421 — Data Structures
- University: Birzeit University
- Semester: Spring 2024/2025
