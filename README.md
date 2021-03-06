#CVRP - Capacitated Vehicle Routing Problem
#### PRVC - Problema de Roteamento de Veículos Capacitados
Problema de Roteamento de Veículos Capacitados com custos simétricos. 

[Paralelização de uma Heurística em Aceleradores Gráficos para Resolucao do Problema de Roteamento de Veiculos](http://periclesfeltrin.com.br/arquivos/artigo/Paralelizacao_de_uma_Heuristica_em_Aceleradores_Graficos_para_Resolucao_do_Problema_de_Roteamento_de_Veiculos_TFG_2015.pdf)

### Install OpenACC
Antes de iniciar siga os passos os seguintes passos para instalar o [OpenACC](http://www.openacc.org/) e o compilador pgcc da PGI Compilers & Tools.

1. [University Developer License.](http://www.nvidia.com/object/openacc-toolkit.html)
2. [Download PGI Accelerator C/C++ Workstation.](http://www.pgroup.com/)
3. [Como instalar.](https://www.pgroup.com/doc/pgiinstall.pdf) 

Obs.: Se utilizar o e-mail da universidade consegue-se uma licença para desenvolvedor universitário ou pode-se conseguir uma licença trial de 90 dias.

##### Para compilar na CPU use o gcc:
```sh
$ gcc CVRP.c -o sequencial -std=c99 -lm
$ ./sequencial
```
Obs.: Algoritmo será executado sequencialmente.

##### Para compilar na GPU com OpenACC use pgcc:
```sh
$ pgcc -acc -Minfo=accel CVRP.c -o paralelo
$ ./paralelo
```
Obs. 1: Algoritmo será executado em paralelo na GPU.

Obs. 2: -Minfo=accel para ver informações somente referente ao acelerador na compilação.

Obs. 3: -Minfo=all para ver todas informações da compilação.

##### Para limpar a memória cache no Linux.
```sh
$ sudo sync; sudo echo 3 > /proc/sys/vm/drop_caches
```

##### Instâncias:
Na pasta A-VRP encontra-se alguns arquivos com diferentes instâncias.
Pode-se baixar outros arquivos com diferentes tamanhos de instâncias no repositório da PUC-RIO. Após baixar adicionar na pasta A-VRP.

[Download instâncias](http://vrp.atd-lab.inf.puc-rio.br/)

Obs.: Utilizar somente os arquivos no padrão especificado pela biblioteca [TSPLIB 95](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/) e com "TYPE : CVRP", "EDGE_WEIGTH_TYPE : EUC_2D" e apenas um depósito central.

Copyright (C) 2015 - [Péricles Pinheiro Feltrin](http://periclesfeltrin.com.br/)
