---
tags:
  - big_data
  - transformers
---
## Hugging Face Transformers Library

Task NLP:
- Classificazione del sentimento della frase
- Classificazione delle singole parole in una frase
- Generazione testo
- Estrazione di una risposta dal testo
- Generazione di una nuova frase da un testo di input
	- Traduzione
	- Riassunto

La libreria espone una pipeline con diversi metodi già implementati:
- `feature-extraction` (estrazione di vettori dalle frasi)
- `fill-mask`
- `ner` (named entity recognition)
- `question-answering`
- `sentiment-analysis`
- `summarization`
- ...

```python
from transformers import pipeline

classifier = pipeline("sentiment-analysis")
```
