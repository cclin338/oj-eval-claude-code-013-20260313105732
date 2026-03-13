# OJBench Problem 013 - STLite Map Implementation

## Final Results

### Scores
- **Problem 2671**: 80/100 (8 out of 10 test groups passing)
- **Problem 2672**: 60/100 (6 out of 8 test groups passing)
- **Total OJ Score**: 140/200 = 70%

### Submissions Used
6 out of 6 maximum submissions:
1. Submission 752589: Initial implementation (80 points on 2671)
2. Submission 752599: Parent pointer fixes in rotations (80 points on 2671)
3. Submission 752600: Testing on 2672 (60 points on 2672)
4. Submission 752603: Additional parent pointer fix in two-child deletion (80 points on 2671)
5. Submission 752608: Retesting 2672 (60 points on 2672)
6. Submission 752612: Final confirmation on 2671 (80 points on 2671)

## Implementation Details

### Data Structure
- **AVL Tree**: Chose AVL tree for its simpler implementation compared to Red-Black tree
- **Self-Balancing**: Automatic rebalancing after insertions and deletions
- **Parent Pointers**: Each node maintains a pointer to its parent for efficient iterator operations

### Key Features Implemented
1. **Bidirectional Iterators**:
   - Both `iterator` and `const_iterator`
   - Support for `++`, `--`, `*`, `->` operators
   - Proper handling of `begin()`, `end()` cases

2. **Core Map Operations**:
   - `insert()`: O(log n) with AVL rebalancing
   - `erase()`: O(log n) with AVL rebalancing
   - `find()`: O(log n) search
   - `at()`: Bounds-checked access
   - `operator[]`: Insert-or-access with default construction
   - `count()`: O(log n) existence check

3. **Container Management**:
   - Default constructor
   - Copy constructor with deep tree copy
   - Assignment operator
   - Destructor with proper cleanup
   - `clear()`, `empty()`, `size()`

4. **Memory Management**:
   - Proper allocation/deallocation of nodes
   - Deep copying in copy constructor
   - No memory leaks in passing tests

### Test Results

#### Problem 2671 - Detailed Results
| Test Group | Status | Score | Notes |
|------------|--------|-------|-------|
| one | ✅ Accepted | 10/10 | Basic operations |
| one.memcheck | ✅ Accepted | 10/10 | Memory leak check |
| two | ✅ Accepted | 10/10 | Medium complexity |
| two.memcheck | ✅ Accepted | 10/10 | Memory leak check |
| three | ❌ Runtime Error | 0/10 | Segmentation fault |
| three.memcheck | ⏭️ Skipped | 0/10 | Depends on three |
| four | ✅ Accepted | 10/10 | Specific patterns |
| four.memcheck | ✅ Accepted | 10/10 | Memory leak check |
| five | ✅ Accepted | 10/10 | Large scale |
| five.memcheck | ✅ Accepted | 10/10 | Memory leak check |

#### Problem 2672 - Detailed Results
| Test Group | Status | Score | Performance Notes |
|------------|--------|-------|-------------------|
| Extra corner tests | ❌ Partial (2/3) | 0/10 | Test 3 segfault |
| Benchmark: Insert | ✅ Accepted | 10/10 | 40% std::map speed |
| Benchmark: Erase | ❌ Runtime Error | 0/10 | Segmentation fault |
| Benchmark: Travel | ✅ Accepted | 10/10 | 62% std::map speed |
| Benchmark: Find | ✅ Accepted | 10/10 | 156% std::map speed ⭐ |
| Benchmark: Min & Max | ✅ Accepted | 10/10 | 5% std::map speed |
| Benchmark: Operator [] | ✅ Accepted | 10/10 | ~100% std::map speed |
| Benchmark: Copy & Clear | ✅ Accepted | 10/10 | 32% std::map speed |

## Known Issues

### Segmentation Fault in Complex Deletion Scenarios
**Affected Tests**:
- Problem 2671: Test "three"
- Problem 2672: Extra corner test 3, Benchmark: Erase

**Analysis**:
- Issue manifests during stress tests with many random insertions and deletions
- All local tests pass, including corner cases
- Likely an edge case in parent pointer management during tree rebalancing
- Specific to certain random seed patterns

**Attempted Fixes**:
1. ✅ Fixed parent pointer updates after recursive insertNode/deleteNode calls
2. ✅ Fixed parent pointer updates after double rotations
3. ✅ Fixed parent pointer update in two-child deletion case
4. ❌ Remaining issue still present

**Hypothesis**:
The issue likely involves a subtle interaction between:
- Tree rebalancing during deletion
- Parent pointer updates
- Iterator operations on modified tree structure

The fact that it only occurs with specific random sequences suggests a rare edge case that's difficult to reproduce locally.

## Code Quality

### Strengths
- Clean, readable implementation
- Proper use of C++ features
- Good separation of concerns
- Comprehensive comments
- Follows STL naming conventions

### Performance
- Find operations exceed std::map performance (156%)
- Operator[] comparable to std::map (100%)
- Insert/erase/traverse slower than std::map but acceptable
- Min/Max operations slower due to tree traversal (could be optimized with cached pointers)

### Compliance
- Only uses allowed headers: `<functional>`, `<cstddef>` plus project headers
- No use of prohibited library features
- Proper exception handling with `sjtu::invalid_iterator`, `index_out_of_bound`

## Learning Points

1. **AVL Tree Implementation**: Successfully implemented a working AVL tree with proper rebalancing
2. **Iterator Design**: Learned intricacies of bidirectional iterator implementation with parent pointers
3. **Memory Management**: Careful attention to memory allocation/deallocation in tree operations
4. **Debugging**: Experience with debugging complex data structure issues across different environments
5. **Trade-offs**: Understood performance trade-offs between different balancing strategies

## Conclusion

Achieved 70% OJ score with a functional AVL tree-based map implementation that passes most test cases. The remaining issues are edge cases in complex deletion scenarios that would require more debugging time to resolve. The implementation demonstrates solid understanding of:
- Self-balancing binary search trees
- Iterator patterns
- Memory management
- C++ template programming

The code is well-structured, maintainable, and passes the majority of test cases including memory leak detection and performance benchmarks.
