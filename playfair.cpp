#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

// Fun��o para imprimir a matriz chave
void imprime_matriz_chave(char m[5][5]) {
    int i, j;
    for(i = 0; i < 5; i++) {
        printf("\n");
        for (j = 0; j < 5; j++) printf("%c ", m[i][j]);
    }
}

// Fun��o para cifrar o texto claro
void cifrar(char texto[100], char cifra[100], char m[5][5]) {
    int i, j, k = 0;
    char texto_preproc[100];

    // Prepara��o do texto
     for(i = 0, j = 0; texto[i] != '\0'; i++) {
        if((texto[i] >= 'a' && texto[i] <= 'z') || (texto[i] >= 'A' && texto[i] <= 'Z')) {
            texto_preproc[j++] = tolower(texto[i]); // Converter para min�sculas
        }
    }
    texto_preproc[j] = '\0';

    // Adicionar caractere fict�cio se o n�mero de caracteres for �mpar
    if(strlen(texto_preproc) % 2 != 0) {
        texto_preproc[strlen(texto_preproc)] = 'x';
    }

    // Cifragem de cada par de letras
    for(i = 0; i < strlen(texto_preproc); i += 2) {
        char letra1 = texto_preproc[i];
        char letra2 = texto_preproc[i + 1];
        int linha1, coluna1, linha2, coluna2;

        // Encontrar as posi��es de cada letra na matriz chave
        for(j = 0; j < 5; j++) {
            for(k = 0; k < 5; k++) {
                if(m[j][k] == letra1) {
                    linha1 = j;
                    coluna1 = k;
                }
                if(m[j][k] == letra2) {
                    linha2 = j;
                    coluna2 = k;
                }
            }
        }

        // Aplicar regras da cifra de Playfair
        if(linha1 == linha2) { // Mesma linha
            cifra[i] = m[linha1][(coluna1 + 1) % 5];
            cifra[i + 1] = m[linha2][(coluna2 + 1) % 5];
        } else if(coluna1 == coluna2) { // Mesma coluna
            cifra[i] = m[(linha1 + 1) % 5][coluna1];
            cifra[i + 1] = m[(linha2 + 1) % 5][coluna2];
        } else { // Forma retangular
            cifra[i] = m[linha1][coluna2];
            cifra[i + 1] = m[linha2][coluna1];
        }
    }

    cifra[strlen(texto)] = '\0'; // Adicionar terminador de string
    printf("\nTexto cifrado: %s\n", cifra);
}

// Fun��o para decifrar o texto cifrado
void decifrar(char cifra[100], char texto[100], char m[5][5]) {
    int i, j, k = 0;
    char texto_preproc[100];

    // Prepara��o do texto
     for(i = 0, j = 0; texto[i] != '\0'; i++) {
        if((texto[i] >= 'a' && texto[i] <= 'z') || (texto[i] >= 'A' && texto[i] <= 'Z')) {
            texto_preproc[j++] = tolower(texto[i]); // Converter para min�sculas
        }
    }
    texto_preproc[j] = '\0';

    // Adicionar caractere fict�cio se o n�mero de caracteres for �mpar
    if(strlen(texto_preproc) % 2 != 0) {
        texto_preproc[strlen(texto_preproc)] = 'x';
    }
    
    // Decifrar cada par de letras
    for(i = 0; i < strlen(cifra); i += 2) {
        char letra1 = cifra[i];
        char letra2 = cifra[i + 1];
        int linha1, coluna1, linha2, coluna2;

        // Encontrar as posi��es de cada letra na matriz chave
        for(j = 0; j < 5; j++) {
            for(k = 0; k < 5; k++) {
                if(m[j][k] == letra1) {
                    linha1 = j;
                    coluna1 = k;
                }
                if(m[j][k] == letra2) {
                    linha2 = j;
                    coluna2 = k;
                }
            }
        }

        // Aplicar regras da cifra de Playfair inversas
        if(linha1 == linha2) { // Mesma linha
            texto[i] = m[linha1][(coluna1 - 1 + 5) % 5];
            texto[i + 1] = m[linha2][(coluna2 - 1 + 5) % 5];
        } else if(coluna1 == coluna2) { // Mesma coluna
            texto[i] = m[(linha1 - 1 + 5) % 5][coluna1];
            texto[i + 1] = m[(linha2 - 1 + 5) % 5][coluna2];
        } else { // Forma retangular
            texto[i] = m[linha1][coluna2];
            texto[i + 1] = m[linha2][coluna1];
        }
    }

    texto[strlen(cifra)] = '\0'; // Adicionar terminador de string
}


int main() {
    setbuf(stdout, NULL); // Limpar o buffer de sa�da

    char m[5][5], v[26]; 
    int i, j, k, p; 
    char chave[10], escolha;
    char texto[100], cifra[100];

    // cria��o do vetor alfab�tico de controle (cont�m as 26 letras em ordem)
    for (i = 0; i < 26; i++) {
        v[i] = 97 + i;
    }
    v[i] = '\0';

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Cifragem\n");
        printf("2. Decifragem\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf(" %c", &escolha);

        switch(escolha) {
            case '1':
                // Entrada da chave
                do {
                    printf("\nDigite uma chave alfabetica entre 6 e 10 caracteres: ");
                    scanf("%s", chave);
                } while(strlen(chave) < 6);

                // elimina do vetor alfab�tico de controle as letras da chave (move })
                for (i = 0; i < strlen(chave); i++) {
                    v[(chave[i]) - 97] = 123;
                }

                // Cria��o da matriz chave - parte 1: distribui os caracteres da chave
                for (i = 0, k = 0; i < 2; i++) {
                    for(j = 0; j < 5; j++) {
                        m[i][j] = chave[k++];
                        if(k > strlen(chave)) break;
                    }
                    m[i][5] = '\0';   
                }

                // Cria��o da matriz chave - parte 2: distribui os demais caracteres
                // p = usado para continuar onde parou na linha 1 da matriz
                if (j == 5) 
                    p = 0;
                else 
                    p = j - 1; 
                k = 0;
                for (i = 1; i < 5; i++) {
                    if (i == 1 && p == 0) 
                        i = 2; // a chave tem 10 chars, come�ar na linha 2
                    for(j = 0; j < 5; j++, k++) {
                        if (i == 1 && j == 0) 
                            j += p; 
                        if (v[k] != 123 && v[k] != 'j') 
                            m[i][j] = v[k];
                        else 
                            j--;
                    }
                }

                printf("\nMatriz chave gerada:\n");
                imprime_matriz_chave(m);

                printf("\nDigite o texto claro: "); 
                scanf(" %[^\n]", texto);
                cifrar(texto, cifra, m);
                break;

            case '2':
                printf("\nDigite o texto cifrado: ");
                scanf(" %[^\n]", cifra);
                
                // Entrada da chave
                do {
                    printf("\nDigite a chave alfabetica entre 6 e 10 caracteres: ");
                    scanf("%s", chave);
                } while(strlen(chave) < 6);

                // elimina do vetor alfab�tico de controle as letras da chave (move })
                for (i = 0; i < strlen(chave); i++) {
                    v[(chave[i]) - 97] = 123;
                }

                // Cria��o da matriz chave - parte 1: distribui os caracteres da chave
                for (i = 0, k = 0; i < 2; i++) {
                    for(j = 0; j < 5; j++) {
                        m[i][j] = chave[k++];
                        if(k > strlen(chave)) break;
                    }
                    m[i][5] = '\0';   
                }

                // Cria��o da matriz chave - parte 2: distribui os demais caracteres
                // p = usado para continuar onde parou na linha 1 da matriz
                if (j == 5) 
                    p = 0;
                else 
                    p = j - 1; 
                k = 0;
                for (i = 1; i < 5; i++) {
                    if (i == 1 && p == 0) 
                        i = 2; // a chave tem 10 chars, come�ar na linha 2
                    for(j = 0; j < 5; j++, k++) {
                        if (i == 1 && j == 0) 
                            j += p; 
                        if (v[k] != 123 && v[k] != 'j') 
                            m[i][j] = v[k];
                        else 
                            j--;
                    }
                }

                printf("\nMatriz chave gerada:\n");
                imprime_matriz_chave(m);

                decifrar(cifra, texto, m);
                printf("\nTexto decifrado: %s\n", texto);
                break;

            case '0':
                printf("\nEncerrando o programa.\n");
                break;

            default:
                printf("\nOpcao invalida. Escolha novamente.\n");
        }

    } while(escolha != '0');

    return 0;
}
