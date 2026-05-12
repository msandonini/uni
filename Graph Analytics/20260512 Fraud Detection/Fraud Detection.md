---
course: Graph Analytics
---
Molte tecniche di fraud detection si appoggiano a tecniche di anomaly ed outlier detection.
Anomalie ed outlier in ambito di fraud detection sono molto importanti, in quanto comportamenti non convenzionali sono solitamente un buon indicatore di una possibile frode avvenuta.

La frode viene definita come un evento non comune, ben pianificato e organizzato nel tempo, che si evolve nel tempo, e nascosto impercettibilmente che può apparire in diversi tipi e forme.
Secondo alcuni report, a livello globale, circa il 5% di tutti i ricavi annui sono affetti da frode, con un impatto pari a 3 trilioni di dollari all'anno.

| Fraud detection methods | Utilises correlations (higher is better) | Detects unknown fraud (higher is better) | Requires feature engineering (lower is better) | Depends on labels (lower is better) |
| ----------------------- | ---------------------------------------- | ---------------------------------------- | ---------------------------------------------- | ----------------------------------- |
| Rule Engine             | Low                                      | N/A                                      | N/A                                            | Low                                 |
| Decision tree           | Low                                      | Low                                      | High                                           | High                                |
| Graph model             | High                                     | High                                     | Low                                            | Low                                 |

Fraud detection e fraud prevention sono 2 termini vicini ma con differenti significati:
- Fraud prevention
	- Si riferisce a mosse che possono essere intraprese per prevenire e ridurre casi di frode, quali:
		- Uso di fibre fluorescenti, lamine metalliche, e stampe olografiche al di sopra delle banconote
		- Numeri di identificazione personali per le carte di credito
		- Sistemi di sicurezza online per le transazioni bancarie
		- Utilizzo di password su sistemi informatici e applicazioni bancarie
	- Ogni metodo ha delle controindicazioni, siano esse in termini di vulnerabilità, effettività, costi, o inconvenienza per l'utente finale, di conseguenza è necessario trovare un trade-off tra i pro e i contro
- Fraud detection
	- Si riferisce alla capacità di riconoscere o scoprire un caso di frode
	- Torna utile quando i sistemi di prevenzione della frode falliscono, ma proprio perché non è sempre ovvio quando ciò accade, è necessario utilizzare queste misure costantemente, risultando in un sistema non solo costoso da costruire ma anche da mantenere

%% Es. slide 33 %%
```cypher
MATCH p = (fraud:Fraudolent)<-[:HAS_NEXT*]-(tx:Transaction)
WHERE fraud.date > datetime() - duration("P7D") 
	AND NONE (
		tx IN nodes(p)
		WHERE COALESCE(tx.date, datetime()) <= datetime() - duration("P14D")
	)
RETURN p
```