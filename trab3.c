#include <stdio.h>
#include <string.h>

struct Dicio{
    char palavra[50];
    char ocor[20];
    int num;
};
typedef struct Dicio Dicio;

int main(){
    int max = 1000;
    char opt;
    char *texto[10000], *textoaux, linha[100];
    char *token;
    char *tokenpos;
    char *aux;
    char busca[50];
    char posaux[100];
    char frase[50];
    FILE *arq;
    Dicio* invert = malloc(max * sizeof (Dicio));
    int count;
    int posic = 1;
    int comp;

    do{
        opt = menu(opt);
        switch(opt){
            case '0':
                system("cls");
                fflush(stdin);
                count = 0;
                posic = 1;
                strcpy(texto,"");
                arq = fopen("texto.txt", "rt");
                if(arq != NULL){
                    while(!feof(arq)){
                        textoaux = fgets(linha, 100, arq);
                        strcat(texto,textoaux);
                    }
                    token = strtok(texto, " ");
                    while(token != NULL) {
                        comp = 0;
                        for(int i = 0; i < count; i++){
                            if(strcmp(token,invert[i].palavra)==0){
                                strcpy(textoaux," ");
                                sprintf(posaux, "%d", posic);
                                strcat(textoaux,posaux);
                                strcat(invert[i].ocor,textoaux);
                                invert[i].num++;
                                comp++;
                            }
                        }
                        if(comp==0){
                            strcpy(invert[count].palavra,token);
                            sprintf(posaux, "%d", posic);
                            strcpy(invert[count].ocor,posaux);
                            invert[count].num = 1;
                            count++;
                        }
                        posic = posic + strlen(token) + 1;
                        token = strtok(NULL, " ");
                    }
                    fclose(arq);
                }else{
                    perror("texto.txt");
                }
            break;
            case '1':
                system("cls");
                fflush(stdin);
                for(int i = 0;i < count; i++){
                    printf("%s, %d : %s\n",invert[i].palavra,invert[i].num,invert[i].ocor);
                }
            break;
            case'2':
                system("cls");
                fflush(stdin);
                comp = 0;
                strcpy(texto,"");
                printf("Digite a palavra que deseja buscar: ");
                scanf("%s", &busca);
                for(int i = 0;i < count; i++){
                    if(strcmp(invert[i].palavra,busca)==0){
                        int vez = 1;
                        int menuocor;
                        comp++;
                        posic = 0;
                        printf("A palavra %s aparece %d vezes no arquivo, nas posicoes: %s\n",invert[i].palavra,invert[i].num,invert[i].ocor);

                        aux = invert[i].ocor;

                        arq = fopen("texto.txt", "rt");
                        if(arq != NULL){
                            while(!feof(arq)){
                                textoaux = fgets(linha, 100, arq);
                                strcat(texto,textoaux);
                            }
                        }else{
                            perror("texto.txt");
                        }
                        token = strtok(texto,".");
                        comp = strlen(token);
                        tokenpos = "123";
                        while(tokenpos != NULL && menuocor != 10){
                            tokenpos = strtok_r(aux," ",&aux);
                            posic = atoi(tokenpos);
                            while(token != NULL && opt != 1){
                                if(posic<=comp){
                                    printf("%s",token);
                                    vez++;
                                    opt = 1;
                                }else{
                                    token = strtok(NULL,".");
                                    comp = comp + strlen(token) + 1;
                                }
                            }
                            opt = 0;
                            if(invert[i].num >= vez){
                                printf("\nDigite 1 para ir para a proxima ocorrencia: ");
                                fflush(stdin);
                                printf("%s",aux);
                                scanf("%d",menuocor);
                                printf("%s",aux);
                                if(menuocor == 1){

                                }else{
                                    menuocor = 10;
                                }
                            }else{
                                menuocor = 10;
                            }
                        }
                    }
                }
                if(comp==0){
                    printf("\nPalavra não foi encontrada.");
                }
                fflush(stdin);
            break;
            case'x':
                printf("Programa Finalizado\n");
            break;
            default:
                printf("Opcao Invalida\n");
            break;
        }
    }while(opt!='x');
}

int menu(int opt){
    printf("\n---------MENU--------\n");
    printf("0 - Ler arquivo texto\n");
    printf("1 - Apresentar arquivo invertido\n");
    printf("2 - Procurar uma palavra no arquivo invertido\n");
    printf("x - Sair do Sistema\n");
    printf("Digite a opcao desejada: ");
    opt = getchar();
    return(opt);
}
