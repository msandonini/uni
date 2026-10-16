---
aliases:
  - docker
---
## Gestione container

```sh
docker container ps
```
Visualizza i container attivi

```sh
docker container ps -a
```
Visualizza tutti i container

```sh
docker container rm <name/ID>
```
Rimuove un container. Si può scrivere anche solo una parte dell'id invece che tutto

```sh
docker container inspect <name/ID>
```
Mostra le informazioni di configurazione del container

```sh
docker container inspect -f {{<filter>}}
```
Mostra le informazioni del container filtrandole. Il filtro segue la sintassi di Go

```sh
docker container exec -it <name> <command>
```
Esegue un comando sul container

## Gestione immagini

```sh
docker image build -t <name> <context>
```
Crea un immagine con nome `<name>` partendo dalla posizione `<context>`

```sh
docker image rm <name>
```
Elimina un'immagine 

## Gestione sistema

```sh
docker system prune
```
Rimuove tutto ciò che non è utilizzato

```sh
docker system prune -v
```
Elimina tutti i volumi non correntemente utilizzati (anche se legato ad un container ancora esistente)

## Docker compose

```sh
docker compose -f <file> <command>
```
Specifica il file di configurazione di compose
- `-f <file>` specifica il nome del file di configurazione

```sh
docker compose up
```
Crea il container

```sh
docker compose down
```
Elimina il container (se si stoppa con `CTRL+C` il container viene stoppato ma non eliminato e al prossimo `docker compose up` viene ricaricato dall'ultimo stato, non applicando eventuali modifiche)

```sh
docker compose down -v
```
Elimina il container e i volumi

```sh
docker compose exec -it <service> <command>
```
Come eseguire `docker container exec` ma su un servizio specifico


