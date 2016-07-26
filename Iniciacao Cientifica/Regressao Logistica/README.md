# Regressão Logística
Objetivo: estimar o desempenho do algoritmo de regressão logística pelo Apache Spark e pelo MapReduce do Apache Hadoop.

Para isso foram desenvolvidos 3 scripts:

1. [Spark](spark.py): implementação do algoritmo utilizando somente o Apache Spark;
2. [Spark com MLib](spark_mlib.py): implementação do algoritmo utilizando o Apache Spark e a biblioteca MLib;
3. [MapReduce com MLib](hadoop.py): implementação do algoritmo utilizando MapReduce do Hadoop e MLib;

## Scripts
Os scripts foram escritos em Python.

Para utilizar o script que faz o uso do Spark sem MLib:
> python spark.py [dataset, ex: data/spark_sample_1.txt] [numero de iteracoes, ex: 100]

Para utilizar o script que faz o uso do Spark com MLib:
> python spark_mlib.py [dataset, ex: data/spark_mlib_sample_1.txt] [numero de iteracoes, ex: 100]

Para utilizar o script que faz o uso do Hadoop:
> python hadoop.py [dataset, ex: data/hadoop_sample_1.txt] [numero de iteracoes, ex: 100]



## Ajuste adicional
Para executar os testes sobre o Apache Spark, foi feito algumas mudanças nas configurações do mesmo para evitar outputs de de informações, warnings e erros. Essa alteração foi realizada para diminuir o tempo gasto para imprimir os logs na tela.

As alterações foram feitas seguindo [essas instruções no StackOverflow](http://stackoverflow.com/questions/25193488/how-to-turn-off-info-logging-in-pyspark). A mudança realizada foi de:
> log4j.rootCategory=INFO, console

Para:
> log4j.rootCategory=OFF, console



## Datasets
Com o objetivo de medir o impacto dos dados da entrada, foram criados 3 datasets de teste para cada script. São eles:

Spark sem MLib:

1. [Sample 1](data/spark_sample_1.txt): pequeno, com 300 dados;
2. [Sample 2](data/spark_sample_2.txt): médio, com 3.000 dados;
3. [Sample 3](data/spark_sample_3.txt): grande, com 30.000 dados;

Spark com MLib:

1. [Sample 1](data/spark_mlib_sample_1.txt): pequeno, com 300 dados;
2. [Sample 2](data/spark_mlib_sample_2.txt): médio, com 3.000 dados;
3. [Sample 3](data/spark_mlib_sample_3.txt): grande, com 30.000 dados;

Hadoop:

1. [Sample 1](data/hadoop_sample_1.txt): pequeno, com 300 dados;
2. [Sample 2](data/hadoop_sample_2.txt): médio, com 3.000 dados;
3. [Sample 3](data/hadoop_sample_3.txt): grande, com 30.000 dados;



## Resultados locais
Os resultados locais foram computados em uma máquina com a seguinte configuração: OSX 10.11.6 - 2,5GHz i7 - 16GB memória - Python 2.7.10. Os testes foram realizados com as frameworks nas versões Apache Spark v1.6.2 e Apache Hadoop v2.6.

O tempo foi calculado executando:
> time python {spark|spark_mlib|hadoop}.py data/{sample}.txt {10|100|1000}

#### Apache Spark sem MLib
|          | 10 iterações | 100 iterações | 1.000 iterações |
|----------|--------------|---------------|----------------|
| sample 1 | 0m5.356s | 0m5.392s | 0m5.375s |
| sample 2 | 0m5.871s | 0m5.886s | 0m5.941s |
| sample 3 | 0m6.373s | 0m7.050s | 0m7.039s |

#### Apache Spark com MLib
|          | 10 iterações | 100 iterações | 1.000 iterações |
|----------|--------------|---------------|----------------|
| sample 1 | 0m5.137s | 0m6.395s | 0m13.794s |
| sample 2 | 0m5.347s | 0m6.588s | 0m14.202s |
| sample 3 | 0m5.919s | 0m7.445s | 0m17.858s |

#### Apache Hadoop
|          | 10 iterações | 100 iterações | 1.000 iterações |
|----------|--------------|---------------|----------------|
| sample 1 | - | - | - |
| sample 2 | - | - | - |
| sample 3 | - | - | - |



## Referências
1. http://spark.apache.org/docs/latest/ml-classification-regression.html#logistic-regression
2. http://spark.apache.org/docs/latest/mllib-linear-methods.html#logistic-regression
3. http://wiki.apache.org/hadoop/HadoopMapReduce
4. http://www.michael-noll.com/tutorials/writing-an-hadoop-mapreduce-program-in-python/
