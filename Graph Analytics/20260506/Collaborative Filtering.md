In uno scenario content based la creazione dei vettori per gli items si basa su un numero limitato di possibili dimensioni. In questo caso la considerazione più grande da fare è quella riguardante sparsità e densità.
Per tali considerazioni, possiamo rappresentare il vettore con una struttura ad hoc:
![[Pasted image 20260506103351.png]]

Una domanda che ci possiamo fare è quale sia la soglia sulla base della quale considerare un vettore sparso o denso.
In realtà non c'è una vera soglia, bensì varia da caso a caso.

```cypher
MATCH (u:User {userId: "121688"})-[:PURCHASES]->(i:Item)
RETURN elementId(i) as index, count(i) as value
ORDER BY index
```

