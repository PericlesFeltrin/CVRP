#CVRP - Capacitated Vehicle Routing Problem
#### PRVC - Problema de Roteamento de Veículos Capacitados
Problema de Roteamento de Veículos Capacitados com custos simétricos. 

Para gerar uma solução Sequencial para o problema use:
```
$ gcc CVRP.c -o main
$ ./main
```

Para gerar uma solução com OpenAcc para o problema use:
```
$ pgcc -acc -Minfo=accel -fast CVRP.c
$ ./a.out
```

Repositório com as instancias:
http://vrp.atd-lab.inf.puc-rio.br/index.php/en/

Obs.: Somente para arquivos no padrão EUC_2D

```
Copyright (C) 2015 - Péricles Pinheiro Feltrin
```
