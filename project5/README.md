# CS 360, Project 5
# Matthew Leeds
# 2015-04-09

## Assumptions ##
* Both dict.txt and board.txt are formatted correctly and contain only uppercase ASCII characters (except the first line of board.txt).

## Design, Data Structures, and Algorithms ##
  This project primarily uses three data structures, a 2D array for the board, a 2D array to keep track of whether nodes have been visited (seen),
and a prefix tree for the dictionary of words. Since we are traversing the board as a tree, a first instinct might be to use an adjacency list or
adjacency matrix, a simple 2D array is faster both in time and space complexity since we can simply increment and decrement to reach adjacent nodes,
and we don't have the overhead that lists of node pointers would have. For the dictionary I have an array for each possible starting character
(that you can index into with ASCII values). Each of these has a list of "children", which are letters that follow it in some word, and so on as
deep as necessary. Nodes also have a bit for whether they are the last letter in a word so that we can identify words that are prefixes of other words. 
This data structure enables us to quickly determine (in time logarithmic to the length of the string) whether a path we are traversing could lead to
any valid words.

  The primary algorithm used to find valid words in the board is a recursive depth-first search. We begin a separate search starting at each of the nodes
as they are all potential starting letters. At a node, the algorithm only proceeds if it isn't marked as seen and the current string is a valid prefix.
If so, we mark it as seen so it won't be repeated in this search, visit all of the nodes adjacent to it (and expand them), and mark it as unseen. This
way, the node will be considered valid for inclusion in other searches. This approach ensures that we visit every possible path on the board. 

  The object-oriented design of the project may seem questionable since the board, dictionary, and all the related methods are in one class. If this were
a larger project it might make sense to make separate classes for those but since it is relatively short I don't think readability is hurt very much. This
design is also probably marginally more efficient due to the overhead of object instantiation.
