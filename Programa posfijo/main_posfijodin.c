#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TADPilaDin.h"
//#include "TADPilaEst.h"
#define MAX_CADENA 100
void Parentesis(string expresion);
void Posfijo(string expresion);
void EvaluarPos(string expresion);
int jerarquia(char operador);
main()
{
	char expresion[MAX_CADENA];
	printf(" INFIJO ======> POSFIJO\nINTRODUZCA LA CADENA A TRANSFORMAR\nNOTA: DENTRO DE LA EXPRESION SOLO PUEDES USAR LETRA MAYUSCULAS\n ");
	scanf("%s",expresion);
	Parentesis(expresion);
	Posfijo(expresion);
	system("PAUSE");
	
	
}
void Parentesis(string expresion) //COMPROBACION DE LOS PARENTESIS
{
	int i,tam_cad;
	tam_cad=strlen(expresion);
	pila pila1;
	Initialize(&pila1);
	elemento caracter;
	for(i=0;i<tam_cad;i++)
		{
			if(expresion[i]=='(')
				{
					caracter.carac='(';
					Push(&pila1,caracter);
				}
			else if(expresion[i]==')')
				{
					if(Empty(&pila1))
						{
							printf("ERROR: Existen mas parentesis que cierran de los que abren o no hay un parentesis que abra antes del que cierra");
							exit(1); 
						}
					caracter=Pop(&pila1);
				}
				
		}
	if(!Empty(&pila1))
		{
			printf("ERROR: Existen mas parentesis que abren de los que cierran");
			exit(1); 
		}
	printf("EXCELENTE: Expresion correcta\n");
	Destroy(&pila1);	
	return;
}

void Posfijo(string expresion)
{
	int tam_cad,i,j=0,aux_pila,aux_exp;
	elemento el;
	pila pila1;
	Initialize(&pila1);
	tam_cad=strlen(expresion);
	char posfija[tam_cad];
	
	for(i=0;i<tam_cad;i++)
	{
		if(expresion[i]>64 && (expresion[i]<91))
		{
			posfija[j]=expresion[i];
			j++;
		}
		else if(expresion[i]=='(')// SI ES '(' ENTRA DIRECTO
		{
				el.carac=expresion[i];
				Push(&pila1,el);
		}
		else if (Empty(&pila1))
		{
			el.carac=expresion[i];
			Push(&pila1,el);
		}
		else if (!Empty(&pila1))
		{
			aux_exp=jerarquia(expresion[i]);
			aux_pila=jerarquia((Top(&pila1)).carac);
			if(aux_pila==aux_exp)
			{
				el=Pop(&pila1);
				posfija[j]=el.carac;
				j++;
				el.carac=expresion[i];
				Push(&pila1,el);
			}
			else if (aux_pila<aux_exp && (aux_exp!=5))
			{
				el.carac=expresion[i];
				Push(&pila1,el);
			}
			else if(aux_pila>aux_exp)
			{
				while(aux_pila>aux_exp)
				{
					el=Pop(&pila1);
					posfija[j]=el.carac;
					j++;
					if(Empty(&pila1)!=TRUE) aux_pila=jerarquia((Top(&pila1)).carac);
					else break;	
				}
				el.carac=expresion[i];
				Push(&pila1,el);
			}
			else if(aux_exp==5)
			{
				el=Pop(&pila1);
				while(el.carac!='(')
				{
					posfija[j]=el.carac;
					el=Pop(&pila1);
					j++;	
				}
			}
		}
	}
	while(!Empty(&pila1))
	{
		el=Pop(&pila1);
		posfija[j]=el.carac;
		j++;
	}
	posfija[j]=0; //AGREGAMOS EL NULO A LA CADENA
	Destroy(&pila1);
	printf("%s\n",posfija);
	EvaluarPos(posfija);
	return;
}
void EvaluarPos(string expresion)
{
	int tam_cad,i;
	pila pila1;
	elemento el,el2;
	Initialize(&pila1);
	tam_cad=strlen(expresion);
	double abc[27];
	for(i=0;i<27;i++)	abc[i]=0; //DECLARAR ARREGLO EN 0
	printf("EVALUACION INTRODUZCA LOS VALORES DE LAS LETRAS\nNOTA: NO PUEDE IGUALAR UNA LETRA CON 0\n");
	for(i=0;i<tam_cad;i++)
	{
		if(expresion[i]>64 && (expresion[i]<91))
		{
			if(abc[expresion[i]-65] == 0)
			{
				printf("INTRODUCE EL VALOR DE %c\n",expresion[i]);
				scanf("%lf",&abc[expresion[i]-65]);
			}
		}
	}	
	for(i=0;i<tam_cad;i++)
	{
		if(expresion[i]>64 && (expresion[i]<91))
		{
			el.variable=abc[expresion[i]-65];
			Push(&pila1,el);
		}
		else
		{
			if(expresion[i]=='+')
			{
				el=Pop(&pila1);
				el2=Pop(&pila1);
				el2.variable+=el.variable;
				Push(&pila1,el2);
			}
			else if(expresion[i]=='-')
			{
				el=Pop(&pila1);
				el2=Pop(&pila1);
				el2.variable-=el.variable;
				Push(&pila1,el2);
			}
			else if(expresion[i]=='*')
			{
				el=Pop(&pila1);
				el2=Pop(&pila1);
				el2.variable*=el.variable;
				Push(&pila1,el2);
			}
			if(expresion[i]=='/')
			{
				el=Pop(&pila1);
				el2=Pop(&pila1);
				el2.variable/=el.variable;
				Push(&pila1,el2);
			}
			if(expresion[i]=='^')
			{
				el=Pop(&pila1);
				el2=Pop(&pila1);
				el2.variable=pow(el2.variable,el.variable);
				Push(&pila1,el2);
			}
		}
	
	}
	el=Pop(&pila1);
	printf("EL VALOR DE LA EVALUACION ES :  %.4lf.\n",el.variable);
	Destroy(&pila1);
	return;
} 
int jerarquia(char operador) //CHECA LA JERARQUIA DE LOS OPERADORES
{
	int valor;
	switch(operador)
	{
		case ')':
			valor=5;
			break;
		case '^':
			valor=4;
			break;
		case '*':
			valor=3;
			break;
		case '/':
			valor=3;
			break;
		case '+':
			valor=2;
			break;
		case '-':
			valor=2;
			break;
		case '(':
			valor=1;
			break;	
	}
	return valor;
}
