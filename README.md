# AutoBracket

## Overview

AutoBracket is an algorithm designed to determine the correct parenthesization of a sequence of binary operations over integers, given an operator table. This project was developed for an Algorithm Analysis and Synthesis class.

## Problem Description

The operator ⊕, can be defined by a table of this kind:

<pre>
⊕ | 1 2 3
--|------
1 | 2 2 1
2 | 3 2 1
3 | 1 3 3
</pre>

Sequences of successive applications of this operator are associated with their results, such as:

<pre>
2 ⊕ 2 ⊕ 2 ⊕ 2 ⊕ 1 ⊕ 3 = 1
</pre>

However, the sequences lack parentheses to indicate the order of operations. The goal is to discover the correct order to achieve the given results. For example, one possible parenthesization for the above sequence is:

<pre>
((((2 ⊕ 2) ⊕ 2) ⊕ (2 ⊕ 1)) ⊕ 3) = 1
</pre>

The objective of this project is to develop an algorithm which will read the operator table and sequence and automate the placement of parentheses to reach the desired result.
Some sequences may have multiple valid parenthesizations, in which case the algorithm should return the left-most one.
