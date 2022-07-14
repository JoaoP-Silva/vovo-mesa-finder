# vovo-mesa-finder
A partir de uma lista de retângulos, encontrar o retângulo de maior área que pode ser inserido em um mapa utilizando programação dinâmica.

# Sobre o projeto
vovo-mesa-finder é um projeto que trata da seguinte situação hipotética: sua avó quer reformar sua humilde casa e dispôe de uma lista de mesas retangulares que disse que pensa em adquirir, e você como um bom neto quer que sua avó tenha em sua casa a maior mesa possível. Dado um mapa binário que representa a sala de sua avó, separado em espaços vazios (possíveis de ocupar a mesa) e espaços já ocupados, qual a mesa de maior área, dentre as que foram listadas, que pode ser colocada na sala da vó?
# Solução pensada

1) **Modelagem**

O problema pode ser pensado como: enumerar soluções viáveis de áreas dentro do mapa, e a partir desta lista de soluções, verificar qual a mesa de maior área que pode ser inserida no mapa. O mapa é uma matriz binária, e como o número de submatrizes retangulares é exponencial ao tamanho da matriz, é inviável enumerar todas as soluções possíveis de áreas dentro do mapa. Assim, a solução pensada ignora soluções redundantes, de forma que se um retângulo viável no mapa já foi encontrado previamente, ele é salvo e incorporado no processamento de novas soluções. Após a enumeração (limitada) dos retângulos livres no mapa, é calculada a mesa de maior área que pode ser inserida em alguma deles.

2) **Implementação**

A implementação da solução começa com a leitura do mapa, caso haja mais colunas do que linhas na matriz de entrada, ela é transposta. Essa operação é feita de forma a padronizar a entrada e será importante no momento de enumerar as áreas possíveis no mapa. Após isso é gerada uma matriz de inteiros maiores ou iguais a zero $m$ que salva a quantidade de espaços livres seguidos por coluna, ou seja, se em uma coordenada $(i, j)$ da matriz $m$ verifica-se um inteiro $k ≥$ 0, na mesma coluna $j$, até a linha $i$ existem $(k - 1)$ coordenadas válidas seguidas. A matriz $m$ de dimensão $l$ x $c$ será a matriz que será usada para enumerar os retângulos viáveis no mapa. Para processar $m$ foi definida a função $genMaxArea$ que recebe como parâmetro uma matriz $n$ de inteiros no padrão especificado anteriormente por $m$ (ressalta o fato da necessidade da matriz ter o número de linhas maior ou igual o número de colunas). $genMaxArea$ gera duas matrizes de dimensões iguais as de $n$, uma matriz $leftlimit$ e outra $rightlimit$, as quais são preenchidas de forma a salvar os limites aos lados esquerdo e direto que se podem extrapolar as alturas calculadas em $n$. Assim pode-se calcular a largura de cada retângulo pela diferença dos valores em $rightlimit$ e $leftlimit$ e o comprimento pelo valor previamente calculado em $n$. Para salvar as áreas importantes é declarado um vetor de inteiros $result$ que tem tamanho $l$, neste vetor cada retângulo $r$ viável de lados $MA$ e $ME$ calculado em $n$, sendo $MA$ o lado maior de $r$, é salvo em $l$, de forma que $l[MA]= ME$. Caso já haja um retângulo na posição $[MA]$ salvo, o retângulo de maior valor $ME$ é mantido no vetor. Ao fim da execução da função $genMaxArea$, o vetor $result$ é retornado com o maior retângulo possível para cada valor de lado possível. Dessa forma, agora o problema é reduzido em encontrar a maior mesa que cabe em algum dos retângulos em $result$. Uma lista de mesas $tables$ é declarada, e inserem-se os dados da entrada. As mesas são ordenadas pela área e de forma decrescente e para cada mesa em $tables$, calcula-se o maior lado $MA$ e menor lado $ME$, assim pode-se realizar a consulta em $result$ de forma que, se para em alguma solução que tenha posição maior ou igual a $MA$ o valor salvo seja maior ou igual a $ME$, a área é viável para a mesa em tables e é salva em uma variável $chosentable$. Caso a próxima mesa tenha área menor que $chosen_table$, $chosen_table$ é impresso, caso contrário a mesa de maior comprimento é salva em $chosentable$. Enquanto não houver uma mesa selecionada, o procedimento se repete, até o fim do vetor $tables$.

# Arquivo de entrada
O programa terá como entrada na sua primeira linha linha contendo dois inteiros N e M separados por espaço, que são as dimensões da casa da avó. Em seguida, há $N$ linhas contendo $M$ caracteres descrevendo a planta arquitetônica. Um caractere "." (ponto) representa um espaçoo vazio, enquanto que o caractere "#" representa um espaço preenchido (parede ou outro móvel).
A linha seguinte contém um inteiro $K$ que representa o tamanho da lista de opções de mesa que sua avó pode comprar. As próximas $K$ linhas contém, cada uma, dois inteiros $C_i$ e $L_i$ separados por espaço, representando o comprimento e largura da i-ésima mesa.
O sistema vem com 4 valores de input salvos na pasta input, por padrão é utilizado o input4, mas pode-se alterar a entrada do programa através do Makefile. Na linha 11 do Makefile se encontra o nome do arquivo de entrada:
```Makefile
INPUT = <NOME_ENTRADA.txt>
```
# Exemplo prático de entrada / saída
Considerando a figura abaixo como o mapa da casa da avó:

![image](https://user-images.githubusercontent.com/73205375/178860938-12632cc6-9538-4ff7-b302-9099d2dfcd68.png)

A respectiva entrada seria(com mesas de valores 3 3, 4 6, 15 2 e 2 7):

![image](https://user-images.githubusercontent.com/73205375/178861080-6fa36fae-18f2-483e-a385-1d6c4b28b147.png)

A saída seria:

![image](https://user-images.githubusercontent.com/73205375/178861115-801bc3f8-7292-4df0-b461-fd6537746d73.png)

# Instruções de compilação e execução
Para executar o programa é necessário ter instalada a função "make" na máquina, além de um compilador C++. A maneira mais fácil para instalar o make em um sistema windows é utilizando o [Chocolatey](https://chocolatey.org/install). Após a instalação do Chocolatey, digite no terminal:
```
choco install make
```
Após a instalação do Make, para compilar o código e gerar o executável do programa digite no diretório do programa: ```make all```. Após compilar o código, para executá-lo digite ```make run```. Se o programa for executado com sucesso, a saída especificada deve ser impressa na saída padrão.

# Considerações finais
Foi interessante a realização do projeto, programação dinâmica é uma tópico importante quando se trata de desafios combinatórios (como problema da mochila) ambos códigos da função genMaxArea e o main podem ser otimizados ao preencher as três matrizes ao mesmo tempo. A complexidade de espaço da função genMaxArea pode ser otimizada tabém fazendo com que ao invés de utilizar matrizes para alocar os limites ao lado esquero e direito, processar os dados "on demmand" e salvar apenas um vetor de variáveis, que vai sendo modificado à medida que se percorre a matriz de entrada. São modificações válidas mas que manteriam a complexidade de tempo no pior caso em O($l.c + l.m$) sendo $l$ o número de linhas do mapa da casa da avó $c$ o número de colunas e $m$ o número de mesas possíveis.

## Autores

| [<img src="https://avatars.githubusercontent.com/u/73205375?v=4" width=115><br><sub>João Pedro Fernandes Silva</sub>](https://github.com/JoaoP-Silva)
