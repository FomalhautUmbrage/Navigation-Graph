# Description
I design and implement a graph data structure to store a weighted, undirected graph. In addition, I implement Dijkstra’s algorithm to determine the lowest-weight path between two vertices. In this project, the vertices represent intersections in a city and the edge weight represents the travel time between the two intersections.<br/>
## Understanding Range-Based Search
In a range-based search, we are interested obtaining a list of points within a given range. For example, I might want to know all points whose coordinates lie within the range 𝑥 ∈ (0,1), 𝑦 ∈ (−1, −0.4). If we are guaranteed that all search regions are contained entirely within a single node’s rectangular region of space, this problem is simple. However, if the search region intersects multiple nodes’ rectangles, the problem is more difficult. Recursion or stack-based algorithms are often used for this purpose.
# Command
## LOAD
**Parameters:** *filename* <br/>
**Description:** Load a dataset into a graph. This command may not be present in all input files or may be present multiple times. You may assume there are no illegal arguments in the datasets. All rows in these files will have the same format as a single INSERT command. Assume A = 1 while inserting.
