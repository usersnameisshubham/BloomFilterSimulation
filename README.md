# Bloom Filter vs std::map in C++

## Overview

This project demonstrates the implementation and performance comparison of a **Bloom Filter** and C++ `std::map`.

A Bloom Filter is a **probabilistic data structure** used for fast membership testing with very low memory usage. Unlike traditional data structures, it may return **false positives**, but it never returns false negatives.

The project benchmarks both data structures in terms of:

- Insertion speed
- Lookup performance
- Memory consumption
- Hit and miss query performance

---

## Features

- Custom Bloom Filter implementation
- Multiple hash functions
- Random string key generation
- Memory usage tracking
- Performance benchmarking
- Interactive command-line interface
- Comparison with ordered `std::map`

---

## Technologies Used

- C++
- STL (`map`, `vector`, `chrono`)
- Bloom Filter
- Hashing
- Performance Benchmarking

---

## How Bloom Filter Works

A Bloom Filter uses:

- A large bit array
- Multiple hash functions

When inserting a key:
1. The key is hashed multiple times
2. Corresponding bit positions are set to `1`

When searching:
1. The same hashes are computed
2. If any bit is `0` → key definitely does not exist
3. If all bits are `1` → key may exist

This makes Bloom Filters:
- Extremely memory efficient
- Very fast for lookups

But they can produce:
- False positives
- No false negatives

---

## Project Structure

```bash
.
├── bloom.cpp
├── README.md
└── results.csv
```

---

## Compilation

### Linux / macOS

```bash
g++ bloom.cpp -O2 -o bloom
./bloom
```

---

## Menu Options

```text
1. Insert keys into std::map
2. Lookup hits (map)
3. Lookup misses (map)
4. Insert keys into Bloom Filter
5. Lookup hits (Bloom)
6. Lookup misses (Bloom)
7. Show total memory usage
8. Exit
```

---

## Performance Metrics Measured

The program compares:

- Insert time
- Lookup hit time
- Lookup miss time
- Total memory usage

---

## Why Bloom Filters Are Useful

Bloom Filters are widely used in:

- Databases
- Web browsers
- Distributed systems
- Network routers
- Cache systems
- Spell checkers

They are ideal when:
- Memory efficiency is important
- Fast lookups are required
- Occasional false positives are acceptable

---

## Example Workflow

1. Generate random keys
2. Store them in `std::map`
3. Store the same keys in Bloom Filter
4. Benchmark both structures
5. Compare memory and speed

---

## Advantages of Bloom Filter

- Very low memory usage
- Extremely fast lookup
- Scales well for huge datasets

---

## Limitations

- False positives are possible
- Cannot retrieve stored values
- Cannot remove elements easily (basic Bloom Filter)

---

## Future Improvements

- Counting Bloom Filter
- Dynamic Bloom Filter
- Better hash functions
- Visualization graphs
- CSV benchmark export
- False positive rate analysis

---
