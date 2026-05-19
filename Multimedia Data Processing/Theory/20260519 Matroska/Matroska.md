---
course: Multimedia Data Processing
---
Container formats are formats born to combine multiple data types (audio, video, subtitles, and other metadata) in a single object.
The most famous container formats are:
- Audio Video Interlaced (AVI), with `.avi` extension
- Matroska, with `.mkv` extension
- MPEG4 part 14, with `.mp4` and `m4a` extensions (`.m4a` is usually associated with audio only streams)

## Matroska
### Extensible Binary Meta Language (EBML)

EBML is the format used by Matroska to store data within the binary file.
It is a byte-aligned binary markup format (called octet, in the meaning of an 8-bit group).
Similarly to XML or JSON, syntax and semantics are completely separate, so EBML can be used to represent arbitrary data within a file.
In order to be EBML-compliant, the only standard part of the format is the header.

EBML allows to organize its elements hierarchically, where some of them (called *masters*) may contain other EBML elements.
EBML supports different data types of varying sizes:
- Signed integer
	- Big endian
	- Can be of any size from 1 to 8 octets
- Unsigned integer
	- Big endian
	- Can be of any size from 1 to 8 octets
- Float
	- Big endian
	- Can be of 4 or 8 octets (32 or 64 bits)
- String
	- Printable ASCII characters (from `0x20` to `0x7E`)
- UTF-8
	- Sequence of Unicode characters in UTF-8 format
- Date
	- Signed 8 octets integer in nanoseconds
	- 0 indicates the beginning of the millennium (for some reason it's `2001-01-01T00:00:00,00000000 UTC`)
- Master element
	- Contains other EBML sub-elements of the next lower level
- Binary
	- Not interpreted by the parser
Both String and UTF-8 can have some bytes set to 0 in the end (zero-padding)

The structure of each EBML element is composed of the fields `<ID> <size> <data>`.
Each element has an identifier, a size, and some data:
- `ID`
	- Is an identifier of the EBML element type (not data type)
- `Size`
	- Indicates the size of the data contained in the data field
- `Data`
	- Contains the actual data
Both the `ID` and the `size` fields are integers and are stored with a variable number of bytes (*variable size integer*, or *`VINT`*).

The `ID` length in bytes can be determined by checking the contents of the first byte:

| Width | Size     | Representation                            |
| ----- | -------- | ----------------------------------------- |
| 1     | $2^{7}$  | `1xxx.xxxx`                               |
| 2     | $2^{14}$ | `01xx.xxxx xxxx.xxxx`                     |
| 3     | $2^{21}$ | `001x.xxxx xxxx.xxxx xxxx.xxxx`           |
| 4     | $2^{28}$ | `0001.xxxx xxxx.xxxx xxxx.xxxx xxxx.xxxx` |

Since it's mandatory for `ID`s to represent values with as few bytes as possible, fewer values are available for each class:

| Class | Base   | Width | Number of IDs                   |
| ----- | ------ | ----- | ------------------------------- |
| A     | `0x8x` | 1     | $2^{7} - 2 = 126$               |
| B     | `0x4x` | 2     | $2^{14} - 2^{7}= 16,256$        |
| C     | `0x2x` | 3     | $2^{21} - 2^{14} = 2,080,768$   |
| D     | `0x1x` | 4     | $2^{28} - 2^{21} = 2,6633,8304$ |
For each class of IDs the combinations with all the bits indicated with `x` at `1` or `0` is reserved.

A size can be represented using from 1 to 8 bytes, although a maximum number of bytes less than 8 can be indicated in the header. This size is determined using the same technique used for `ID`:
![[Pasted image 20260519143913.png]]
In all cases the representable values range from 0 to $2^{\text{nbit}} - 2$, because the combination with all the bits indicated by `x` to `1` is used to indicate an unknown size.

#### Header

At the beginning of each file that respects the EBML format there is a header containing some information on how the file is formatted and what type of document it contains (the header also respects the format).
The main fields are the following:
![[Pasted image 20260519144529.png]]

#### Format

The Matroska format is an open container format that allows to store in the same file an arbitrary number of tracks, of video, audio, or text type (for subtitles).
The format only indicates which elements a file is made of, not how to divide a stream into the available elements.
It is completely based on the EBML format and a file at its level 0 (highest level) is composed of 2 elements:
- The standard `EBML header` (with DocType containing the string "matroska")
- An element called `Segment` which contains all other elements and data
![[Pasted image 20260519144729.png]]

The `Segment` contains all the level 1 EBML elements indicated in the Matroska format:
- `SeekHead`
	- Contains an index of where all the other level 1 elements are located in the file (since they can be in any order)
	- Not mandatory,as it's possible to find other level 1 elements by just scrolling the file (even if more expensive)
	- Has a very simple structure, as it maintains key-value pairs called *Seeks* which contain IDs and location as `<SeekID><SeekPosition>`:
		- `SeekID` is the EBML ID of a level 1 element
		- `SeekPosition` is the position in bytes with respect to the first level 1 element
	![[Pasted image 20260519145958.png]]
- `SegmentInfo`
	- Contains generic information on the entire file
	- It's mandatory, and some relevant elements in it are:
		- `SegmentUID`: a randomly generated unique ID to identify the file (128 bit)
		- `SegmentFilename`: a filename corresponding to the segment
		- `TimecodeScale`: a mandatory element containing a scale factor expressed in nanoseconds used to represent all the time codes contained within the file
		- `Duration`: the duration expressed using the `TimecodeScale` parameter
	![[Pasted image 20260519150416.png]]
- `Tracks`
	- Contains information on all tracks present in the file
	- Each track contains a `TrackEntry` element which mainly contains other elements:
		- `TrackNumber`: track number used later in clusters
		- `TrackUID`: a unique identifier for the track
		- `TrackType`: an 8-bit integer for the track type
			- `1`: video
			- `2`: audio
			- `3`: complex (audio and video combined)
			- `0x10`: logo
			- `0x11`: subtitle
			- `0x12`: buttons
			- `0x20`: control
		- `Language`: the language of the track
		- `CodecID`: the identifier of the codec used to encode the track
		- `CodecPrivate`: specific additional information of the codec
		- `Video`: if the track is video, contains all the video settings
		- `Audio`: if the track is audio, contains all the audio settings
	![[Pasted image 20260519150919.png]]
- `Clusters`
	- Contains clusters, each of which contains some blocks of different tracks
	- Generally contains data for a total of a few MB or a few seconds of playback. The choice of how much data to include is left to the application that creates the file
	- Can also contain some other important elements:
		- `Timecode`: a mandatory element containing an absolute timestamp of the cluster (always based on the `TimeCodeScale` present in the `SegmentInfo`)
		- `PrevSize`: contains the size in bytes of the previous cluster, it's not mandatory but useful for playback or backward search
	- The blocks can be of `SimpleBlock` or `BlockGroup` type, which perform the same function but `BlockGroup` blocks can add more information to the data block
		- `BlockGroup` is a master element and can also contain other elements, among which the important ones are the following:
			- `Block`: the binary element containing the data
				- The data is preceded by a header, and it must be interpreted in a way specified by the format (this time not EBML)
				- Each header contains different elements:
					- `Track Number`: the track number to which the data belongs, it is an integer stored as a `VINT`
					- `Timecode`: a 16-bit signed integer relating to the timecode of the cluster to which the block belongs
					- `Flags`: 1 byte of flags:
						![[Pasted image 20260519153420.png]]
					- `Number of frames`, only if lacing is used, it is an 8-bit unsigned integer indicating how many frames are stored within the block
					- `Dimensions`, only if lacing is used, contains the size of each frame. The way of representing this value varies based on the type of lacing
			- `BlockDuration`: the duration expressed in relation to the `TimecodeScale`
			- `ReferenceBlock`: contains the timestamp of another frame to be used as a reference (to indicate relationships between frames of type `B` and `P` and a frame of type `I`)
		- `SimpleBlock` is a binary element that directly contains data
			- Its structure is almost the same as the `Block` one, with the only difference being the `Flags`:
				![[Pasted image 20260519153817.png]]
	![[Pasted image 20260519152940.png]]
	![[Pasted image 20260519153032.png]]
	- Lacing is a mechanism used to save space
		- It is used when some small sized frames must be saved to the file in succession and we don't want to use new `SimpleBlock` or `BlockGroup` elements for each
		- The Matroska format supports 3 different types of lacing:
			- [[Xiph]]
			- [[EBML]]
			- [[Fixed-size]]
		- The mechanism is the same in all 3 cases, what changes is the way of representing the number and size of the frames in the corresponding field of the `Block` or `SimpleBlock`
- `Cues`
	- Contains information called `CuePoints` which represent information on where we can jump while playing the file without having to scroll through all the `Cluster` elements
	- The most important elements contained in the `CuePoints` are:
		- `CueTime`: an absolute timestamp that uses the scale indicated in `SegmentInfo` to indicate the time position of the `CuePoint`
		- `CueTrackPosition`: a master element containing all the information on how to reach the timestamp indicated in `CueTime` within a specific track:
			- `CueTrack`: indicates the track number to which it refers
			- `CueClusterPosition`: indicates the position in bytes within the `Segment` of the cluster which contains the indicated `Block`
			- `CueRelativePosition`: indicates the relative position of the `Block` within the cluster
	![[Pasted image 20260519154816.png]]
- `Chapters`
	- Contains information on the chapters in which the file is divided
	- Differs from the `CuePoint` because each `Chapter` can be associated with strings in different languages to allow the user to understand exactly where a certain `Chapter` will lead into the file
- `Attachment`
	- Can contain any type of file
- `Tagging`
	- Contains all kinds of information about the tracks, like the `ID3` tags of [[MP3]] files

