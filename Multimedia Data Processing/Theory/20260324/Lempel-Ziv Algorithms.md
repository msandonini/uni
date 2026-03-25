---
course: Multimedia Data Processing
---
- LZ77
	- Sliding window algorithm
	- First one
	- Variation: 
		- LZSS (Lempel-Ziv-Storer-Szymanski)
	- Applications: 
		- `gzip`
		- Squeeze
		- LHA
		- PKZIP
		- ZOO
- LZ78
	- Dictionary base technique
	- Slower to compress but faster to implement
	- Variations: 
		- LZW (Lempel-Ziv-Welch): technique used in GIF files
		- LZC (Lempel-Ziv-Compress)
	- Applications:
		- `compress`
		- GIF
		- CCITT
		- ARC
		- PAC

## LZ77

LZ77 works by using 3 different pieces of information:
- Dictionary (previously encoded data)
- Cursor (current position)
- Lookahead buffer (data we still need to process)

The window containing the dictionary and the buffer are of fixed length and scroll with the cursor.

At each step, we send out a triplet composed of:
- P 
	- Position of the longest match in the dictionary, relative to the current position
- L
	- Length of the longest match
- C
	- Next character to be buffered after the correspondence
After that we move the window L+1 steps forward

This algorithm is powerful because it's able to copy over the same sequence of characters multiple times.

Dictionary: `abcd`
Symbol to decode: `(2, 9, e)`

- We move back of P, so in the dictionary we move back of 2 and get the sequence `cd`
- We add a character from the sequence until we hit the L length, so 9 times, obtaining the sequence `abcdcdcdcdc`
- We append the character C to the sequence, obtaining the final sequence `abcdcdcdcdce`

<!-- Immagine a slide 39 del pacchetto 01_Data_Compression -->
![[Pasted image 20260324142950.png]]

### LZSS

A tiny variation to LZ77, which separates insertion from copy, obtaining 2 different codes:
- (0, `position`, `length`)
- (1, `character`)

### Optimizations employed by gzip

- Position, length and characters are coded with Huffman
- Some special rules are introduced to prevent the use of the longest string right now if we can do better in the next step
- Hash tables are used to store the dictionary:
	- Hash based on strings of length 3
	- The best match is found within the correct bucket.
	- Limits are imposed on the length of the search.
	- The data is stored in the bucket in position order

### Theory behind LZ77

In 1994, Wyner and Ziv published a paper proving that the LZ algorithm applied to sufficiently long strings results in them being compressed up to the limit of the entropy of the message when the search window tends to infinity:
$$
\begin{align}
H_{n} &= \sum_{X \in A^{n}} p(X) \log \frac{1}{p(X)} \\
H &= \lim_{ n \to \infty } H_{n}
\end{align}
$$

## LZ78

A dictionary of words is kept with an integer identifier for each entry (from an implementation POV this aspect becomes fundamental, as a structure like a trie can modify performance dramatically)

- Find the longest string `S` in the dictionary matching the string starting at current position
- Send the identifier of `S` and the next (after the correspondence) character `c`
- add the string `Sc` to the dictionary

<!-- Slide 44, stesso pacchetto delle slide di prima -->
![[Pasted image 20260324145131.png]]

## LZW

LZW is a variation of LZ78 which avoids the extra character `c` while still adding `Sc` to the dictionary.
The dictionary is initialized with byte values from 0 to 255 (all possible single bytes that can be encountered). This initialization is fixed and therefore does not require any data transmission.
The decoder rebuilds the code and the dictionary based only on the codes received.

<!-- Slide 47 -->
![[Pasted image 20260324152030.png]]

There is a special case that must be handled separately:
<!-- Slide 49 -->
![[Pasted image 20260324152504.png]]

When the code that we should have created in the current step is found, it means that this is equal to the last decoded code plus its first symbol.

> [!WARNING] Problem with LZ78 e LZW
> With LZ78 and LZW there can be an issue where the dictionary gets too big.
> To solve this there are various ideas:
> - Delete the dictionary when it reaches a certain size and then start again as if the file started here (technique used by GIF: simple)
> - Delete the dictionary when the compression is not particularly effective and then start again (used in the Unix `compress` utility)
> - Delete the least recently used entry (Least-Recently-Used or LRU) when the dictionary reaches a certain size (used in BTLZ, the standard of British Telecom)

> [!INFO] Current state of LZ algorithms
> Both LZ77 and LZ78 are becoming obsolete but the ideas used are the basis of all the latest algorithms

