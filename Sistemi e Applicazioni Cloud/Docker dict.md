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
docker image build -t <name> <context>
```
Crea un immagine con nome `<name>` partendo dalla posizione `<context>`


