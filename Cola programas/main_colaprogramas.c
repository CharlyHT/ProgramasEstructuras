#include <stdio.h>
#include <stdlib.h>
#include "TADColaDin.h"
#include "presentacion.h"
#define DATOS 4
void Menu(cola *programas,cola *finalizados);
void Iniciar(void);
main()
{
	int i,aux,tam_cola;
	elemento el,el2,aux_el;
	cola programas,finalizados;
	Initialize(&finalizados);
	Initialize(&programas);	
	el2.time=0;el2.tistos=0;el2.tecucion=1;el2.name[0]='\0';el2.act[0]='\0';el2.id[0]='\0';
	Menu(&programas,&finalizados);	
	Iniciar();
	tam_cola=SizeCola(&programas);	
	while(TRUE)
	{
		
		if(Empty(&programas)!=TRUE)
		{
			el=Dequeue(&programas);
			el.tecucion++;
			if(el2.time!=0)
				for(i=0;i<DATOS;i++)	
			{
				MoverCursor(22,2+i);
				printf("                                                                                                              ");
				MoverCursor(22,2+i);
				i==0?printf("%s",el2.name):(i==1?printf("%s",el2.act):(i==2?printf("%s",el2.id):((el2.time-el2.tecucion)==0?printf("PROCESO FINALIZADO "):printf("TIEMPO FALTANTE DE EJECUCION: %d",el2.time-el2.tecucion))));
			}
			for(i=0;i<DATOS;i++)	
			{
				MoverCursor(22,8+i);
				printf("                                                                                                              ");
				MoverCursor(22,8+i);
				if(i==0)
					printf("%s",el.name);
				else if(i==1)
					printf("%s",el.act);
				else if(i==2)
					printf("%s",el.id);
				else 
					{
						if((el.time-el.tecucion)==0)
							printf("PROCESO FINALIZADO ");
						else
							printf("TIEMPO DE EJC. TOTAL: %d",el.tistos+el.tecucion);	
					}
			}
			if(Empty(&programas)!=TRUE)
				{
					aux_el=Front(&programas);
					for(i=0;i<DATOS;i++)	
					{
					MoverCursor(22,14+i);
					printf("                                                                                                              ");
					MoverCursor(22,14+i);
					i==0?printf("%s",aux_el.name):(i==1?printf("%s",aux_el.act):(i==2?printf("%s",aux_el.id):((aux_el.time-aux_el.tecucion)==0?printf("PROCESO FINALIZADO "):printf("TIEMPO FALTANTE DE EJECUCION: %d",aux_el.time-aux_el.tecucion))));
					}
				}
	
			if(el2.time!=0 && (Empty(&programas)==TRUE))
				for(i=0;i<DATOS;i++)	
			{
				MoverCursor(22,14+i);
				printf("                                                                                                              ");
				MoverCursor(22,14+i);
				i==0?printf("%s",el2.name):(i==1?printf("%s",el2.act):(i==2?printf("%s",el2.id):((el2.time-el2.tecucion)==0?printf("PROCESO FINALIZADO "):printf("TIEMPO FALTANTE DE EJECUCION: %d",el2.time-el2.tecucion))));
			}
			
			aux=SizeCola(&programas);
			if(Empty(&programas)!=TRUE)
					for(i=1;i<=aux;i++)
				{
					aux_el=Dequeue(&programas);
					aux_el.tistos++;
					Queue(&programas,aux_el);
				}
			}
		if(el.tecucion%el.time!=0)
			Queue(&programas,el);
		else
			Queue(&finalizados,el);	
		if(SizeCola(&finalizados)==tam_cola)
		{
			Destroy(&programas);
			Destroy(&finalizados);
			exit(0);	
		}
		el2=el;	
		EsperarMiliSeg(1000);
	}
	
	
}
void Menu(cola *programas,cola *finalizados)
{
	elemento el;
	int aux=0,i;
	puts("SIMULACION DE EJECUCION DE PROCESOS \"ESCOMIAMOS\"");
	puts("(1) INTRODUCIR UN PROCESO(NOTA:SEGUN EL ORDDEN COMO LOS METAS ES COMO EMPEZARA)\n(2) EMPEZAR SIMULACION\n(3) SALIR");
	fflush(stdin);
	scanf("%d",&aux);
	while(aux!=2)
	{
		if(aux==1)
			{
				for(i=0;i<DATOS;i++)
				{
					printf("INTRODUCE %s",i==0?"EL NOMBRE DEL PROCESO:\n":(i==1?"LA ACTIVIDAD QUE RALIZARA:\n":(i==2?"SU ID:\n":"EL TIEMPO DEL PROCESO:\n")));
					fflush(stdin);
					i==0?gets(el.name):(i==1?gets(el.act):(i==2?gets(el.id):scanf("%d",&el.time)));
				}
				el.tistos=0; el.tecucion=0;
				Queue(programas,el);
			}
		else if(aux==3)
		{
			puts("FUE UN GUSTO NO HABER SERVIDO PARA NADA");
			Destroy(programas);
			Destroy(finalizados);
			exit(0);
		}
	
		BorrarPantalla();
		puts("SIMULACION DE EJECUCION DE PROCESOS \"ESCOMIAMOS\"");
		puts("(1) INTRODUCIR UN PROCESO(NOTA:SEGUN EL ORDDEN COMO LOS METAS ES COMO EMPEZARA)\n(2) EMPEZAR SIMULACION\n(3) SALIR");
		aux=0;
		fflush(stdin);
		scanf("%d",&aux);
	}
}
void Iniciar(void)
{
	BorrarPantalla();
	puts("SIMULACION DE EJECUCION DE PROCESOS \"ESCOMIAMOS\" CORRIENDO...");
	MoverCursor(0,3);
	puts("PROCESO  >>ACTIVIDAD:\nANTERIOR >>       ID:");
	MoverCursor(0,9);
	puts("PROCESO  >>ACTIVIDAD:\nACTUAL   >>       ID:");
	MoverCursor(0,15);
	puts("PROCESO  >>ACTIVIDAD:\nSIGUIENTE>>       ID:");
	MoverCursor(12,2);
	puts("  NOMBRE:");
	MoverCursor(12,8);
	puts("  NOMBRE:");
	MoverCursor(12,14);
	puts("  NOMBRE:");
	MoverCursor(12,5);
	puts(" TIEMPO>>");
	MoverCursor(12,11);
	puts(" TIEMPO>>");
	MoverCursor(12,17);
	puts(" TIEMPO>>");
}
