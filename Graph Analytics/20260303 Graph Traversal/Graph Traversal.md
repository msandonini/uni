---
tags:
  - graph_aanalytics
---
In Graph Theory, the **shortest path** problem is the problem of finding the quickest path between 2 vertices.

If all edges cost the same, BFS can

| Algorithm      | Problem solved | Negative Weights? | Best Time Complexity | When to use | Key Use Cases |
| -------------- | -------------- | ----------------- | -------------------- | ----------- | ------------- |
| Dijkstra       | Single source  | No                |                      |             |               |
| Bellman-Ford   |                |                   |                      |             |               |
| A (A Star)*    |                |                   |                      |             |               |
| Floyd Warshall |                |                   |                      |             |               |
| Johnson        |                |                   |                      |             |               |
| Viterbi        |                |                   |                      |             |               |

A road network can be considered a graph with positive weights. 
The nodes represent road junctions and each edge of t he graph is associated with a road segment between 2 junctions.
The weight of an edge may correspond to the length of t he associated road segment, the time needed to traverse the segment or the cost of traversing the segment. 
Using directed edges it is also possible to model one-way streets.

Road networks are a special type of graph, in the sense that some edges are more important than others for long-distance travel (e.g. highways). This property has been formalized using the notation of **highway dimension**.

**Connectivity** is one of the basic concepts of graph theory, as it asks for the minimum number of elements (nodes or edges) that need to be removed to separate the remaining nodes into 2 or more isolated sub-graphs.
The **Max-Flow Min-Cut** theorem establishes that the maximum flow between a source and a target in a network equals the minimum capacity of all possible cuts separating them.

**Eccentricity** of a node in a connected graph G is the maximum graph distance between v and any other vertex u, and is given by the maximum length between all the shortest paths starting from a specific node.

A direct graph is said to be **strongly connected** if every vertex is reachable from each other vertex through a directed path.
An example of a strongly connected graph is the road network of a city, where there must be a way from a vertex to reach all other ones.

**Conductance** is a measure of connectivity, obtained by partitioning a graph $G$ in 2 sub-graphs, and summing the paths that from $G_{1}$ go in $G_{2}$.
$$
\text{Conductance }(G_{1}, G_{2}) = \phi(G_{1}, G_{2}) = \frac{\text{cut}(G_{1}, G_{2})}{\min(\text{vol}(G_{1}), \text{vol}(G_{2}))}
$$
Conductance is useful for evaluating the quality of a graph partition, since a smaller conductance means tighter clusters with fewer edges crossing the partition.

