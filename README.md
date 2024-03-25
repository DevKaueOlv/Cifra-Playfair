### Cifra-Playfair
Implementação da cifra playfair em C padrão

# Relatório Construção do programa

A função chamada **`imprime_matriz_chave`** que imprime a matriz chave utilizada para cifrar e decifrar o texto. Ela recebe como argumento uma matriz **`m`** de tamanho 5x5 que contém a matriz chave.

A função **`cifrar`** implementa a cifragem utilizando a cifra de Playfair para cifrar um texto claro. A função começa criando uma versão pré-processada do texto de entrada (**`texto_preproc`**). Para haver um tratamento no texto tornando todas as letras minúsculas e eliminando os caracteres não alfabéticos. A função identifica as posições dos pares na matriz chave e aplica as regras da cifra para determinar o texto cifrado.

A função **`decifrar`** utiliza a mesma lógica da cifragem, porém aplicando as regras inversas da cifra de playfair.

OBS: Tive bastante dificuldade no tratamento do texto claro caso houvessem caracteres repetidos, mas deu certo no final, e não achei solução para o tratamento do texto claro, caso haja um caractere especial ou acentuação, fiz simplesmente substituir por “x”
