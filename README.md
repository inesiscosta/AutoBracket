# AutoBracket

## Overview

AutoBracket is an algorithm designed to determine the correct parenthesization of a sequence of binary operations over integers, given an operator table. This project was developed for the Analysis and Synthesis of Algorithms class.

## Problem Description

Given several tables defining binary operators over integers, one such operator, ⊕, is defined by the following table:

```
⊕ | 1 2 3
--|------
1 | 2 2 1
2 | 3 2 1
3 | 1 3 3
```

Sequences of successive applications of these operators are associated with their results, such as:

```
2 ⊕ 2 ⊕ 2 ⊕ 2 ⊕ 1 ⊕ 3 = 1
```

However, the sequences lack parentheses to indicate the order of operations. The goal is to discover the correct order to achieve the given results. For example, one possible parenthesization for the above sequence is:

```
((((2 ⊕ 2) ⊕ 2) ⊕ (2 ⊕ 1)) ⊕ 3) = 1
```

The objective of this project is to develop an algorithm to automate the placement of parentheses in the sequences.
Some sequences may have multiple valid parenthesizations, in which case the algorithm should return the left-most one.
