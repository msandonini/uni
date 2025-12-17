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
```json
>>> [
		{
			'label': 'POSITIVE', 
			'score': 0.9598047137260437
		}
	]
```

```python
from transformers import pipeline

classifier = pipeline("zero-shot-classification")
classifier(
    "This is a course about the Transformers library",
    candidate_labels=["education", "politics", "business"],
)
```
```json
>>> {
		'sequence': 'This is a course about the Transformers library',
		'labels': ['education', 'business', 'politics'], 
		'scores': [0.844, 0.112, 0.0434]
	}
```

Una pipeline, come si può vedere nella figura seguente, prende in input una frase, la converte in token da passare al modello, e per finire ne esegue il post-processing per ottenere le probabilità:
![[hugging_face_pipeline.png]]

### Tokenizer

Per utilizzare un tokenizer nella libreria `transformers` il metodo più veloce è utilizzare `transformers.AutoTokenizer`, classe che automaticamente sceglie quale modello di tokenizer utilizzare per lo specifico input (in alternativa si possono usare metodi specifici, come ad esempio `transformers.BertTokenizerFast`)

```python
from transformers import AutoTokenizer
checkpoint = "distilbert-base-uncased-finetuned-sst-2-english"
tokenizer = AutoTokenizer.from_pretrained(checkpoint)
raw_inputs = [ "I've been waiting for a HuggingFace course my whole life.", "I hate this so much!", ]
inputs = tokenizer(raw_inputs, padding=True, truncation=True, return_tensors="pt")
```
```json
>>> {
		'input_ids': tensor(
			[
				[  101,  1045,  1005,  2310,  2042,  3403,  2005,  1037, 17662, 12172, 2607,  2026,  2878,  2166,  1012,   102], 
				[  101,  1045,  5223,  2023,  2061,  2172,   999,   102,     0,     0,     0,     0,     0,     0,     0,     0]
			]
		), 
	    'attention_mask': tensor(
		    [
			    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 
			    [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0]
			]
		)
	}
```


Utilizzando [[Transformers#BERT|BERT]] come tokenizer, viene utilizzato il metodo dei CLS Token, utilizzando i caratteri `101` (`CLS`) e `102` (`SEP`).

### Model

```python
from transformers import AutoModel

checkpoint = "distilbert-base-uncased-finetuned-sst-2-english"
model = AutoModel.from_pretrained(checkpoint)
```

Questa architettura contiene solamente il modulo di base del transformer, che dato l'input restituirà in output il suo hidden state (ovvero le features).

```python
outputs = model(**inputs)

print(outputs.last_hidden_state.shape)
```
```python
>>> torch.Size([2, 16, 768])
```

Per quanto questi hidden states possano essere utili per conto loro, solitamente vengono usati come input per un'altra parte del modello, conosciuta come `head`, e che viene scritta come `<model-name><head-name>`:
- `<model>ForCasualLM`
- `<model>ForMaskedLM`
- `<model>ForMultipleChoice`
- `<model>ForQuestionAnswering`
- `<model>ForSequenceClassification`
- `<model>ForTokenClassification`
![[hugging_face_head.png]]

Di conseguenza, per riuscire a classificare il sentimento di una frase come positivo o  negativo abbiamo bisogno di una classification head:
```python
from transformers import AutoModelForSequenceClassification
checkpoint = "distilbert-base-uncased-finetuned-sst-2-english"
model = AutoModelForSequenceClassification.from_pretrained(checkpoint)
outputs = model(**inputs)
print(outputs.logits)
```
```python
>>> tensor([[-1.5607,  1.6123], [ 4.1692, -3.3464]])
```
Come possiamo vedere, qua ci vengono restituiti i logits del modello, ovvero degli score grezzi da convertire in probabilità. Per convertire questi logits in rappresentazione probabilistica possiamo usare una softmax


