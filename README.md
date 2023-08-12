# Word-Suggest-Alogrithm

This project implements a spelling suggestion system using dynamic memory allocation, Abstract Data Types (ADTs), and linked data structures. The system provides users with suggestions for potentially misspelled words by utilizing an edit distance approach. The project comprises various components that work together to achieve this functionality.

Components and Concepts

1. Triple S ADT (triple-s.h)
The Triple S ADT (Set of Sorted Strings) serves as a wrapper for handling a collection of sorted strings. It leverages dynamic memory allocation to manage the storage of strings. The ADT provides essential operations for creating, adding, searching, and removing strings from the collection.

2. Sequence of Strings ADT (sos.h, sos.c)
The Sequence of Strings ADT (SOS) is a linked data structure that manages a sequence of strings. It dynamically allocates memory for each string and maintains a linked list of string nodes. The ADT offers functions for creating, destroying, inserting, and manipulating sequences of strings.

3. Counting Bloom Filter ADT (countingbloomfilter.h, countingbloomfilter.c)
The Counting Bloom Filter ADT employs dynamic memory allocation to manage a data structure that efficiently tests set membership. It uses an array of counters to represent hash values and dynamically resizes the array as needed. The ADT allows insertion, lookup, and removal of items.

4. Spelling Suggestion (suggest.h, suggest.c)
The Spelling Suggestion module implements a dynamic approach to generating spelling suggestions for potentially misspelled words. It calculates an edit distance between the input word and other words, creating a set of candidate words. The ADTs, including Triple S and Counting Bloom Filter, help filter and store valid suggestions.

5. Main Client (main.c)
The Main Client is an I/O test program that showcases the utilization of the implemented ADTs and data structures. It reads input words, processes them through the spelling suggestion system, and outputs suggestions or "OK" for correctly spelled words.
