# Componentes Biconexas

Imagine-se em um planeta distante, onde redes de computadores são frequentemente atingidas por tempestades de raios e eventos eletromagnéticos. Para enfrentar esse desafio, uma nova tecnologia revolucionária está prestes a ser implementada: os para-raios. Porém, há uma regra crucial: eles só podem ser instalados nos "links de borda" dos clusters de rede, nunca no interior.


## Objetivo

O objetivo deste trabalho é desenvolver um algoritmo capaz de listar os "links de borda" da rede, identificar todos os clusters e construir a Floresta de clusters-bordas.

## O que são esses termos?

- **Links de Borda**: São os links que conectam diferentes clusters de rede. Ou seja, são aqueles que, se desconectados, resultam em isolamento entre dois ou mais clusters.
- **Clusters**: São conjuntos de links de rede onde, mesmo que um link seja removido, ainda é possível trocar mensagens entre todos os outros links do cluster.
- **Floresta de Clusters-Bordas**: É uma representação da rede onde cada cluster é representado por um vértice, e há uma aresta entre um vértice de cluster e um vértice de link de borda se o cluster correspondente compartilha esse link de borda.

### Exemplo
![image](https://github.com/leticiascofield/BiconnectedComponents/assets/125830543/4b2b6097-1044-4d83-b2b7-01f0b719f15b)

Os links denotados por quadrados são os links de borda, no caso são os vértices: c, d, h. <br>
Cada cluster é marcado por um círculo, sendo assim temos os clusters: {a, b, c, d}, {c, h}, {d, e, f, g}, {h, i}.

![image](https://github.com/leticiascofield/BiconnectedComponents/assets/125830543/d8089e6a-0856-458e-944a-0be84e4bdb3f)

Floresta de clusters-bordas correspondente à rede da imagem anterior.
## Implementação

A implementação é feita em linguagem C++, foi utilizada uma abordagem eficiente baseada em busca em profundidade (DFS). Com estruturas de dados bem pensadas e algoritmos otimizados, garantindo que o programa seja rápido e robusto, mesmo para redes com milhões de vértices.

## Passos para Execução
Para compilar o código, basta utilizar um compilador C++ como o g++, fornecendo o arquivo de origem "tp1.cpp":

```bash
g++ -o tp1 tp1.cpp
```
Depois de compilado, basta executar o programa e fornecer as entradas necessárias:

```bash
./tp1
```

## Mais informações e detalhes
Este README fornece uma visão geral do trabalho e da implementação. Para mais detalhes sobre o funcionamento do algoritmo e sobre o código-fonte, consulte o enunciado no trabalho (enunciado.pdf) e próprio código (tp1.cpp).

## Referências
GeeksforGeeks: [Biconnected Components - GeeksforGeeks](https://www.geeksforgeeks.org/biconnected-components/?ref=ml_lbp) <br>
Wikipedia: [Biconnected Component - Wikipedia](https://en.wikipedia.org/wiki/Biconnected_component)

