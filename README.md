# AVL-Tree-Wordlist

This is an extension of my Data Structures assignment, using an AVL Tree (instead of a linked list, which was used as per the assingment instructions) to store words from a text file in a "Wordlist." It offers insightful data such as the frequency of each word in the file, the most frequent word, singletons, and the total number of unique words. 

## Using the wordlist

To run the program with your own .txt file:

1. Replace `"tiny_shakespeare.txt"` with your text file's filename in the line:

   ```cpp
   Wordlist lst("tiny_shakespeare.txt");
