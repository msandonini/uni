// -- NODI --
// Character
MERGE
  (FirstDoctor:Character
    {name: "First Doctor", species: "The Doctor's Species", iteration: 1})
MERGE
  (SecondDoctor:Character
    {name: "Second Doctor", species: "Time Lord", iteration: 2})
MERGE
  (ThirdDoctor:Character
    {name: "Third Doctor", species: "Time Lord", iteration: 3})
MERGE
  (FourthDoctor:Character
    {name: "Fourth Doctor", species: "Time Lord", iteration: 4})
MERGE
  (FifthDoctor:Character
    {name: "Fifth Doctor", species: "Time Lord", iteration: 5})
MERGE
  (SixthDoctor:Character
    {name: "Sixth Doctor", species: "Time Lord", iteration: 6})
MERGE
  (SeventhDoctor:Character
    {name: "Seventh Doctor", species: "Time Lord", iteration: 7})
MERGE
  (EighthDoctor:Character
    {name: "Eighth Doctor", species: "Time Lord", iteration: 8})
MERGE
  (NinthDoctor:Character
    {name: "Ninth Doctor", species: "Time Lord", iteration: 10})
MERGE
  (TenthDoctor:Character
    {name: "Tenth Doctor", species: "Time Lord", iteration: 11})
MERGE (MetacrysisDoctor:Character {name: "Metacrysis Doctor", species: "Human"})
MERGE
  (EleventhDoctor:Character
    {name: "Eleventh Doctor", species: "Time Lord", iteration: 13})
MERGE
  (WarDoctor:Character {name: "War Doctor", species: "Time Lord", iteration: 9})
MERGE
  (TwelfthDoctor:Character
    {name: "Twelfth Doctor", species: "Time Lord", iteration: 14})
MERGE
  (ThirteenthDoctor:Character
    {name: "Thirteenth Doctor", species: "Time Lord", iteration: 15})
MERGE
  (FourteenthDoctor:Character
    {name: "Fourteenth Doctor", species: "Time Lord", iteration: 16})
MERGE
  (FifteenthDoctor:Character
    {name: "Fifteenth Doctor", species: "Time Lord", iteration: 17})

MERGE (Susan:Character {name: "Susan Foreman", species: "Gallifreyan"})
MERGE (SarahJane:Character {name: "Sarah Jane Smith", species: "Human"})
MERGE (RoseTyler:Character {name: "Rose Tyler", species: "Human"})
MERGE (MarthaJones:Character {name: "Martha Jones", species: "Human"})
MERGE (DonnaNoble:Character {name: "Donna Noble", species: "Human"})
MERGE (AmyPond:Character {name: "Amelia Pond", species: "Human"})
MERGE (RoryWilliams:Character {name: "Rory Williams", species: "Human"})
MERGE (ClaraOswald:Character {name: "Clara Oswald", species: "Human"})
MERGE (BillPotts:Character {name: "Bill Potts", species: "Human"})
MERGE (YasminKhan:Character {name: "Yasmin Khan", species: "Human"})

MERGE
  (MelodyPond:Character
    {name: "Melody Pond", species: "Proto-Time Lord", iteration: 1})
MERGE
  (MelsZucker:Character
    {name: "Melody Zucker", species: "Proto-Time Lord", iteration: 2})
MERGE
  (RiverSong:Character
    {name: "River Song", species: "Proto-Time Lord", iteration: 3})

MERGE (DalekCaan:Character {name: "Dalek Caan", species: "Dalek"})
MERGE (Rusty:Character {name: "Rusty", species: "Dalek"})
MERGE (Davros:Character {name: "Davros", species: "Kaled"})

MERGE
  (TwelfthMaster:Character
    {name: "The Master", species: "Time Lord", iteration: 12})
MERGE
  (SaxonMaster:Character
    {name: "The Master", species: "Time Lord", iteration: 1})
MERGE (Missy:Character {name: "Missy", species: "Time Lord", iteration: 2})
MERGE (Rassilon:Character {name: "Rassilon", species: "Time Lord"})
MERGE (Omega:Character {name: "Omega", species: "Time Lord"})

// Species
MERGE (Daleks:Species {name: "Daleks"})
MERGE (TimeLords:Species {name: "Time Lords"})
MERGE (Humans:Species {name: "Humans"})
MERGE (Cybermen:Species {name: "Cybermen"})
MERGE (WeepingAngels:Species {name: "Weeping Angels"})
MERGE (TheSilence:Species {name: "The Silence"})
MERGE (Sutekh:Character {name: "Sutekh", species: "Osiran"})
MERGE (Autons:Species {name: "Autons"})
MERGE (IceWarriors:Species {name: "Ice Warriors"})

// Organizations
MERGE (UNIT:Organization {name: "UNIT"})
MERGE (Torchwood:Organization {name: "Torchwood"})

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
MERGE (Trenzalore:Planet {name: "Trenzalore", sector: "Unknown"})
MERGE (Mondas:Planet {name: "Mondas", sector: "Twin Earth System"})
MERGE (Karn:Planet {name: "Karn", sector: "Acturus"})
MERGE (NewEarth:Planet {name: "New Earth", sector: "New Earth System"})
MERGE (Skonnos:Planet {name: "Skonnos", sector: "Unknown"})
MERGE
  (MondasianEarth:Planet {name: "Mondas (Twin Earth)", sector: "Solar System"})
MERGE (AndrozaniMinor:Planet {name: "Androzani Minor", sector: "Unknown"})
MERGE (Mars:Planet {name: "Mars", sector: "Solar System"})
MERGE (Telos:Planet {name: "Telos", sector: "Unknown"})
MERGE (GallifreyCapital:Planet {name: "Gallifrey (Capitol)", sector: "Acturus"})

// Event
MERGE (TimeWar:Event {name: "Last Great Time War", type: "Time War"})
MERGE (Flux:Event {name: "The Flux", type: "Universal Event"})
MERGE
  (PandoricaEvent:Event {name: "The Pandorica Opens", type: "Temporal Crisis"})
MERGE (CrackInTime:Event {name: "Cracks in Time", type: "Time Fracture"})
MERGE (SiegeOfTrenzalore:Event {name: "Siege of Trenzalore", type: "War"})
MERGE
  (FirstRegeneration:Event {name: "First Regeneration", type: "Regeneration"})
MERGE (FourthDoctor)-[:REGENERATED_FROM]->(ThirdDoctor)

MERGE (TheTenthPlanet)-[:DEPICTS]->(FirstRegeneration)

MERGE (TimeLords)-[:INTERVENED_IN]->(TheWarGames)

// Episode
MERGE
  (UnearthlyChild:Episode
    {
      title: "An Unearthly Child",
      era: "classic",
      release: date('1963-11-23'),
      serial: 1
    })
MERGE
  (GenesisOfTheDaleks:Episode
    {
      title: "Genesis of the Daleks",
      era: "classic",
      release: date('1975-03-08'),
      serial: 78
    })
MERGE
  (Doomsday:Episode
    {title: "Doomsday", era: "modern", release: date('2006-07-08'), series: 2})
MERGE
  (Blink:Episode
    {title: "Blink", era: "modern", release: date('2007-06-09'), series: 3})
MERGE
  (TheEndOfTime:Episode
    {
      title: "The End of Time",
      era: "modern",
      release: date('2009-12-25'),
      series: 4
    })
MERGE
  (PandoricaOpens:Episode
    {
      title: "The Pandorica Opens",
      era: "modern",
      release: date('2010-06-19'),
      series: 5
    })
MERGE
  (BigBang:Episode
    {
      title: "The Big Bang",
      era: "modern",
      release: date('2010-06-26'),
      series: 5
    })
MERGE
  (TheDayOfTheDoctor:Episode
    {
      title: "The Day of the Doctor",
      era: "modern",
      release: date('2013-11-23'),
      special: true
    })
MERGE
  (DayOfTheDoctor:Episode
    {
      title: "The Day of the Doctor",
      era: "modern",
      release: date('2013-11-23'),
      special: true
    })
MERGE
  (TimeOfTheDoctor:Episode
    {
      title: "The Time of the Doctor",
      era: "modern",
      release: date('2013-12-25'),
      special: true
    })
MERGE
  (HeavenSent:Episode
    {
      title: "Heaven Sent",
      era: "modern",
      release: date('2015-11-28'),
      series: 9
    })
MERGE
  (HellBent:Episode
    {title: "Hell Bent", era: "modern", release: date('2015-12-05'), series: 9})
MERGE
  (FluxEpisode:Episode
    {title: "Flux", era: "modern", release: date('2021-10-31'), series: 13})
MERGE
  (TheDaleks:Episode
    {
      title: "The Daleks",
      era: "classic",
      release: date('1963-12-21'),
      serial: 2
    })

MERGE
  (TheTenthPlanet:Episode
    {
      title: "The Tenth Planet",
      era: "classic",
      release: date('1966-10-08'),
      serial: 29
    })

MERGE
  (TheWarGames:Episode
    {
      title: "The War Games",
      era: "classic",
      release: date('1969-04-19'),
      serial: 50
    })

MERGE
  (SpearheadFromSpace:Episode
    {
      title: "Spearhead from Space",
      era: "classic",
      release: date('1970-01-03'),
      serial: 51
    })

MERGE
  (Robot:Episode
    {title: "Robot", era: "classic", release: date('1974-12-28'), serial: 75})

MERGE
  (PyramidsOfMars:Episode
    {
      title: "Pyramids of Mars",
      era: "classic",
      release: date('1975-10-25'),
      serial: 82
    })

MERGE
  (TheDeadlyAssassin:Episode
    {
      title: "The Deadly Assassin",
      era: "classic",
      release: date('1976-10-30'),
      serial: 89
    })

MERGE
  (Logopolis:Episode
    {
      title: "Logopolis",
      era: "classic",
      release: date('1981-02-28'),
      serial: 115
    })

MERGE
  (Earthshock:Episode
    {
      title: "Earthshock",
      era: "classic",
      release: date('1982-03-08'),
      serial: 122
    })

MERGE
  (TheCavesOfAndrozani:Episode
    {
      title: "The Caves of Androzani",
      era: "classic",
      release: date('1984-03-08'),
      serial: 135
    })

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
MERGE (Susan)-[:COMPANION_OF]->(FirstDoctor)
MERGE (SarahJane)-[:COMPANION_OF]->(FourthDoctor)
MERGE (RoseTyler)-[:COMPANION_OF]->(NinthDoctor)
MERGE (RoseTyler)-[:COMPANION_OF]->(TenthDoctor)
MERGE (MarthaJones)-[:COMPANION_OF]->(TenthDoctor)
MERGE (DonnaNoble)-[:COMPANION_OF]->(TenthDoctor)
MERGE (AmyPond)-[:COMPANION_OF]->(EleventhDoctor)
MERGE (RoryWilliams)-[:COMPANION_OF]->(EleventhDoctor)
MERGE (ClaraOswald)-[:COMPANION_OF]->(EleventhDoctor)
MERGE (ClaraOswald)-[:COMPANION_OF]->(TwelfthDoctor)
MERGE (BillPotts)-[:COMPANION_OF]->(TwelfthDoctor)
MERGE (YasminKhan)-[:COMPANION_OF]->(ThirteenthDoctor)

// ENEMY_OF
MERGE (Daleks)-[:ENEMY_OF {threat: 8}]->(FirstDoctor)
MERGE (Daleks)-[:ENEMY_OF {threat: 9}]->(TenthDoctor)
MERGE (Daleks)-[:ENEMY_OF {threat: 10}]->(WarDoctor)
MERGE (SaxonMaster)-[:ENEMY_OF {threat: 8}]->(TenthDoctor)
MERGE (Davros)-[:ENEMY_OF {threat: 9}]->(FourthDoctor)
MERGE (Daleks)-[:ENEMY_OF {threat: 7}]->(Humans)
MERGE (SaxonMaster)-[:ENEMY_OF {threat: 8}]->(Humans)
MERGE (Cybermen)-[:ENEMY_OF {threat: 9}]->(TwelfthDoctor)
MERGE (WeepingAngels)-[:ENEMY_OF {threat: 10}]->(EleventhDoctor)
MERGE (TheSilence)-[:ENEMY_OF {threat: 9}]->(EleventhDoctor)
MERGE (TimeLords)-[:ENEMY_OF {threat: 10}]->(Daleks)
MERGE (Cybermen)-[:ENEMY_OF {threat: 9}]->(Humans)
MERGE (WeepingAngels)-[:ENEMY_OF {threat: 6}]->(TenthDoctor)

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
MERGE (Earth)-[:APPEARS_IN]->(UnearthlyChild)

MERGE (FourthDoctor)-[:APPEARS_IN]->(GenesisOfTheDaleks)

MERGE (TenthDoctor)-[:APPEARS_IN]->(Blink)
MERGE (WeepingAngels)-[:APPEARS_IN]->(Blink)

MERGE (TenthDoctor)-[:APPEARS_IN]->(Doomsday)
MERGE (RoseTyler)-[:APPEARS_IN]->(Doomsday)

MERGE (TenthDoctor)-[:APPEARS_IN]->(TheEndOfTime)

MERGE (Skaro)-[:APPEARS_IN]->(GenesisOfTheDaleks)
MERGE (Davros)-[:APPEARS_IN]->(GenesisOfTheDaleks)

MERGE (WarDoctor)-[:APPEARS_IN]->(TheDayOfTheDoctor)
MERGE (EleventhDoctor)-[:APPEARS_IN]->(TheDayOfTheDoctor)
MERGE (TenthDoctor)-[:APPEARS_IN]->(TheDayOfTheDoctor)

MERGE (NewEarth)-[:APPEARS_IN]->(NewEarth)
MERGE (Trenzalore)-[:APPEARS_IN]->(TimeOfTheDoctor)
MERGE (Gallifrey)-[:APPEARS_IN]->(HellBent)

MERGE (FirstDoctor)-[:APPEARS_IN]->(TheDaleks)

MERGE (FirstDoctor)-[:APPEARS_IN]->(TheTenthPlanet)

MERGE (SecondDoctor)-[:APPEARS_IN]->(TheWarGames)

MERGE (ThirdDoctor)-[:APPEARS_IN]->(SpearheadFromSpace)

MERGE (FourthDoctor)-[:APPEARS_IN]->(Robot)
MERGE (FourthDoctor)-[:APPEARS_IN]->(PyramidsOfMars)
MERGE (FourthDoctor)-[:APPEARS_IN]->(TheDeadlyAssassin)

MERGE (FourthDoctor)-[:APPEARS_IN]->(Logopolis)
MERGE (FifthDoctor)-[:APPEARS_IN]->(TheCavesOfAndrozani)

MERGE (FifthDoctor)-[:APPEARS_IN]->(Earthshock)

MERGE (Susan)-[:APPEARS_IN]->(TheDaleks)

MERGE (SarahJane)-[:APPEARS_IN]->(PyramidsOfMars)

MERGE (SarahJane)-[:APPEARS_IN]->(Robot)

MERGE (Skaro)-[:APPEARS_IN]->(TheDaleks)

MERGE (MondasianEarth)-[:APPEARS_IN]->(TheTenthPlanet)

MERGE (Earth)-[:APPEARS_IN]->(SpearheadFromSpace)

MERGE (Mars)-[:APPEARS_IN]->(PyramidsOfMars)

MERGE (AndrozaniMinor)-[:APPEARS_IN]->(TheCavesOfAndrozani)
MERGE (Daleks)-[:APPEARS_IN]->(TheDaleks)

MERGE (Cybermen)-[:APPEARS_IN]->(TheTenthPlanet)
MERGE (Cybermen)-[:APPEARS_IN]->(Earthshock)

MERGE (Autons)-[:APPEARS_IN]->(SpearheadFromSpace)

MERGE (Sutekh)-[:ENEMY_OF {threat: 10}]->(FourthDoctor)
MERGE (Sutekh)-[:APPEARS_IN]->(PyramidsOfMars)

// INTERPRETED
MERGE (WilliamHartnell)-[:INTERPRETED {from: 1963, to: 1966}]->(FirstDoctor)

MERGE (DavidTennant)-[:INTERPRETED {from: 2005, to: 2010}]->(TenthDoctor)
MERGE
  (DavidTennant)-
    [:INTERPRETED {from: 2023, to: 2023, note: "Fourteenth incarnation"}]->
  (FourteenthDoctor)

MERGE (MattSmith)-[:INTERPRETED {from: 2010, to: 2013}]->(EleventhDoctor)

MERGE (PeterCapaldi)-[:INTERPRETED {from: 2013, to: 2017}]->(TwelfthDoctor)
MERGE (CaroleAnnFord)-[:INTERPRETED]->(Susan)

MERGE (BilliePiper)-[:INTERPRETED {from: 2005, to: 2006}]->(RoseTyler)
MERGE (JohnSimm)-[:INTERPRETED]->(SaxonMaster)
MERGE (MichelleGomez)-[:INTERPRETED]->(Missy)

// -- Other Relations --

// Time War
MERGE (WarDoctor)-[:PARTICIPATED_IN]->(TimeWar)
MERGE (TenthDoctor)-[:ENDED]->(TimeWar)
MERGE (Daleks)-[:PARTICIPATED_IN]->(TimeWar)
MERGE (TimeLords)-[:PARTICIPATED_IN]->(TimeWar)

// Flux
MERGE (ThirteenthDoctor)-[:INVOLVED_IN]->(Flux)
MERGE (Flux)-[:AFFECTS]->(Earth)
MERGE (Flux)-[:AFFECTS]->(Gallifrey)

// Pandorica
MERGE (EleventhDoctor)-[:IMPRISONED_IN]->(PandoricaEvent)
MERGE (PandoricaEvent)-[:INVOLVES]->(Daleks)
MERGE (PandoricaEvent)-[:INVOLVES]->(Cybermen)

// Trenzalore
MERGE (EleventhDoctor)-[:DEFENDED]->(Trenzalore)
MERGE (SiegeOfTrenzalore)-[:OCCURS_ON]->(Trenzalore)

// Organizations

MERGE (MarthaJones)-[:WORKS_FOR]->(UNIT)
MERGE (UNIT)-[:PROTECTS]->(Earth)
MERGE (Torchwood)-[:OPERATES_ON]->(Earth)
MERGE (AmyPond)-[:MOTHER_OF]->(RiverSong)
MERGE (RoryWilliams)-[:FATHER_OF]->(RiverSong)
MERGE (RiverSong)-[:WIFE_OF]->(EleventhDoctor)
MERGE (Susan)-[:GRANDDAUGHTER_OF]->(FirstDoctor)

// Events to episodes

MERGE (PandoricaOpens)-[:DEPICTS]->(PandoricaEvent)
MERGE (BigBang)-[:RESOLVES]->(PandoricaEvent)

MERGE (DayOfTheDoctor)-[:DEPICTS]->(TimeWar)

MERGE (TimeOfTheDoctor)-[:DEPICTS]->(SiegeOfTrenzalore)

MERGE (FluxEpisode)-[:DEPICTS]->(Flux)

// Other
MERGE (CrackInTime)-[:THREATENS]->(Universe:Place {name: "Universe"})
MERGE (EleventhDoctor)-[:INVESTIGATES]->(CrackInTime)

MERGE (PandoricaEvent)-[:CAUSES]->(CrackInTime)