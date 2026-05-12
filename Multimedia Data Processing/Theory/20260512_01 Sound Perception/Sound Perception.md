---
course: Multimedia Data Processing
---
The human ear acts as a transducer in transforming acoustic energy, first into mechanical energy and then into electrical energy.

Once the energy has been converted from mechanical to electrical form by the ear, the electrical impulses come to the brain through nerve endings.

The auditory system is made up of three sections: the outer ear, the middle ear and the inner ear.
![[Pasted image 20260512141147.png]]

In the outer ear we find the auricle, where the sound is reflected and concentrated towards the ear canal, whose length is on average equal to 3 cm.
The resonant frequency of the ear canal is on average 3 kHz (the frequency around which the voices are).
The ear canal ends on a membrane where the middle ear starts.
This membrane is called eardrum (or also tympanic membrane or myringa), and it vibrates in accordance with the sound that has reached the ear.
On the opposite side of the eardrum there are three small bones called hammer, anvil, and stirrup, which have the function of amplifying the vibration of the eardrum and retransmitting it to the cochlea (a snail-shaped bone containing fluid and located inside of the inner ear).
This amplification is necessary because while the eardrum is a very light membrane suspended in the air, the cochlea is filled with a dense fluid and therefore much more difficult to put into vibration.
An opening inside the middle ear leads to the Eustachian tube, which consists of a canal that leads to the oral cavity (which allows to balance the atmospheric pressure on the 2 sides of the eardrum).
The cochlea and the stirrup are in contact through a membrane called oval window.
When the fluid inside the cochlea receives a vibration from the stirrup through the oval window, it transports it inside to the Corti organ, which is the real organ responsible for converting mechanical energy into electrical energy.
The corti organ is composed of a basic membrane which houses a population of about 4000 eyelashes, which vibrate according to the fluid vibration.
Each group of eyelashes is connected to a nerve termination capable of converting the vibration received by the fluid into electrical impulses which then get sent to the brain and processed to be perceived as sound.
The extension of the eyelashes excited by the single frequency is called the critical band, and it is the basis of many psychoacoustic phenomena.
The extension of the critical band increases with increasing frequency.

The phenomenon of critical bands is at the origin of the masking phenomenon, used in many audio data compression algorithms.
Information relating to frequencies that fall in the same critical band is replaced with a single frequency representative of all.
The sound perceived in this way will not be degraded much, while the sound information to be stored will be decreased, thus creating data compression.

The concept of critical band is also the basis of another psychoacoustic phenomenon: beats and occurs when the two frequencies that originate the beat fall into the same critical band.

The isophonic curves were obtained by processing the data on a statistical sample subjected to a series of sounds produced in an anechoic chamber (a chamber designed to minimize reflection of sounds on the walls):
![[Pasted image 20260512142805.png]]
The isophonic curves are curves on a graph designed to indicate the $\text{dB}_{\text{spl}}$ value necessary to perceive a sound always at the same volume along each curve (in short terms, these charts allow to have a reference on how the human ear reacts to different frequencies).
These curves were created since the human ear has a different perception of sound intensity as the frequency changes.
The reference frequency for each curve is 1 kHz and, at this frequency, the $\text{dB}_{\text{spl}}$ value is equal to the value that identifies a particular curve and which is called **phon**.
![[Pasted image 20260512143228.png]]
>[!WARNING] Curves standards
> Different studies' revisions change how the data is shown, so when working with them it's important to reference the correct curve standards and revision and keep an eye on how the curves were obtained in the specific study we are referencing

The lowest isophonic curve of all is called the audibility threshold, and it indicates the smallest pressure change that the ear is able to detect at different frequencies:

| Frequency zone   | Hz    | $\text{dB}_{spl}$ |
| ---------------- | ----- | ----------------- |
| Reference        | 1000  | 5                 |
| Low Frequencies  | 50    | 42                |
| High frequencies | 10000 | 15                |
The table shows some reference values relating to the curve.
The pain threshold is located at 120 phons, and it's the point where the ear begins to perceive physical pain and non-reversible damage can be generated for prolonged exposures.

The hearing, like the view that interprets the light, is capable of perceiving only a part of the acoustic waves that surround us and therefore returns a partial picture.
The perceived waves are processed by the brain which thus interprets the sounds it has to process.
Psychoacoustics is the science that studies the brain's sound processing mechanisms.

A frequency component with *high amplitude* can mask components at nearby frequencies with lower amplitudes, since nearby frequencies are decoded by cilia belonging to the same critical band.
A sound of a certain frequency and intensity (masker) can temporarily change the frequency response of the ear bringing other sounds (masked) below the audibility threshold:
![[Pasted image 20260512144321.png]]
The bandwidth of the masking threshold depends on the intensity and frequency of the masker and the intensity of the masking effect decreases moving away from the frequency of the masker sound.
![[Pasted image 20260512145154.png]]
This property is massively exploited to create algorithms for compressing audio data in digital format such as MP3 or AAC, allowing compressions in the order of 5: 1

Another type of sound masking is the temporal masking, which occurs when a weak sound follows (in about 50 ms) or, incredibly, precedes (of about 10 ms), a more intense sound.
![[Pasted image 20260512145224.png]]

