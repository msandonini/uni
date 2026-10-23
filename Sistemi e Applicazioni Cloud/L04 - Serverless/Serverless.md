---
date:
  - 2026/10/23
---
In un'architettura serverless si lavora in modalità no-ops, dove la gestione delle operations diventa un compito del cloud provider

Proprietà di un'architettura serverless:
- Scaling automatico (se ne occupa il cloud provider)
- Monitoring e analisi gestiti dal cloud provider
- Servizio spento quando non utilizzato
- Modello di costo fine-grained (costo in base ai consumi)

Queste proprietà portano diversi benefici:
- Minimizzazione della latenza
	- Solitamente richieste gestite da diversi nodi sul territorio
- Minimizzazione della complessità del software
	- Il software non deve più tenere conto di considerazioni sull'hardware del server
- Aumento della produttività

FaaS e serverless computing sono tipicamente basati sui container, e solitamente supportano diversi linguaggi, tra cui i più usati sono Go, Rust, e Python.

Ci sono 2 tipi di servizi serverless:
- FaaS (Function as a Service)
	- Elastico
		- Stateless
		- Asincrono
		- Event-driven
	- Poco costoso
	- Gestione semplice
- BaaS (Backend as a Service)
	- Servizio fornito ad altre applicazioni come API per i dev
	- Esempi tipici di BaaS sono server di autenticazioni e storage
	- Persistente (cloud storage e db management)
	- Serve gestione della sicurezza

