---
date:
  - 2026/10/16
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


