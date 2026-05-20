---
course: Graph Analytics
---
Gli LLM sono basati sull'architettura dei [[Transformers]], un'evoluzione dei modelli encoder-decoder basata sugli [[RNN]].
Questo tipo di architettura fa uso di meccanismi di dot-product attention e self-attention, così da permettere:
- Parallelizzazione
- Cattura di dipendenze a lungo termine
- Scalabilità

Esistono 3 principali famiglie di LLM:
- Encoder-only
	- Sono LLM che fanno uso solamente dell'encoder, e non utilizzano il decoder
	- Tra questi modelli si possono trovare [[Sentence-BERT (SBERT)|BERT]] o [[ELECTRA]]
	- Processano l'intera sequenza di input simultaneamente, permettendo una comprensione del testo molto estesa
	- Sono utilizzati per capire il linguaggio naturale
	- Hanno diversi vantaggi
- Decoder-only
	- Sono LLM che fanno uso solamente del decoder e non utilizzano l'encoder
	- Eseguono una previsione della parola successiva basandosi sulla distribuzione di probabilità delle parole del proprio dizionario (generazione auto-regressiva)
	- Tra questi modelli si possono trovare la famiglia di modelli [[GPT]], [[Llama]], [[Claude]], ecc...
- Retrieval augmented generation ([[Best Practices for RAG Applications|RAG]])

Un RAG è composto da diverse componenti:
- Dati esterni (nel senso di dati nuovi al di fuori del dataset di training originale)
- Embedding model
	- Componente che crea una rappresentazione vettoriale contestuale dei documenti (i documenti semanticamente simili sono proiettati a punti vicini nello spazio vettoriale)
- Vector database
	- Un database che si occupa di immagazzinare gli embedding di parole, frasi, e documenti, assieme ai loro classificatori
- Retriever
	- Componente che ottiene i documenti più rilevanti rispetto alla query di input convertendola in un embedding e computandone la similarità
- Generator
![[Pasted image 20260520104331.png]]

## Graph Retrieval-Augmented Generation

Un Graph-RAG è una versione avanzata di RAG che incorpora i dati in una struttura a grafo.
Gli knowledge graphs sono rappresentazioni strutturate delle informazioni che evidenziano le relazioni tra varie entità.

Il processo seguito da un Graph RAG è come segue:
1. Query processing
2. Graph traversal
3. Subgraph retrieval
4. Information integration
5. Response generation

