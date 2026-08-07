# My DataStructures

A collection of common data structures implemented from scratch in modern C++ (C++20).
This project is built for learning: it shows **how** these structures work internally
instead of just using the STL versions.

## What's inside

| Data Structure | Description |
| --- | --- |
| `Array` | Fixed-size array wrapper with bounds-checked access |
| `DynamicArray` | Growable array with automatic resizing |
| `LinkedList` | Doubly linked list with iterators |
| `Stack` | LIFO stack (linked-list based) |
| `StackArr` | LIFO stack (dynamic-array based) |
| `Queue` | FIFO queue (linked-list based) |
| `QueueArr` | FIFO queue (dynamic-array based) |
| `BinarySearchTree` | BST with insert, remove, search and DFS/BFS traversals |
| `Graph` | Abstract graph interface (directed / undirected) |
| `AdjacencyMatrixGraph` | Graph using an adjacency matrix, with a BFS iterator |
| `AdjacencyListGraph` | Graph using adjacency lists, with a BFS iterator |

## Project structure

```
My_DataStructures/
├── src/
│   ├── main.cpp              # Example usage / tests
│   └── DS/                   # All data structures (header-only, template-based)
│       ├── Array.h
│       ├── DynamicArray.h
│       ├── LinkedList.h
│       ├── Stack.h
│       ├── StackArr.h
│       ├── Queue.h
│       ├── QueueArr.h
│       ├── IStack.h          # Stack interface
│       ├── IQueue.h          # Queue interface
│       ├── BinarySearchTree.h
│       └── Graph/
│           ├── Graph.h
│           ├── AdjacencyMatrixGraph.h
│           └── AdjacencyListGraph.h
├── My_DataStructures.slnx    # Visual Studio solution
└── My_DataStructures.vcxproj # Visual Studio project
```

All data structures are **header-only templates**, so you can simply
`#include` them in your own code.

Every ADT also comes with its own **iterator** (STL-style `begin()` / `end()`
and `++` / `*` support), so you can loop over the structures naturally — just
like you would with the STL.

## Requirements

- Windows
- Visual Studio 2022 (or later) with the **v145** toolset
- C++20 or later

## How to build & run

1. Open `My_DataStructures.slnx` in Visual Studio.
2. Set the configuration to **Debug** (or Release).
3. Press **Ctrl + F5** to build and run.

The program currently demonstrates an example using `AdjacencyListGraph`:
adding vertices and edges, getting neighbors, and traversing with the BFS iterator.

## Example usage

```cpp
#include "DS/Graph/AdjacencyListGraph.h"
#include <string>

int main()
{
    AdjacencyListGraph<std::string> graph(
        Graph<std::string>::GraphDirectionType::eUnDirected
    );

    graph.AddVertex("A");
    graph.AddVertex("B");
    graph.AddVertex("C");

    graph.AddEdge("A", "B");
    graph.AddEdge("A", "C");

    // BFS traversal starting from "A"
    for (auto it = graph.beginBFS("A"); it != graph.endBFS(); ++it)
    {
        // visit *it
    }
}
```

## Why this project exists

This is a practice project for understanding how classic data structures are
designed and implemented in C++. Each class is written to feel like the STL
(iterators, `size()`, `empty()`, `clear()`, etc.), but the internals are
hand-written so you can read and learn from them.

> **Important note:** This project was made for **learning purposes only**.
> It has **not been thoroughly tested**, so it may contain **logical bugs** and
> some **performance issues**. Use it as a reference to study how data
> structures work — not as a production-ready library.

## Roadmap (ideas)

- Add `Set`, `HashTable`, and `Heap`
- Add Dijkstra / DFS graph traversals
- Add unit tests for every structure
