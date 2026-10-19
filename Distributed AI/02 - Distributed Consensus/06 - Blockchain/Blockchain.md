---
date:
  - 2026/10/19
---
Not asked in exam

The blockchain is a general concept describing a model for dealing with distributed asset tracking and identity management, which can be implemented in different ways and with disparate goals (e.g. Bitcoin for cryptocurrency, medical records for health, or the EU ID system which is currently being thought in the EU for identity management).

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

In each block we can expect to see a set of different pieces of information:
- Index
- Timestamp
- Hash
- Previous hash
- Data
- Nonce
If any change is to be made we cannot modify the block, we instead need to make a new block with the changes.

In the blockchain, a hash must follow some rules:
- Typical hashing rules:
	- Same data always maps to same hash
	- Different data almost always maps to a different hash
	- Easy to compute hash from data
	- Infeasible to compute data from hash
- Additional constraints (e.g. $N$ leading 0s, since increasing $N$ raises hashing difficulty)

We define "mining" as the operation of finding a nonce (number), which produces a desired hash, in order to commit the block.
As difficulty increases the number $M$ of valid hashes decreases, and with a lower $M$ it takes more processing power and time to find a valid hash.
Those who find the nonce are called miners, and since they are the ones who write blockchain history, they can also harm the system, either by mistake or maliciously (by lying)


