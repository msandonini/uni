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

## Query

- Tutte le iterazioni del Dottore
```cypher
MATCH (d:Character)
WHERE d.name CONTAINS "Doctor" AND exists(d.iteration)
RETURN d.name, d.iteration
```

- Tutti i companion dell'undicesimo Dottore
```cypher
MATCH (c:Character)-[:COMPANION_OF]->(d:Character {name: "Tenth Doctor"})
RETURN c.name
```

- Tutti i nemici del Dottore:
```cypher
MATCH (enemy)-[:ENEMY_OF]->(d:Character)
WHERE d.name CONTAINS "Doctor"
RETURN DISTINCT enemy.name
```

- Tutti gli episodi in cui appare il decimo Dottore
```cypher
MATCH (c:Character {name: "Tenth Doctor"})-[:APPEARS_IN]->(e:Episode)
RETURN e.title, e.release
ORDER BY e.release
```

- Nemici comuni tra diverse incarnazioni del Dottore:
```cypher
MATCH (e)-[:ENEMY_OF]->(d1:Character {name: "Tenth Doctor"}),
      (e)-[:ENEMY_OF]->(d2:Character {name: "Eleventh Doctor"})
RETURN DISTINCT e.name
```

- Catena causale degli eventi:
```cypher
MATCH path = (e1:Event)-[:CAUSES*]->(e2:Event)
RETURN path
```