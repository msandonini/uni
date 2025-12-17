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

classifier("I've been waiting for a HuggingFace course my whole life.")
```
```
$ [{'label': 'POSITIVE', 'score': 0.9598047137260437}]
```

```python
from transformers import pipeline

classifier = pipeline("zero-shot-classification")
classifier(
    "This is a course about the Transformers library",
    candidate_labels=["education", "politics", "business"],
)
```
```
{'sequence': 'This is a course about the Transformers library',
 'labels': ['education', 'business', 'politics'], 'scores': [0.844, 0.112, 0.0434]}
```

Una pipeline, come si può vedere nella figura seguente, prende in input una frase, la converte in token da passare al modello, e per finire ne esegue il post-processing per ottenere le probabilità:
![[hugging_face_pipeline.png]]


