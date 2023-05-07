//Declaracion de las librerias
 
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>
#include<string.h>

/*	La	definición	del	Tipo de	datos struct fecha.*/
struct fecha
{
	unsigned int dia, mes, anio;// El unsigned hace que la variable no acepte valores negativos
	
};

/*definición de	Tipo de	datos struct alumno*/
struct alumno
{
	unsigned int  Matricula;
	unsigned int  Promedio;   
		     char Nombre[40];
		     char Cve_Baja;
			 struct fecha fechaIngreso;
	
	
};

//Declaracion de las Funciones
int Altas(int i, struct alumno estudiantes[' ']);
int Bajas(int i, struct alumno estudiantes[' ']);
int Consultas(int i,struct alumno estudiantes[' ']);
int Listado_Completo(int i,struct alumno estudiantes[' ']);
int Listado_sin_Bajas(int i,struct alumno estudiantes[' ']);
int escribe_archivo(int i,struct alumno *estudiantes);
int leer_archivo(int i,struct alumno *estudiantes);
int archivo_txt(int i, struct alumno *estudiante, int argc,char* argv[]);
int archivo_txt_bajas(int i, struct alumno *estudiantes, int argc,char* argv[]);
int validar_numero(char numero[ ]);


//inicializacion del main()
int main(int argc,char* argv[])
{
	//Proceso para la obtecion de la fecha/Hora 
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    
    //Declaracion de Nuestras Variables locales 
    int op3=0,i=0;
	char Bandera='0',op;
	struct alumno estudiantes[' '];
	
	//Lectura del archivo Binario
	i=leer_archivo(i,estudiantes);
	
	//Ciclo principal 
	do
	 {
	 	
		 //Validacion de opcion 
		do
	 	 {
	 	  	system("cls");
		 	printf("\t\t\tMENU\n\t\t\t1.-Altas\n\t\t\t2.-Bajas\n\t\t\t3.-Consultas\n\t\t\t4.-Reportes\n\t\t\t5.-Salir\n\t\t\tOP> ");
		 	op=getche();
		 	if(op<'1' || op>'5')
				printf("ERROR. Ingrese un caracter valido ");
		 }while(op<'1' || op>'5');
		 	
		//switch principal	
	 	switch(op)
	  	 { 
	  		case '1': printf("\n\t\tALTA DE ESTUDIANTES ");
			  		 //Llamadas a funciones
					  i=Altas(i,estudiantes);
			  		  escribe_archivo(i,&estudiantes[0]);
	  	         	  break;
	  	         	  
	  		case '2': //Llamadas a funciones
			  		  Bajas(i,estudiantes);
	  		          escribe_archivo(i,&estudiantes[0]);
	  		          break;
	  		          
	    	case '3': //Llamadas a funciones
					  Consultas(i,estudiantes);
	  	         	  break;
	  	         	  
	  		case '4': do
	  		          {
							system("cls");
							do
							{
			  		  			printf("\n\t\t\tMENU DE IMPRESION\n\t\t\t1.-Listado Completo\n\t\t\t2.-Listado sin Bajas\n\t\t\t3.-Regresar al menu principal\n\t\t\tOP> ");
	  				  			scanf("%d",&op3);
	  				  		}while(op3<1 && op3>3);
	  				  		
	  				  		//switch secundario
	  				  		switch(op3)
	  				  		{
	  				  			case 1: system("cls");
										//i=leer_archivo(i,estudiantes);
	  				  	    	 	   	Listado_Completo(i,estudiantes);
	  				  	        		archivo_txt(i,estudiantes,argc,argv);
	  				  	        		//Para detener la ejecucion y visualizar la informacion
	  				  	        		system("pause");
							  			break;
							  
								case 2: system("cls");
										//i=leer_archivo(i,estudiantes);
								 	    Listado_sin_Bajas(i,estudiantes);
							    		archivo_txt_bajas(i,estudiantes,argc,argv);
							   			system("pause");
						      			break;
						      			
								case 3:
						    		    break;	
						    		    
						    //cierre del switch secundario 		    
					  		}
					  				
					 }while(op3!=3);
	             	 break;
	             	 
	    	case '5': printf("\n\n\t\tFIN DEL PROGRAMA ");
	  	           	  break;
	 	 
		 //cierre del switch secundario 
	     }
	 }while(op!='5');
	 
	printf("\n\n\n\n\n\n\n");
	strftime(output,128,"\n%d/%m/%y %H:%M:%S",tlocal);
    printf("%s\n",output);
    printf("\n");
	system("pause");
	return 0;
	
}//fin	main()


//Registro estudiantes por medio de funcion altas 
int Altas(int i, struct alumno estudiantes[' '])
{
 	int k;
	char opcion,band, op2,aux;
	char auxiliar[5];
	int N;
	int numerovalido;
	
	//Ciclo para validar la opcion de dar de alta otro alumno 
	do
	{
		system("cls");
		do
		{
			system("cls");
			
			estudiantes[i].Matricula=i+1;
			
	    	do
		 	{
		 		
	        	band='V';
				printf("\nNombre Completo: ");
				fflush(stdin);
				gets(estudiantes[i].Nombre);
				//Validacion Para solo ingreso de letras y espacios 
				for(k=0;k<strlen(estudiantes[i].Nombre);k++)//strlen para que recorra toda la cadena
					//Si no es letra te arroja un valor 0 de lo contrario te arroja un valor != 0
					if((isalpha(estudiantes[i].Nombre[k]))==0 && (isspace(estudiantes[i].Nombre[k]))==0)//isalpha acepte letras  isspace acepte espacios 
						band='F';
				if(band=='F')
					printf("\nIngresa s%clo letras\n",162);
		 	}while(band=='F');
	
			do
			{
				do
				{
    			printf("\nD%ca: ",161);
			 	scanf("%s",auxiliar);
			 	N=validar_numero(auxiliar);
			 	}while(N==0);
			 	estudiantes[i].fechaIngreso.dia=atoi(auxiliar);
			 	//Validacion de la variable dia(el valor se encuentre en un dia existente)
			 	if(estudiantes[i].fechaIngreso.dia<0 || estudiantes[i].fechaIngreso.dia>31)
					printf("\n\nD%ca no v%clido, ingrese un d%ca entre 1 y 31\n",161,160,161);
			}while(estudiantes[i].fechaIngreso.dia<0 || estudiantes[i].fechaIngreso.dia>31);
							
			do
			{
				printf("\nMes: ");
			 	scanf("%d",&estudiantes[i].fechaIngreso.mes);
			 	//VAlidacion de la variable mes(el valor se encuentre en un mes existente)
			 	if(estudiantes[i].fechaIngreso.mes<0 || estudiantes[i].fechaIngreso.mes>12)
					printf("\n\nMes no v%clido, ingrese un mes entre 1 y 12\n",160);
			}while(estudiantes[i].fechaIngreso.mes<0 || estudiantes[i].fechaIngreso.mes>12);	
							
			do
			{
		   	 	printf("\nA%co: ",164);
			 	scanf("%d",&estudiantes[i].fechaIngreso.anio);
			 	//Validacion de la variable anio(el valor se encuentre en un anio existente)
			 	if(estudiantes[i].fechaIngreso.anio<2000 || estudiantes[i].fechaIngreso.anio>2021)
					printf("\n\nA%co no v%clido, ingrese un a%co a partir de 2000\n",164,160,164);
			}while(estudiantes[i].fechaIngreso.anio<2000 || estudiantes[i].fechaIngreso.anio>2021 );
							
			do
			{
			 	printf("\nPromedio: ");
			 	scanf("%d",&estudiantes[i].Promedio);
			 	//Validacion de la variable promedio(se encuentre en un valor existente)
			 	if(estudiantes[i].Promedio<0 || estudiantes[i].Promedio>100)
			 		printf("\n\nPromedio no v%clido.Ingrese nuevamente un promedio entre 0 y 100\n",160);
			}while(estudiantes[i].Promedio<0 || estudiantes[i].Promedio>100);
	
			estudiantes[i].Cve_Baja='A';
			
			do
			{
			 	printf("\n%cLa informaci%cn es correcta? S/N: ",168,162);
			 	fflush(stdin);//Limpieza de buffer
			 	aux=getche();
			 	aux=toupper(aux);
			 	if(aux!='S' && aux!='N')
			 		printf("\n\nDato erroneo");
			}while(aux!='S' && aux!='N');
		
		}while(aux!='S');
		
		i++;
		do
		{
			printf("\n\n\n%cDesea dar de alta otro registro? S/N",168);
			fflush(stdin);
			op2=getche();
			op2=toupper(op2);
			if(op2!='S' && op2!='N')
				printf("\n\nDato erroneo");
	    }while(op2!='S' && op2!='N');
		
	
    }while(op2!='N');
	
    return i;
		
		
}
  
int Bajas(int i,struct alumno estudiantes[' '])
{
	int j, Mat, aux=0,k=0;
	char op, op2, BAND='F';
	
	do
	{
		system("cls");
		printf("\n\t\tIngrese la matr%ccula que desea borrar ",161);
		scanf("%d",&Mat);
	
		for(j=0; j<i; j++)
		{
			if(Mat==estudiantes[j].Matricula)//Comparacion de la matricula ingresada con las del arreglo 
			{
				BAND ='V';
				if(estudiantes[j].Cve_Baja=='A')//Verificar si el alumno aun este dado de alta en el sistema 
				{
					system("cls");	
					printf("\n\t\t\tLa Matr%ccula Fue encontada: ",161);
					printf("\n\n\n\n\t\t\tMatr%ccula : %d",161,estudiantes[j].Matricula);
					printf("\n\t\t\tNombre : %s",estudiantes[j].Nombre);
					printf("\n\t\t\tD%ca : %d",161,estudiantes[j].fechaIngreso.dia);
					printf("\n\t\t\tMes : %d",estudiantes[j].fechaIngreso.mes);
					printf("\n\t\t\tA%co : %d",164,estudiantes[j].fechaIngreso.anio);
					printf("\n\t\t\tPromedio : %d",estudiantes[j].Promedio);
					printf("\n\t\t\tCve_Baja : %c",estudiantes[j].Cve_Baja);
					
					do
					{
						printf("\n\n\n\t\t%cDesea dar baja el alumno S/N: ",168);
						fflush(stdin);
						op=getche();
						op=toupper(op);
						if(op!='S' && op!='N')
							printf("\nDato erroneo");
	        		}while(op!='S' && op!='N');
	       		
					k=j;
            		j=i+1;//para terminar el ciclo 
            	}    
			}
    	}
    	
        if(BAND=='V')
		{
			printf("\n\n\t\tEsta matr%ccula ya est%c dada de baja",161,160);
		}
		
		if(BAND=='F')
		{
			printf("\nMatr%ccula erronea",161);
		}
		
		if(op=='S')
	   	{
	    	system("cls");
	    	printf("\n\n\t\tEl registro fue dado de baja con %cxito: ",130);
	      	estudiantes[k].Cve_Baja='B';//Dar de baja al alumno(Cambiando el valor del campo cve_baja a 'B')
		}
		
    	do
		{
			printf("\n\n\n\n\n\n\n\n\n%cDesea dar de baja otro alumno? S/N: ",168);
			fflush(stdin);
			op2=getche();
			op2=toupper(op2);
			if(op2!='S' && op2!='N')
			printf("\nDato erroneo");
		}while(op2!='S' && op2!='N');
		
	
	}while(op2!='N');
    return 0;
		
}


int Consultas(int i,struct alumno estudiantes[' '])
{
	int j, Mat, aux, k=-1,m=-1;
	char op2;
	
	do
	{
		
			system("cls");
			k=-1;
			printf("\n\t\tIngrese la matr%ccula que desea Consultar ",161);
			scanf("%d",&Mat);

			for(j=0; j<i; j++)
			{	
				if(Mat==estudiantes[j].Matricula)
				{
		    		k=j;
					m=-1;
					if(estudiantes[j].Cve_Baja=='A')
					{
						printf("\n\t\t\tLa Matr%ccula Fue encontada: ",161);
						printf("\n\t\t\tMatr%ccula : %d",161,estudiantes[j].Matricula);
						printf("\n\t\t\tNombre : %s",estudiantes[j].Nombre);
						printf("\n\t\t\tD%ca : %d",161,estudiantes[j].fechaIngreso.dia);
						printf("\n\t\t\tMes : %d",estudiantes[j].fechaIngreso.mes);
						printf("\n\t\t\tA%co : %d",164,estudiantes[j].fechaIngreso.anio);
						printf("\n\t\t\tPromedio : %d",estudiantes[j].Promedio);
						printf("\n\t\t\tCve_Baja : %c",estudiantes[j].Cve_Baja);
            			j=i+1;
            			m=j;
            		}
        		}
    		}
    		
    		if(m==-1)
    		{
      			printf("\n\t\tRegistro dado de baja");
			}  
    
    	if(k==-1)
		{
			printf("\n\t\tMatr%ccula erronea",161);
		}
     
		do
		{
			printf("\n\n\n\n\n\n\n\n\n%cDesea consultar otro alumno? S/N: ",168);
			fflush(stdin);
			op2=getche();
			op2=toupper(op2);
			if(op2!='S' && op2!='N')
				printf("\nDato erroneo");
		}while(op2!='S' && op2!='N');
		
	
	}while(op2!='N');
    
    return 0;
		
}


 /*Funcion que escribe en el archivo binario .data*/
int escribe_archivo(int i,struct alumno *estudiantes)
{
 
	/*Guardado de la informacion de la estructura estudiante en un archivo 
    Crear puntero tipo FILE para conectar con el archivo.*/ 
    FILE *ap;

       
	/*Apertura de archivo con validacion para detectar posibles errores de apertura. 
	Modo de apertura (w+)para crear  el archivo y seguir  añadiendo  mas registros*/
    
    if((ap = fopen("Estudiantes.dat","w+"))== NULL)
    {
        puts("\nError al abrir archivo");
        return -1;
    }

    /* escribir informacion en el archivo. Se escribe el arreglo estudiantes 
	completo. Pruebe escribiendo 1 struct cada vez*/ 
    
    int n;
	for(n=0;n<i;n++)
    	fwrite(&estudiantes[n], sizeof(estudiantes[n]), 1, ap);

    fclose(ap);
    /* cierre de archivo */
  	return 0;
}
 


/*Funcion que lee el archivo binario .data */
int leer_archivo(int i,struct alumno *estudiantes)
{
	FILE *ap;
	int n=0;
	if((ap = fopen("Estudiantes.dat","r"))== NULL)
    {
        puts("\nError al abrir archivo");
        return -1;
    }
    /*Ciclo que dice que mientras no sea difrente del fianl del archivo se ejecute...*/
    while(!feof (ap))
    {
    	fread(&estudiantes[n], sizeof(estudiantes[n]), 1, ap);
    	n++;
	}
	fclose(ap);
	return n-1;
} 




int Listado_Completo(int i,struct alumno estudiantes[' '])
{
	int j;
	printf("\n\t\t\t\tLISTADO DE ESTUDIANTES\n");
	printf("Matricula\tNombre\t\t\t\tFecha de Ingreso\tPromedio\t\tClave de Baja\n");
	
	for(j=0; j<i; j++)
	{
			printf("%-16d%-39s %2d/%2d/%2d%19d%20c\n\n",estudiantes[j].Matricula,
														estudiantes[j].Nombre,
														estudiantes[j].fechaIngreso.dia,
														estudiantes[j].fechaIngreso.mes,
														estudiantes[j].fechaIngreso.anio,
														estudiantes[j].Promedio,
														estudiantes[j].Cve_Baja);
	}
	
	
}


int Listado_sin_Bajas(int i,struct alumno estudiantes[' '])
{
	int j;
	
	printf("\n\t\t\t\t\t\t\tLISTADO DE ESTUDIANTES ACTIVOS\n");
	printf("Matricula\tNombre\t\t\t\t\tFecha de Ingreso\tPromedio\t\tClave de Baja\n");
	
	for(j=0; j<i; j++)
	{
		if(estudiantes[j].Cve_Baja=='A')
		{
			printf("%-16d%-39s %2d/%2d/%2d%19d%20c\n\n",estudiantes[j].Matricula,
														estudiantes[j].Nombre,
														estudiantes[j].fechaIngreso.dia,
														estudiantes[j].fechaIngreso.mes,
														estudiantes[j].fechaIngreso.anio,
														estudiantes[j].Promedio,
														estudiantes[j].Cve_Baja);
			
		}
	}
}



/*Funcion que genera el archivo de texto .txt*/
int archivo_txt(int i, struct alumno *estudiantes, int argc,char* argv[])
{
	
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    
    
	int j;
	FILE *ap;
	
	/*Creacion del archivo de texto*/
	
	if((ap = fopen("Listado Completo.txt","wt"))== NULL)
    {
        puts("\nError al abrir archivo");
        return -1;
    }
        
        /* Escribir la informacion en el archivo texto reporte.txt con formato reporte*/
        
    fprintf(ap,"\n\t\t\t\t\t\t\tLISTADO DE ESTUDIANTES COMPLETO\n");
	fprintf(ap,"\nMatricula\tNombre\t\t\t\t\tFecha de Ingreso\tPromedio\t\tClave de Baja\n\n");
    for( j= 0; j<i ; j++)
    {
    	fprintf(ap,"%-16d%-39s %2d/%2d/%2d%19d%20c\n\n",estudiantes[j].Matricula,
														estudiantes[j].Nombre,
														estudiantes[j].fechaIngreso.dia,
														estudiantes[j].fechaIngreso.mes,
														estudiantes[j].fechaIngreso.anio,
														estudiantes[j].Promedio,
														estudiantes[j].Cve_Baja);
    }
    fprintf(ap,"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	fprintf(ap,"  Fecha:   Hora:\n");
	fprintf(ap,"%s",output);	

    /* cierre del archivo*/
    fclose(ap);
}



/*Funcion que genera el archivo de texto .txt*/
int archivo_txt_bajas(int i, struct alumno *estudiantes, int argc,char* argv[])
{
	
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    
	int j;
	FILE *ap;
	
	/*Creacion del archivo de texto*/
	
	if((ap = fopen("Listado sin Bajas.txt","wt"))== NULL)
    {
        puts("\nError al abrir archivo");
        return -1;
    }
        
        /* Escribir la informacion en el archivo texto reporte.txt con formato reporte*/
        
    fprintf(ap,"\n\t\t\t\t\t\t\tLISTADO DE ESTUDIANTES SIN BAJAS\n");
	fprintf(ap,"\nMatricula\tNombre\t\t\t\t\tFecha de Ingreso\tPromedio\t\tClave de Baja\n");
    for( j= 0; j<i ; j++)
    {
    	if(estudiantes[j].Cve_Baja=='A')
    	{
    		fprintf(ap,"%-16d%-39s %2d/%2d/%2d%19d%20c\n\n",estudiantes[j].Matricula,
														    estudiantes[j].Nombre,
														    estudiantes[j].fechaIngreso.dia,
														    estudiantes[j].fechaIngreso.mes,
														    estudiantes[j].fechaIngreso.anio,
														    estudiantes[j].Promedio,
	     												    estudiantes[j].Cve_Baja);
	    }
														
	}
	fprintf(ap,"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	fprintf(ap,"  Fecha:   Hora:\n");
    fprintf(ap,"%s",output);
    
    /* cierre del archivo*/
    fclose(ap);
}


int validar_numero(char numero[ ])
{
	int k;
	for(k=0; k<strlen(numero); k++)
	{
		if(!(isdigit(numero[k])))
		{
			printf("\n\nIngresa s%clo n%cmeros\n\n",162,163);
			return 0;
		}
	}
	return 1;
}





