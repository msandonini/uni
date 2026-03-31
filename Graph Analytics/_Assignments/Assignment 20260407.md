---
course: Graph Analytics
---
## Descrizione del dominio

Il grafo si occupa di modellare l'universo narrativo della serie della BBC "Doctor Who".
Per fare ciò, l'obiettivo del grafo è rappresentare le relazioni tra i personaggi (Dottori, compagni di viaggio, e nemici), le epoche, ed i pianeti visitati, identificando chi ha viaggiato con chi, quali minacce sono più frequenti su determinati pianeti, e in quali epoche si concentrano i vari viaggi

## Modello logico

Nodi:
- Character: rappresenta ogni entità senziente, presenta i parametri:
	- name (`string`)
	- species (`string`)
- Planet: rappresenta i luoghi visitati nel tempo e nello spazio
	- name (`string`)
	- sector (`string`)
- Episode: rappresenta un episodio della serie
	- title (`string`)
	- era: può assumere un valore "classic", "modern", o "new"
	- release (`date`)
Determinate istanze del tipo Character possono presentare il parametro "iteration", per rappresentare l'iterazione corrente dei personaggi che si sono rigenerati.
A seconda dell'era dell'episodio, le istanze di Episode possono presentare uno dei parametri tra "season", "series", e "serial", di tipo `integer`, così da rendere più semplice l'identificazione dell'episodio

Archi:
- COMPANION_OF: connette un compagno di viaggio al Dottore specifico
- ENEMY_OF: connette un cattivo ad un personaggio
	- threat (`integer`): indica la pericolosità della specifica rivalità
- COMES_FROM: connette un personaggio al suo pianeta di provenienza
- VISITED: connette un personaggio ad un pianeta
	- year (`integer`): indica quando il personaggio ha visitato il pianeta
- APPEARS_IN: connette personaggi e pianeti ad un episodio, rappresentando in quale episodio sono rappresentati
- REGENERATED_INTO: connette un personaggio che può rigenerarsi alla sua iterazione successiva della sua rigenerazione

## Cypher

```cypher
// -- NODI --

// Character
MERGE (FirstDoctor:Character {name: "First Doctor", species: "The Doctor's Species", iteration: 1})
MERGE (SecondDoctor:Character {name: "Second Doctor", species: "Time Lord", iteration: 2})
MERGE (ThirdDoctor:Character {name: "Third Doctor"}, species: "Time Lord", iteration: 3)
MERGE (FourthDoctor:Character {name: "Fourth Doctor", species: "Time Lord", iteration: 4})
MERGE (FifthDoctor:Character {name: "Fifth Doctor", species: "Time Lord", iteration: 5})
MERGE (SixthDoctor:Character {name: "Sixth Doctor", species: "Time Lord", iteration: 6})
MERGE (SeventhDoctor:Character {name: "Seventh Doctor", species: "Time Lord", iteration: 7})
MERGE (EighthDoctor:Character {name: "Eighth Doctor", species: "Time Lord", iteration: 8})
MERGE (NinthDoctor:Character {name: "Ninth Doctor", species: "Time Lord", iteration: 10})
MERGE (TenthDoctor:Character {name: "Tenth Doctor", species: "Time Lord", iteration: 11})
MERGE (MetacrysisDoctor:Character {name: "Metacrysis Doctor", species: "Human"})
MERGE (EleventhDoctor:Character {name: "Eleventh Doctor", species: "Time Lord", iteration: 13})
MERGE (WarDoctor:Character {name: "War Doctor", species: "Time Lord", iteration: 9})
MERGE (TwelfthDoctor:Character {name: "Twelfth Doctor", species: "Time Lord", iteration: 14})
MERGE (ThirteenthDoctor:Character {name: "Thirteenth Doctor", species: "Time Lord", iteration: 15})
MERGE (FourteenthDoctor:Character {name: "Fourteenth Doctor", species: "Time Lord", iteration: 16})
MERGE (FifteenthDoctor:Character {name: "Fifteenth Doctor", species: "Time Lord", iteration: 17})

MERGE (Susan:Character {name: "Susan Foreman", species: "Gallifreyan"})
MERGE (SarahJane:Character {name: "Sarah Jane Smith", species: "Human"})
MERGE (RoseTyler:Character {name: "Rose Tyler", species: "Human"})
MERGE (AmyPond:Character {name: "Amy Pond", species: "Human"})
MERGE (ClaraOswald:Character {name: "Clara Oswald", species: "Human"})

MERGE (MelodyPond:Character {name: "Melody Pond", species: "Proto-Time Lord", iteration: 1})
MERGE (MelsZucker:Character {name: "Melody Zucker", species: "Proto-Time Lord", iteration: 2})
MERGE (RiverSong:Character {name: "River Song", species: "Proto-Time Lord", iteration: 3})

MERGE (DalekCaan:Character {name: "Dalek Caan", species: "Dalek"})
MERGE (Rusty:Character {name: "Rusty", species: "Dalek"})
MERGE (Davros:Character {name: "Davros", species: "Kaled"})

MERGE (TwelfthMaster:Character {name: "The Master", species: "Time Lord", iteration: 12})
MERGE (SaxonMaster:Character {name: "The Master", species: "Time Lord", iteration: 1})
MERGE (Missy:Character {name: "Missy", species: "Time Lord", iteration: 2})

// Races

MERGE (Daleks:Species {name: "Daleks"})
MERGE (TimeLords:Species {name: "Time Lords"})
MERGE (Humans:Species {name: "Humans"})

// Actor
MERGE (WilliamHartnell:Actor {name: "WilliamHartnell"})
MERGE (DavidTennant:Actor {name: "David Tennant"})
MERGE (MattSmith:Actor {name: "Matt Smith"})
MERGE (PeterCapaldi:Actor {name: "Peter Capaldi"})

MERGE (CaroleAnnFord:Actor {name: "Carole Ann Ford"})
MERGE (BilliePiper:Actor {name: "Billie Piper"})

MERGE (JohnSimm:Actor {name: "John Simm"})
MERGE (MichelleGomez:Actor {name: "Michelle Gomez"})

// Planet
MERGE (Gallifrey:Planet {name: "Gallifrey", sector: "Acturus"})
MERGE (Earth:Planet {name: "Earth", sector: "0-0-1"})
MERGE (Skaro:Planet {name: "Skaro", sector: "7-T-Z"})

// Episode
MERGE (UnearthlyChild:Episode {title: "An Unearthly Child", era: "classic", release: date('1963-11-23'), serial: 1})
MERGE (GenesisOfTheDaleks:Episode {title: "Genesis of the Daleks", era: "classic", release: date('1975-03-08'), serial: 78})
MERGE (Doomsday:Episode {title: "Doomsday", era: "modern", release: date('2006-07-08'), series: 2})
MERGE (TheEndOfTime:Episode {title: "The End of Time", era: "modern", release: date('2009-12-25'), series: 4})

// -- Relazioni --

// REGENERATED_INTO
MERGE (FirstDoctor)-[:REGENERATED_INTO]->(SecondDoctor)
MERGE (SecondDoctor)-[:REGENERATED_INTO]->(ThirdDoctor)
MERGE (ThirdDoctor)-[:REGENERATED_INTO]->(FourthDoctor)
MERGE (FourthDoctor)-[:REGENERATED_INTO]->(FifthDoctor)
MERGE (FifthDoctor)-[:REGENERATED_INTO]->(SixthDoctor)
MERGE (SixthDoctor)-[:REGENERATED_INTO]->(SeventhDoctor)
MERGE (SeventhDoctor)-[:REGENERATED_INTO]->(EighthDoctor)
MERGE (EighthDoctor)-[:REGENERATED_INTO]->(WarDoctor)
MERGE (WarDoctor)-[:REGENERATED_INTO]->(NinthDoctor)
MERGE (NinthDoctor)-[:REGENERATED_INTO]->(TenthDoctor)
MERGE (TenthDoctor)-[:REGENERATED_INTO]->(TenthDoctor)
MERGE (TenthDoctor)-[:REGENERATED_INTO]->(MetacrysisDoctor)
MERGE (TenthDoctor)-[:REGENERATED_INTO]->(EleventhDoctor)
MERGE (EleventhDoctor)-[:REGENERATED_INTO]->(TwelfthDoctor)
MERGE (TwelfthDoctor)-[:REGENERATED_INTO]->(ThirteenthDoctor)
MERGE (ThirteenthDoctor)-[:REGENERATED_INTO]->(FourteenthDoctor)
MERGE (FourteenthDoctor)-[:REGENERATED_INTO]->(FourteenthDoctor)
MERGE (FourteenthDoctor)-[:REGENERATED_INTO]->(FifteenthDoctor)

MERGE (SaxonMaster)-[:REGENERATED_INTO]->(Missy)

MERGE (MelodyPond)-[:REGENERATED_INTO]->(MelsZucker)
MERGE (MelsZucker)-[:REGENERATED_INTO]->(RiverSong)

// COMPANION_OF
MERGE (RoseTyler)-[:COMPANION_OF]->(NinthDoctor)
MERGE (RoseTyler)-[:COMPANION_OF]->(TenthDoctor)
MERGE (SarahJane)-[:COMPANION_OF]->(FourthDoctor)
MERGE (Susan)-[:COMPANION_OF]->(FirstDoctor)

// ENEMY_OF
MERGE (Daleks)-[:ENEMY_OF {threat: 8}]->(FirstDoctor)
MERGE (Daleks)-[:ENEMY_OF {threat: 9}]->(TenthDoctor)
MERGE (Daleks)-[:ENEMY_OF {threat: 10}]->(WarDoctor)
MERGE (SaxonMaster)-[:ENEMY_OF {threat: 8}]->(TenthDoctor)
MERGE (Davros)-[:ENEMY_OF {threat: 9}]->(FourthDoctor)
MERGE (Daleks)-[:ENEMY_OF {threat: 10}]->(TimeLords)
MERGE (Daleks)-[:ENEMY_OF {threat: 7}]->(Humans)
MERGE (SaxonMaster)-[:ENEMY_OF {threat: 8}]->(Humans)

// COMES_FROM
MERGE (Susan)-[:COMES_FROM]->(Gallifrey)
MERGE (SaxonMaster)-[:COMES_FROM]->(Gallifrey)
MERGE (FirstDoctor)-[:COMES_FROM]->(Gallifrey)
MERGE (Davros)-[:COMES_FROM]->(Skaro)
MERGE (Daleks)-[:COMES_FROM]->(Skaro)

// VISITED
MERGE (TenthDoctor)-[:VISITED {year: 2006}]->(Earth)
MERGE (FirstDoctor)-[:VISITED {year: 1963}]->(Earth)
MERGE (FourthDoctor)-[:VISITED {year: 1975}]->(Skaro)

// APPEARS_IN
MERGE (FirstDoctor)-[:APPEARS_IN]->(UnearthlyChild)
MERGE (Earth)-[:APPEARS_IN]->(UnearthlyChild)
MERGE (FourthDoctor)-[:APPEARS_IN]->(GenesisOfTheDaleks)
MERGE (Skaro)-[:APPEARS_IN]->(GenesisOfTheDaleks)
MERGE (Davros)-[:APPEARS_IN]->(GenesisOfTheDaleks)
MERGE (TenthDoctor)-[:APPEARS_IN]->(Doomsday)
MERGE (RoseTyler)-[:APPEARS_IN]->(Doomsday)
MERGE (TenthDoctor)-[:APPEARS_IN]->(TheEndOfTime)
```