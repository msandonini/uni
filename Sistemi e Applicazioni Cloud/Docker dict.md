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


