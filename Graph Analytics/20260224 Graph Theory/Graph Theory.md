---
course: Graph Analytics
---


A graph is a collection of points, called **vertices** and lines connecting those points, called **edges**


> [!NOTE] Definition
> An undirected **Graph** is a collection $V$ of vertices and a collection $E$ of edges, each of which connects a pair of vertices

More formally, a graph is a pair $G = (V, E)$ where $V$ is a collection of vertices $V = \{V_{i}, i = 1, n\}$ and $E$ is a collection of edges over $V$ ($E_{i, j} = \{(V_{i}, V_{j}), V_{i} \in V, V_{j} \in V\}$).
$E \subseteq [V]^{2}$, thus the elements of $E$ are two-element subsets of $V$

The simplest way to represent a graph is to draw a dot or a small circle for each vertex and then join two of those vertices by a line if they form an edge.

A vertex with an associated value/name is called a **labelled** vertex, while a vertex with no associated value is called **unlabelled**.
The number $|V|$ of vertices contained in a graph is called the **order** of the graph.

An edge can connect any two vertices in a graph. The 2 vertices connected by an edge are called **endpoints** of that edge. By definition, if an edge exists, than it has 2 endpoints.
We call an edge going towards a vertex an **incoming** edge, while an edge originating from a vertex is called an **outgoing** edge.

Edges can also be undirected, i.e. they connect two vertices regardless of which one is the vertex of origin for that edge.
Edges of this type can be traversed in both directions.

The number of edges $|E|$ in a graph is a special parameter of that graph, called the size of the graph.

Graphs can be **directed** or **undirected**, depending on whether a direction of traversal is defined on the edges.

A **simple** graph permits only a single relationship between a pair of nodes in each direction. 
There are many use cases when permit multiple relationships between a pair of nodes are needed. In that case, it is called a **multigraph**.

If each vertex in a graph is connected with each other vertex, the graph is called **complete**.