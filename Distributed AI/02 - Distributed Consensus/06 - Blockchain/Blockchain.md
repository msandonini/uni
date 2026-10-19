---
date:
  - 2026/10/19
---
Not asked in exam

The blockchain is a general concept describing a model for dealing with distributed asset tracking and identity management, which can be implemented in different ways and with disparate goals (e.g. Bitcoin for cryptocurrency, or the EU ID system which is currently being thought in the EU for identity management).

Basically, with the term blockchain we identify a combination of distinct already existing technologies:
- Hash functions
- Digital signatures
- Replication technologies
- Consensus-based algorithms
- P2P distributed digital ledger (shared, transparent, append-only registry of transactions)

From a working point of view, the blockchain is a technology very similar to git and its transaction system, where we cannot delete commits but we can only append modifications to it (and eventually revert or amend to a previous state, but never deleting a previous commit).

We define as transaction any form of change of state in the blockchain.
Once a transaction occurs, a block is created, validated by peers, and if valid it becomes permanent and immutable.
In order to declare a block as valid, we must check a few things:
- **hash** must certify transaction integrity
- **signature** must match the issuer identity
- domain-specific validity rules must be respected (for example, in the case of a money transaction, if I send money to someone I must have the money I want to send)


