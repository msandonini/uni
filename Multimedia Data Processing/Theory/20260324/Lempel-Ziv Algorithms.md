---
tags:
  - multimedia_data_processing
  - compression
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
