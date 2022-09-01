//Alunos: Daniel Mota, Eduardo Marculino, Kayky Santana, Leandro Martins e Verner Rafael

#include <stdio.h>
#include <locale.h>
#include <string.h>

int main(){
	setlocale(LC_ALL, "Portuguese");
	int part, i, j, cont = 1, cod[10] = {0,0,0,0,0,0,0,0,0,0};
	
	//Declara��o das fun��es:
	void linha();
	void lerParticipantes(int*);
	void lerCodigoCategoriaNome(int, int[], char[][10], char[][100]);
	void ordemApresentacao(char[10], int, int[], char[][10], char[][100], int*);
	void lerNotas(int, char[10], int[], char[][100], char[][10], float[10][5], int);
	void calcularMedia(int, float[], float[][5], float[][5], float[][5], float[][5], float[][5], float[], float[][5]);
	void imprimirNotas(int, float[][5], float[][5], float[][5], float[][5], float[][5], char[][10]);
	void ranking(int, float[], float[][5], char[][100], char[][10]);
	void resultado(int, float[], float[][5], char[][100], char[][10]);
	
	lerParticipantes(&part);
	float notasJurado1[part][5], notasJurado2[part][5], notasJurado3[part][5], notasJurado4[part][5], notasJurado5[part][5];
	float somaNotas[part];
	float media[part], mediaCrit[part][5];
	char nomeEquipe[part][100];
	char categ[part][10];
	
	lerCodigoCategoriaNome(part, cod, categ, nomeEquipe);	
	
	linha();
	printf("====== Ordem de apresenta��o: ======\n");
	ordemApresentacao("E", part, cod, categ, nomeEquipe, &cont);
	ordemApresentacao("P", part, cod, categ, nomeEquipe, &cont);
	ordemApresentacao("G", part, cod, categ, nomeEquipe, &cont);
	linha();
	
	printf("Crit�rios:\n\n(1) N�vel de organiza��o da equipe(PESO 1).\n(2) Estrat�gia de venda(PESO 1).\n(3) Grau de usabilidade do produto(PESO 2).\n(4) N�vel de maturidade da �rea que pretende atuar(PESO 3).\n(5) Grau de inova��o do produto(PESO 3).\n\n");
    
    //jurado 1
    lerNotas(part, "E", cod, nomeEquipe, categ, notasJurado1, 1);
    lerNotas(part, "P", cod, nomeEquipe, categ, notasJurado1, 1);
    lerNotas(part, "G", cod, nomeEquipe, categ, notasJurado1, 1);
    //jurado 2
	lerNotas(part, "E", cod, nomeEquipe, categ, notasJurado2, 2);
    lerNotas(part, "P", cod, nomeEquipe, categ, notasJurado2, 2);
    lerNotas(part, "G", cod, nomeEquipe, categ, notasJurado2, 2);
    //jurado 3
    lerNotas(part, "E", cod, nomeEquipe, categ, notasJurado3, 3);
    lerNotas(part, "P", cod, nomeEquipe, categ, notasJurado3, 3);
    lerNotas(part, "G", cod, nomeEquipe, categ, notasJurado3, 3);
    //jurado 4
    lerNotas(part, "E", cod, nomeEquipe, categ, notasJurado4, 4);
    lerNotas(part, "P", cod, nomeEquipe, categ, notasJurado4, 4);
    lerNotas(part, "G", cod, nomeEquipe, categ, notasJurado4, 4);
    //jurado 5
    lerNotas(part, "E", cod, nomeEquipe, categ, notasJurado5, 5);
    lerNotas(part, "P", cod, nomeEquipe, categ, notasJurado5, 5);
    lerNotas(part, "G", cod, nomeEquipe, categ, notasJurado5, 5);

	calcularMedia(part, somaNotas, notasJurado1, notasJurado2, notasJurado3, notasJurado4, notasJurado5, media, mediaCrit);
	
	imprimirNotas(part, notasJurado1, notasJurado2, notasJurado3, notasJurado4, notasJurado5, categ);
	
	ranking(part, media, mediaCrit, nomeEquipe, categ);
	
	resultado(part, media, mediaCrit, nomeEquipe, categ);
}

void linha(){
	printf("====================================\n");
}

void lerParticipantes(int *part){
	printf("Insira a quantidade de equipes participantes (Entre 1 e 10): ");
	scanf("%i", &(*part));
	while(*part < 1 || *part > 10){
		system("cls");
		printf("Insira uma quantidade v�lida de participantes (Entre 1 e 10): ");
		scanf("%i", &(*part));
	}
}

void lerCodigoCategoriaNome(int part, int cod[], char categ[][10], char nomeEquipe[][100]){
	//c�digo, categoria e nome ficam na mesma fun��o por utilizar o mesmo valor da vari�vel i(utilizada para indexar a equipe)
	int i, lerCod;
	for(i = 1; i <= part; i++){
		system("cls");
		if (part <= 1){
			printf("===== %i equipe participante. =====\n", part);
		}
		else{
			printf("===== %i equipes partipantes. =====\n", part);
		}
		
		//l� o c�digo da equipe
		printf("Insira o c�digo da equipe %i: ", i);
		scanf("%i", &lerCod);
		
		//verifica se o c�digo � repetido
		int x = 1;
		while(x <= part){
			if(lerCod == cod[x]){
				printf("%i j� � o c�digo de uma equipe, insira um c�digo diferente: ", lerCod);
				scanf("%i", &lerCod);
				x = 1;
			}else{
				x++;
			}
		}
		cod[i] = lerCod;
		
		//l� a categoria da equipe
		linha();
		printf("\n(G)Gest�o\n(E)Educa��o\n(P)Projeto Social\n\n");
		linha();
		printf("Insira a categoria da equipe %i: ", i);
		scanf("%s", &categ[i]);
		
		//verifica se a categoria � valida
		if(strcmp(categ[i], "G") != 0){
			if(strcmp(categ[i], "E") != 0){
				if(strcmp(categ[i], "P") != 0){
					while(1){
						printf("Insira uma categoria v�lida: ");
						scanf("%s", &categ[i]);
						if(strcmp(categ[i], "G") == 0){
							break;
						}
						if(strcmp(categ[i], "E") == 0){
							break;
						}
						if(strcmp(categ[i], "P") == 0){
							break;
						}
					}
				}
			}
		}
		
		//l� o nome da equipe
		printf("Insira o nome da equipe %i: ", i);
		scanf("%s", &nomeEquipe[i]);
		system("cls");
	}
}

void ordemApresentacao(char categoria[10], int part, int cod[], char categ[][10], char nomeEquipe[][100], int *cont){
	int i;
	char nomeCategoria[100];
	//Ordena a apresenta��o das equipe por categoria
	if(strcmp(categoria, "E") == 0){
		strcpy(nomeCategoria, "Educa��o");
	}else if(strcmp(categoria, "P") == 0){
		strcpy(nomeCategoria, "Projeto social");
	}else if(strcmp(categoria, "G") == 0){
		strcpy(nomeCategoria, "Gest�o");
	}
	for(i = 1; i <= part; i++){
		if(strcmp(categ[i], categoria) == 0){
			printf("[C�D: %i] A equipe %s(%s) ser� a %i� a apresentar.\n", cod[i], nomeEquipe[i], nomeCategoria, *cont);
			(*cont)++;
		}
	}
}

void lerNotas(int part, char categoria[10], int cod[], char nomeEquipe[][100], char categ[][10], float notasJurado[10][5], int numJurado){
	int i, j;
	for(i = 1; i <= part; i++){
		if(strcmp(categ[i], categoria) == 0){
			printf("Digite as notas do %i� jurado (De 0 a 10).\n", numJurado);
        	printf("========== Equipe: [C�D: %i] %s ==========\n", cod[i], nomeEquipe[i]);
			for(j = 1; j <= 5; j++){
            	printf("%i� Crit�rio: ",j);
            	scanf("%f", &notasJurado[i][j]);
            	while(notasJurado[i][j] < 0.0 || notasJurado[i][j] > 10.0){
            		printf("Digite uma nota v�lida (de 0 a 10): ");
            		scanf("%f", &notasJurado[i][j]);
				}
        	}
        	printf("\n");
        }
    }
}

void calcularMedia(int part, float somaNotas[], float notasJurado1[][5], float notasJurado2[][5], float notasJurado3[][5], float notasJurado4[][5], float notasJurado5[][5], float media[], float mediaCrit[][5]){
	int i, j;
	for(i = 1; i <= part; i++){
		for(j = 1; j <= 5; j++){
			if(j == 1 || j == 2){
				somaNotas[i] += notasJurado1[i][j] * 1;
				somaNotas[i] += notasJurado2[i][j] * 1;
				somaNotas[i] += notasJurado3[i][j] * 1;
				somaNotas[i] += notasJurado4[i][j] * 1;
				somaNotas[i] += notasJurado5[i][j] * 1;
				mediaCrit[i][j] = (notasJurado1[i][j] + notasJurado2[i][j] + notasJurado3[i][j] + notasJurado4[i][j] + notasJurado5[i][j])/5;
			}
			if(j == 3){
				somaNotas[i] += notasJurado1[i][j] * 2;
				somaNotas[i] += notasJurado2[i][j] * 2;
				somaNotas[i] += notasJurado3[i][j] * 2;
				somaNotas[i] += notasJurado4[i][j] * 2;
				somaNotas[i] += notasJurado5[i][j] * 2;
				mediaCrit[i][j] = (notasJurado1[i][j] + notasJurado2[i][j] + notasJurado3[i][j] + notasJurado4[i][j] + notasJurado5[i][j])/5;
			}
			if(j == 4 || j == 5){
				somaNotas[i] += notasJurado1[i][j] * 3;
				somaNotas[i] += notasJurado2[i][j] * 3;
				somaNotas[i] += notasJurado3[i][j] * 3;
				somaNotas[i] += notasJurado4[i][j] * 3;
				somaNotas[i] += notasJurado5[i][j] * 3;
				mediaCrit[i][j] = (notasJurado1[i][j] + notasJurado2[i][j] + notasJurado3[i][j] + notasJurado4[i][j] + notasJurado5[i][j])/5;
			}
		}
	}
	for(i = 1; i <= part; i++){
		media[i] = somaNotas[i]/((1 + 1 + 2 + 3 + 3) * 5);
	}
}

void imprimirNotas(int part, float notasJurado1[][5], float notasJurado2[][5], float notasJurado3[][5], float notasJurado4[][5], float notasJurado5[][5], char categ[][10]){
	system("cls");
	int i, j;
	printf("           J1  J1  J1  J1  J1  J2  J2  J2  J2  J2  J3  J3  J3  J3  J3  J4  J4  J4  J4  J4  J5  J5  J5  J5  J5\n");
	printf("           C1  C2  C3  C4  C5  C1  C2  C3  C4  C5  C1  C2  C3  C4  C5  C1  C2  C3  C4  C5  C1  C2  C3  C4  C5  \n");
	for(i = 1; i <= part; i++){
		printf("Equipe %i %s ", i, categ[i]);
		for(j = 1; j <= 5; j++){
			printf("%.1f ", notasJurado1[i][j]);
		}
		for(j = 1; j <= 5; j++){
			printf("%.1f ", notasJurado2[i][j]);
		}
		for(j = 1; j <= 5; j++){
			printf("%.1f ", notasJurado3[i][j]);
		}
		for(j = 1; j <= 5; j++){
			printf("%.1f ", notasJurado4[i][j]);
		}
		for(j = 1; j <= 5; j++){
			printf("%.1f ", notasJurado5[i][j]);
		}
		printf("\n");
	}
}

void ranking(int part, float media[], float mediaCrit[][5], char nomeEquipe[][100], char categ[][10]){
	int i, j, x;
	float aux, aux2[part][5];
	char auxNome[100];

	//deixa as notas em ordem crescente
	
	printf("\n=========RANKING=========\n           C1   C2   C3   C4   C5   M\n");
	for(i = 1; i <= part; i++){
		for(j = i+1; j <= part; j++){
			if(media[i] > media[j]){
				// ordena a media
				aux = media[i];
				media[i] = media[j];
				media[j] = aux;
				
				// ordena o nome
				strcpy(auxNome, nomeEquipe[i]);
				strcpy(nomeEquipe[i], nomeEquipe[j]);
				strcpy(nomeEquipe[j], auxNome);
				
				// ordena a categoria
				strcpy(auxNome, categ[i]);
				strcpy(categ[i], categ[j]);
				strcpy(categ[j], auxNome);
							
				// ordena a media por criterio
				for(x = 1; x <= 5; x++){
					aux2[part][x] = mediaCrit[i][x];
					mediaCrit[i][x] = mediaCrit[j][x];
					mediaCrit[j][x] = aux2[part][x];
					
				}
			}
		}
	}
	
	//imprime o ranking das equipes na categoria Educa��o		
	for(i = part; i > 0; i--){
		if(strcmp(categ[i], "E") == 0){
			printf("Educa��o\n");
			printf("Equipe: %s ", nomeEquipe[i]);
			for(j = 1; j <= 5; j++){
				printf("%.1f  ", mediaCrit[i][j]);
			}
			printf("%.1f\n", media[i]);
		}
	}
	
	//imprime o ranking das equipes na categoria Projeto Social	
	for(i = part; i > 0; i--){
		if(strcmp(categ[i], "P") == 0){
			printf("\nProjeto Social\n");
			printf("Equipe: %s ", nomeEquipe[i]);
			for(j = 1; j <= 5; j++){
				printf("%.1f  ", mediaCrit[i][j]);
			}
			printf("%.1f\n", media[i]);
		}
	}
	
	//imprime o ranking das equipes na categoria Gest�o		
	for(i = part; i > 0; i--){
		if(strcmp(categ[i], "G") == 0){
			printf("\nGest�o\n");
			printf("Equipe: %s ", nomeEquipe[i]);
			for(j = 1; j <= 5; j++){
				printf("%.1f  ", mediaCrit[i][j]);
			}
			printf("%.1f\n", media[i]);
		}
	}
}

void resultado(int part, float media[], float mediaCrit[][5], char nomeEquipe[][100], char categ[][10]){
	void desempate(float, char[100], char[][100], int, float[], float[][5], char[][10], char[100]);
	printf("\n=========Resultado final=========\n\n");
	
	int i;
	float maiorE = 0, maiorP = 0, maiorG = 0;
	char vencedoraE[100] = "N�o h� equipes", vencedoraP[100] = "N�o h� equipes", vencedoraG[100] = "N�o h� equipes";
	
	//armazena o nome da equipe vencedora em cada categoria
	for(i = 1; i <= part; i++){
		if(strcmp(categ[i], "E") == 0){
			if(media[i] > maiorE){
				maiorE = media[i];
				strcpy(vencedoraE, nomeEquipe[i]);
			}
		}
	}
	
	for(i = 1; i <= part; i++){
		if(strcmp(categ[i], "P") == 0){
			if(media[i] > maiorP){
				maiorP = media[i];
				strcpy(vencedoraP, nomeEquipe[i]);
			}
		}
	}
	
	for(i = 1; i <= part; i++){
		if(strcmp(categ[i], "G") == 0){
			if(media[i] > maiorG){
				maiorG = media[i];
				strcpy(vencedoraG, nomeEquipe[i]);
			}
		}
	}
	
	desempate(maiorE, vencedoraE, nomeEquipe, part, media, mediaCrit, categ, "E");
	desempate(maiorP, vencedoraP, nomeEquipe, part, media, mediaCrit, categ, "P");
	desempate(maiorG, vencedoraG, nomeEquipe, part, media, mediaCrit, categ, "G");
	
	printf("Educa��o: %s\n", vencedoraE);
	printf("Projeto Social: %s\n", vencedoraP);
	printf("Gest�o: %s\n", vencedoraG);
	
	//desclassificadas
	printf("\n==========Equipe(s) desclassificada(s): ==========\n\n");
	for(i = 1; i <= part; i++){
		if(media[i] < 7){
			printf("%s\n", nomeEquipe[i]);	
		}
	}
}

void desempate(float maior, char vencedora[100], char nomeEquipe[][100], int part, float media[], float mediaCrit[][5], char categ[][10], char categoria[10]){
	int pos[10], i, venc = 0;
	float auxM = 0;
	
	//pega o �ndicie das maiores notas no crit�rio D
	for(i = 1; i <= part; i++){
		if(media[i] == maior){
			if(mediaCrit[i][4] > auxM && strcmp(categ[i], categoria) == 0){
				auxM = mediaCrit[i][4];
				venc = i;
			}
		}
	}
	
	//armazena o nome da equipe vencedora no criterio de desempate	
	if(strcmp(categ[venc], "E") == 0){
		strcpy(vencedora, nomeEquipe[venc]);	
	}else if(strcmp(categ[venc], "P") == 0){
		strcpy(vencedora, nomeEquipe[venc]);
	}else if(strcmp(categ[venc], "G") == 0){
		strcpy(vencedora, nomeEquipe[venc]);
	}	
}
