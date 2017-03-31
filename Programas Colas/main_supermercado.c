#include "TADColaDin.h" 
#include "presentacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_CAJEROS 10
int Mcd(int num1,int num2);
int ExtMcd(int num1,int num2);
main()
{
int i,j,num_cajeros,time_client,*cajeros,mcd,aux;
boolean *dispo;
unsigned int time_base=0,client=0;
elemento aux_element;
srand(time(NULL));
puts("THE ULTIMATE MARKET");
puts("INTRODUZCA EL NUMERO DE CAJEROS DEL SUPERMERCADO :");
scanf("%d",&num_cajeros);
if(num_cajeros==0 || (num_cajeros>MAX_CAJEROS)) exit(1);
cajeros=(int*)malloc(num_cajeros*sizeof(int));
dispo=(boolean*)malloc(num_cajeros*sizeof(boolean));
cola cola_cajeros[num_cajeros];
for(i=0;i<num_cajeros;i++)
	{
	Initialize(&cola_cajeros[i]);
	dispo[i]=FALSE;
	printf("TIEMPO DE ATENCION DE CAJERA %d (MS):\n ",i+1);
	scanf("%d",cajeros+i);
	}
puts("INTRODUCE EL TIEMPO DE LLEGADA DE CADA UNO DE LOS CLIENTES:");
scanf("%d",&time_client);
ClearScreen();
mcd=Mcd(cajeros[0],time_client);
for(i=1;i<num_cajeros;i++) mcd=Mcd(mcd,cajeros[i]);
printf("THE ULTIMATE MARKET \n CAJEROS %d ",mcd);
for(i=0;i<num_cajeros;i++) 
	{
	MoveCursor((i+1)*10,3);
	printf("%d",i+1);
	MoveCursor((i+1)*10,2);
	printf("%d",cajeros[i]);
	cajeros[i]/=mcd;
	}
time_client/=mcd;
while(TRUE)
	{
	Ms(mcd); //TIEMPO BASE 
	if(time_base%time_client==0)
		{
		client++;
		aux_element.n=client;
		aux=rand()%num_cajeros;
		Queue(&cola_cajeros[aux],aux_element);
		MoveCursor((aux+1)*10,SizeCola(&cola_cajeros[aux])+4);
		printf("%d",client);
		}
	for(i=0;i<num_cajeros;i++)
		if(time_base%cajeros[i]==0 || (dispo[i]==TRUE))
			{
			if(Empty(&cola_cajeros[i])!=TRUE)
				{
				dispo[i]=FALSE;
				aux=SizeCola(&cola_cajeros[i]);
				aux_element=Dequeue(&cola_cajeros[i]);
				MoveCursor(((i+1)*10)-2,4);
				printf(">>%d<<",aux_element.n);	
				if(Empty(&cola_cajeros[i])!=TRUE)
					{
					for(j=0;j<aux-1;j++)
						{
						MoveCursor(((i+1)*10),5+j);
						aux_element=Element(&cola_cajeros[i],j+1);	
						printf("%d",aux_element.n);
						}
					MoveCursor(((i+1)*10),4+aux);
					printf("     ",aux_element.n);
					}
				else
					{
					MoveCursor(((i+1)*10),5);
					printf("     ",aux_element.n);	
					}		
				}
			else if (dispo[i]==FALSE)
				{
				dispo[i]=TRUE;
				MoveCursor(((i+1)*10)-2,4);
				printf("      ");	
				}
			}
		
	if(client>=100)
		{
		MoveCursor(0,2);
		printf("CERRAREMOS LA TIENDA EN CUANTO LAS COLAS SE VACIEN ");
		j=0;
		for(i=0;i<num_cajeros;i++)
			if(Empty(&cola_cajeros[i])!=TRUE)
			{
			j++;
			break;
			}
		if(j==0)
			{
			MoveCursor(0,2);
			printf("LA TIENDA YA CERRO NO LLEGARAN MAS CLIENTES!      ");
			MoveCursor(0,20);
			system("PAUSE");
			free(cajeros);
			free(dispo);
			exit(0);
			}	
		}
	time_base++;
	}	
}

int Mcd(int num1,int num2) //UTILIZANDO EL ALGORITMO DE EUCLIDES HACEMOS EL CALCULO DEL MAXIMO COMUN DIVISOR DE DOS NUMEROS
{
int aux_num;
if(num1>num2)
	{
	aux_num=num1;
	num1=num2;
	num2=aux_num;
	}
return ExtMcd(num1,num2);
}

int ExtMcd(int num1,int num2)
{
if(num2%num1==0) return num1;
else return ExtMcd(num2%num1,num1);
}
