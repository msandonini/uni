---
date:
  - 2026/09/29
---
Real world social networks are **small world networks**, where small world means that, despite having a big number of nodes, the mean distance of the network is quite small (like 3/4/5)

Given a set of processes / agents interacting according to a specific network structure, how does the structure impact on the dynamic behaviour of the overall system?
In order to study this we can look at the spread of infectious diseases in a network.
Let's assume that a single individual in the network is initially infected, and that it has a probability of $0 \le p \le 1$ to infect its neighbours:
- $p = 0$: the infection does not spread
- $p = 1$: the infection spreads across the network in the fastest way
- $\forall p \ne 0, 1$: the infection spreads across the network with speed proportional to the probability (it could also happen that not all the network gets infected)
We call **percolation** the process by which something diffuses across a medium, defining as **percolation threshold ($p_c$)** the critical value of a parameter over which the process can complete. 
The "epidemics" can diffuse all over the network if the percentage $p$ of susceptible nodes is greater than $p_c$

