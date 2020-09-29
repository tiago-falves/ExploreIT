# CAL1920

Neste trabalho, pretende-se implementar uma aplicação que, dado um conjunto
de pontos de interesse, locais de confluência e trilhos, produza circuitos
que possam ser percorridos pelos trabalhadores sendo que cada trilho tem um
grau de dificuldade e uma duração estimada, função da distância e do declive
do mesmo.


### Casos de utilização Implementados ###

1. **Visualização do grafo completo** - O programa fornece a possibilidade
de visualizar graficamente um grafo completo, com todos os seus nós e
arestas.
2. **Visualização da Componente fortemente conexa do mapa** - O programa
fornece a possibilidade de visualizar graficamente os nós e arestas
da componente mais fortemente conexa do grafo.
3. **Cálculo do caminho mais adequado ao grupo escolhido** - Esta é
a funcionalidade principal do programa, em que o programa dado um
conjunto de restrições calcula os percursos mais adequados para o grupo.
4. **Cálculo da distância total de um trilho** - O programa deverá ser
capaz de calcular a distância total percorrida por um determinado grupo
5. **Cálculo de caminhos de um ponto a outro com uma certa distância**
6. **Cálculo de caminhos de um ponto a outro com uma certa distância
e dificuldade**
7. **Cálculo do caminho com POI obrigatórios** - Opção de introduzir
pontos de interesse obrigatórios.
8. **Cálculo do caminho que maximize POI’s** - Opção que maximize
os pontos de interesse entre um ponto e outro, com um certo tempo de
duração, independentemente da dificuldade.
9. **Inserção e remoção de pontos de Confluência e de pontos de
interesse obrigatórios**
10. **Escolha entre várias cidades, sendo facilmente adicionada qualquer
outra**
11. **Opção de ver pontos default de modo a facilitar a escolha dos
pontos de confluência**
12. **Pré-Processamento de cada cidade** - incluindo dificuldades, floyd
warshall e conetividade
