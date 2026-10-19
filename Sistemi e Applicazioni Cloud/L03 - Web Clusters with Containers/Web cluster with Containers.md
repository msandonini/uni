---
date:
  - 2026/10/16
  - 2026/10/19
---
Quando si fa server scaling ci sono diverse possibilità:
- Scale-up del server
	- Aumento delle risorse del server
- Scale-out delle risorse
	- Replicazione delle risorse

- Scale-up a livello OS
	- Ridurre il numero di operazioni
	- Cambiare algoritmo di scheduling
- Ottimizzazione del Web Server
	- Programmazione multi-threading o event-driven
- Soluzioni a livello kernel
	- Uso di web server kernel-level
	- Riduzione di context switches
	- Nessuna transizione di spazio tra utente e kernel

slides 5 - 8

Solitamente un web switch opera ad application level, il che rende più semplice l'implementazione in user space, maggiore flessibilità (supporta sessioni, cookies, ...), e supporta meccanismi di riconoscimento IP e reindirizzamento ad altro server.

## Apache `httpd`

```sh
docker run -it --rm --name <name> -p 8080:80 httpd:2.4
```
- `-it`: modalità interattiva (mostra i log)
- `--rm`: rimuove il container quando viene stoppato
- `--name <name>`: imposta il nome del container
- `-p <exposed>:<port>`: publish (espone la porta del container su quella specificata del pc)

```sh
docker container inspect -f {{.NetworkSettings.Networks.bridge.IPAddress}} <name/ID>
```
Mostra l'IP del container

Per poter spostare file in un container o modificare un'immagine posso usare un Dockerfile:
```dockerfile
FROM httpd:2.4

COPY index.html /usr/local/apache2/htdocs
```

Una volta creato il dockerfile posso creare un'immagine con i miei file e configurazioni:
```sh
docker image build -t <name> .
```

```sh
docker container exec -it <name> bash
```
Apre bash su un container in esecuzione

## Lab

```Dockerfile
FROM httpd:2.4
ARG workername='RLworker'
EXPOSE 80
RUN mkdir /usr/local/apache2/htdocs/cluster
COPY index.html /usr/local/apache2/htdocs/cluster
RUN sed -i s/NAME/$workername/ /usr/local/apache2/htdocs/cluster/index.html
```

Equivalente a prima ma con compose, basta creare un file chiamato `docker-compose.yaml`:
```yaml
services:
	httpworker1:
		build:
			context: httpworker
			args:
				workername: worker1
		image: httpworker:worker1
		container_name: httpworker1
	httpworker2:
		build:
			context: httpworker
			args:
				workername: worker2
		image: httpworker:worker2
		container_name: httpworker2
```

```sh
docker compose -f config.yaml
```

---

Gateway container:
```dockerfile
FROM httpd:2.4
EXPOSE 80
COPY mod_proxy.conf /usr/local/apache2/conf/extra
RUN echo "Include conf/extra/mod_proxy.conf" >> /usr/local/apache2/conf/httpd.conf
```

Equivalente in compose:
```yaml
services:
	[...]
	switch:
		build:
			context: switch
		image: httpswitch
		depends_on:
			- httpworker1
			- httpworker2
		ports:
			- "80:80"
```

## `nginx`

A differenza che con [[#Apache `httpd`|httpd]], con nginx non bisogna caricare moduli come mod proxy e mod proxy balancer, in quanto sono già pre-compilati.

Il balancer si crea upstram, e per utilizzarlo si mettono delle regole per specificare i worker disponibili, e necessita di un proxy pass.
Con nginx non si ha visualizzazione integrata delle richieste e dei worker (si può vedere ma con trucchi strani).

Nginx lavora con HTTP e basta (non supporta AJP), e dal momento che lavora con HTTP si aspetta una risposta HTTP, di conseguenza c'è una componente software che fa da intermediario tra nginx e il server che risponde.


