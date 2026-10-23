
```shell
kybectl get <resources>
```
Visualizza risorse

```shell
kubectl get <resources> -o wide
```
Visualizza risorse con più informazioni

```shell
kubectl apply -f <deployment-conf.yaml>
```
Esegue il deployment del file di configurazione

```sh
kubectl top <resources>
```
Mostra i consumi di un tipo di risorsa

```sh
kubectl cordon <node>
```
Evita che un nodo prenda lavoro

```sh
kubectl uncordon <node>
```
Operazione inversa di `cordon`

```sh
kubectl drain <node>
```
Fa si che nessun pod possa essere eseguito sul nodo, così da preparare il nodo per la manutenzione