---
tags:
  - progettazione_software
  - fp
  - esercizi
---
![[Esercizio_FP.png]]

Le linee più marcate indicano i confini dell'applicazione Gestione Professori, che si deve stimare, e dell'applicazione
Gestione Studenti.
1. Gestione dei dati sui professori
	1. Inserisci Professore: inserisci i dati di un nuovo professore (`Nome` e `Anzianità`).
	2. Interroga Professori: richiedi tutti i dati anagrafici di un professore dato il suo `Nome`.
	3. Elenca Professori: la lista di tutti i dati anagrafici dei professori.
2. Gestione dei dati sui corsi
	1. Inserisci Corso: inserisci tutti i dati di un nuovo corso. I dati comprendono il `Codice`, l'`Istituto` e il `nome` del professore che tiene il corso (occorre verificarne l’esistenza).
	2. Interroga Corsi: richiedi tutti i dati di un corso dato il suo `Codice`. I dati comprendono il `Codice`, l'`Istituto` e il `nome` del professore.
	3. Elenca Corsi: mostra la lista di tutti i corsi. I dati comprendono il `Codice`, l'`Istituto` e il `nome` del professore.
3. Gestione degli esami superati.
	1. Inserisci Esame Superato: inserisci un nuovo esame superato. I dati comprendono il `Codice_Corso`, la `Matricola` dello studente e il `Voto` (verifica esistenza del corso e dello studente)
	2. Interroga Esami Superati: richiedi i dati di un esame superato dato il suo codice. I dati comprendono il `Codice_Corso`, la `Matricola_Studente` e il `Voto`.
	3. Elenca Esami Superati: mostra la lista di tutti gli esami superati stampando alla fine il numero totale di esami (stessi dati di 3.2).
Si richiede di identificare i punti funzione relativi l’applicazione.

---

## File

- "Corso" è un nuovo file
	- 1 RET
	- 2 DET
- "Professore" è un nuovo file
	- 1 RET
	- 2 DET
- "Tenuto da" viene collassato dentro "Corso", in quanto per l'utente non ha senso avere un file separato apposito, ed essendo un'associazione (1, n) è più semplice inserirlo lì
	- A "Corso" si aggiunge 1 DET
- "Esame superato" è un nuovo file, perché il concetto di aver superato un esame è un evento separato da un "Corso", ed essendo un file di confine è preferibile gestirlo come file
	- 1 RET
	- 3 DET

Per concludere:
- Corso
	- 1 RET
	- 3 DET
		- Codice
		- Istituto
		- Professore
- Professore
	- 1 RET
	- 2 DET
		- Nome
		- Anzianità
- Esame superato
	- 1 RET
	- 3 DET
		- Codice_corso
		- Matricola_studente
		- Voto

| ILF            | RET | DET | Type  | Value |
| -------------- | --- | --- | ----- | ----- |
| Corso          | 1   | 3   | BASSA | 7     |
| Professore     | 1   | 2   | BASSA | 7     |
| Esame superato | 1   | 3   | BASSA | 7     |
|                |     |     |       |       |
| EIF            |     |     |       |       |
| Studenti       | 1   | 4   | BASSA | 5     |
|
| | EI | EO |

|     | EI - FTR | EI -DET | EI - Type | EI - Value | EO - FTR | EO - DET | EO - Type | EO - Value | EQ - EI - FTR | EQ - EI - DET | EQ - EI - Type | EQ - EO - FTR | EQ - EO - DET | EQ - EO - Type | EQ - Type (Max) | EQ - Value |
| --- | -------- | ------- | --------- | ---------- | -------- | -------- | --------- | ---------- | ------------- | ------------- | -------------- | ------------- | ------------- | -------------- | --------------- | ---------- |
| 1.1 | 1        | 2       | BASSA     | 3          | -        | -        |           |            | -             | -             |                | -             | -             |                |                 |            |
| 1.2 | 1        | 1       | BASSA     | 3          | -        | -        |           |            | -             | -             |                | -             | -             |                |                 |            |
| 1.3 | -        | -       |           |            | 1        | 2        | BASSA     | 4          | 1             | 1             | BASSA          | 1             | 2             | BASSA          | BASSA           | 3          |
|     |          |         |           |            |          |          |           |            |               |               |                |               |               |                |                 |            |
| 2.1 | 2        | 3       | BASSA     | 3          | -        | -        |           |            | 1             | 1             | BASSA          | -             | -             |                | BASSA           | 3          |
| 2.2 | 1        | 1       | BASSA     | 3          | -        | -        |           |            | -             | -             |                |               |               |                |                 |            |
| 2.3 | -        | -       |           |            | 1        | 3        | BASSA     | 4          | 1             | 1             | BASSA          | 1             | 3             | BASSA          | BASSA           | 3          |
|     |          |         |           |            |          |          |           |            |               |               |                |               |               |                |                 |            |
| 3.1 | 3        | 3       | MEDIO     | 4          |          |          |           |            | 2             | 2             | BASSA          | -             | -             |                | BASSA           | 3          |
| 3.2 | 1        | 1       | BASSA     | 3          | -        | -        |           |            | -             | -             |                |               |               |                |                 |            |
| 3.3 | -        | -       |           |            | 1        | 3        | BASSA     | 4          | 1             | 1             | BASSA          | 1             | 3             | BASSA          | BASSA           | 3          |

| Valutazione |     |
| ----------- | --- |
| ILF         | 21  |
| EIF         | 5   |
| EI          | 19  |
| EO          | 12  |
| EQ          | 15  |
| TOTALE      | 72  |
