---
tags:
  - big_data
  - llm
---
Dall'avvento dei LLM, la parte di [[Information Retrieval]] (IR) è rimasta particolarmente colpita.

Nelle applicazioni di retrieval, una query $q$ è usata per cercare tra diversi documenti candidati $d_{i, \dots, n}$, tornando i documenti che corrispondono meglio all'informazione richiesta.

Un retriever può dividersi in 2 categorie:
- Sparse retrievers (ad esempio TF-IDF)
	- Metodi molto veloci visto che non sono basati su reti neurali
	- Facili da implementare, e possono performare bene in diverse occasioni
	- Soffrono da problemi di out-of-vocabulary
	- Richiedono un word-match esatto, in quanto i sinonimi vengono trattati come parole totalmente diversi
- Dense retrievers
	- Performano meglio rispetto agli sparse retrievers
	- Non soffrono di problemi di out-of-vocabulary
	- Sono più computazionalmente onerosi

