#include "basicas.cpp"

#define MAXsexo 2
#define MAXtipoEnf 5

struct Paciente
{
	char nombre[LIM];
   int edad;
   int sexo;
   int tipoEnf;
   float costo;
   int anio;
};

struct NodoPaciente
{
	Paciente P;
   NodoPaciente *sgte;
};

struct ListaPaciente
{
	NodoPaciente *cab;
   int N;
};

char Tsexo[MAXsexo][LIM]={"Masculino","Femenino"};
char TtipoEnf[MAXtipoEnf][LIM]={"S. Cardiaco","S. Nervioso","S. Urinario","S. Endocrino","S. Gastrointestinal"};

//operaciones basicas de paciente
void iniciaPaciente(Paciente &P)
{
	P.nombre[0]=NULL;
   P.edad=0;
   P.sexo=0;
   P.tipoEnf=0;
   P.costo=0.0;
   P.anio=0;
}

void leePaciente(Paciente &P)
{
	printf("\nIngrese nombre del paciente: ");
   fflush(stdin);
   gets(P.nombre);
   P.edad=leeEntero("\nIngrese edad[1-150]: ",1,150);
   P.sexo=validaTabla("\nIngrese sexo: ",Tsexo,MAXsexo);
   P.tipoEnf=validaTabla("\nIngrese tipo de enfermedad: ",TtipoEnf,MAXtipoEnf);
   P.costo=leeReal("\nIngrese costo[20-20,000]: ",20.0,20000.0);
   P.anio=leeEntero("\nIngrese anio de atencion[1900-2018]: ",1900,2018);
}

void mostrarPaciente(Paciente &P)
{
	printf("\nNombre: %s",P.nombre);
   printf("\nEdad: %d",P.edad);
   printf("\nSexo: %s",Tsexo[P.sexo-1]);
   printf("\nTipo de enfermedad: %s",TtipoEnf[P.tipoEnf-1]);
   printf("\nCosto de la atencion: %.2f",P.costo);
   printf("\nAnio de atencion: %d",P.anio);
}

//operaciones basicas de Lista Pacientes

void iniciaListaPacientes(ListaPaciente &LP)
{
	LP.cab=NULL;
   LP.N=0;
}

void inserta(ListaPaciente &LP,Paciente &P,NodoPaciente *&Aux)
{
	NodoPaciente *Dato;

   Dato=new NodoPaciente;
   printf("estoy insertando");

   Dato->P=P;
   if(Aux==NULL)
   {
   	printf("estoy if1");
   	Dato->sgte=LP.cab;
   	printf("estoy if2");
      LP.cab=Dato;
      
   }
   else
   {
   	printf("estoy else");
   	Dato->sgte=Aux->sgte;
      Aux->sgte=Dato;
      
   }
   LP.N++;
   Aux=Dato;
}

void leeListaPacientes(ListaPaciente &LP)
{
	Paciente P;

   NodoPaciente *Aux=LP.cab;

   do{
   	iniciaPaciente(P);
      leePaciente(P);
      printf("lo leo");
      inserta(LP,P,Aux);
      printf("lo inserto");
   }while(!(continuar("\nDesea continuar(S/N): ")=='N'));
}

void mostrarListaPacientes(ListaPaciente &LP)
{
   int i=1;
	NodoPaciente *Aux=LP.cab;

	if(LP.N>0)
   {
   	while(Aux!=NULL)
      {
         printf("\nPaciente Nro[%d]",i);
      	mostrarPaciente(Aux->P);
         Aux=Aux->sgte;
         i++;
      }
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

void liberar(ListaPaciente &LP)
{
	NodoPaciente *Aux=LP.cab;

   while(Aux!=NULL)
   {
   	LP.cab=Aux->sgte;
      delete Aux;
      Aux=LP.cab;
   }
}

//reportes
void reporte01(ListaPaciente &LP)
{
   int flag=0;
   char nombreaux[LIM];

   NodoPaciente *Aux=LP.cab;
   nombreaux[0]=NULL;

	printf("\nIngrese nombre del paciente: ");
   fflush(stdin);
   gets(nombreaux);

	if(LP.N>0)
   {
   	while(Aux!=NULL)
      {
      	if(strcmpi(Aux->P.nombre,nombreaux)==0)
         {
         	printf("\nTipo de enfermedad: %s",TtipoEnf[Aux->P.tipoEnf-1]);
            printf("\nAnio de atencion: %d",Aux->P.anio);
   			printf("\nCosto de la atencion: %.2f",Aux->P.costo);
            flag=1;
         }
         Aux=Aux->sgte;
      }
      if(flag==0)
      	printf("\nNo hay pacientes con este nombre.");
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

void reporte02(ListaPaciente &LP)
{
	int flag=0;
   float mayor=0.0;

   NodoPaciente *Aux = LP.cab;

	if(LP.N>0)
	{
   	while(Aux != NULL)
      {
      	if(Aux->P.anio==2018)
         {
         	if(Aux->P.costo>mayor)
            	mayor=Aux->P.costo;
            flag=1;
         }
         Aux=Aux->sgte;
      }
      if(flag==1)
      {
      	Aux=LP.cab;

         printf("\nEl mayor costo es: %.2f",mayor);
         while(Aux!=NULL)
         {
         	if(Aux->P.costo==mayor && Aux->P.anio==2018)
            {
            	printf("\n- Datos -");
            	printf("\nNombre: %s",Aux->P.nombre);
               printf("\nEdad: %d",Aux->P.edad);
            }
            Aux=Aux->sgte;
         }
      }
      else
      	printf("\nNo hay pacientes en el anio 2018");
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

//d)Mostrar el numero de atenciones por tipo de enfermedad.
void reporte03(ListaPaciente &LP)
{
 	int cont[MAXtipoEnf];
 	iniciaVE(cont,MAXtipoEnf);

   NodoPaciente *Aux=LP.cab;

 	if(LP.N>0)
 	{
  		while(Aux!=NULL)
  		{
   		cont[Aux->P.tipoEnf-1]++;
         Aux=Aux->sgte;
  		}
  		for(int i=0;i<MAXtipoEnf;i++)
      {
      	printf("\nPacientes atendidos(%s): %d",TtipoEnf[i],cont[i]);
      }
 	}
 	else
 		printf("\nNo Hay Datos...");
 	getch();
}

//e)Mostrar el porcentaje de hombres y mujeres atendidas.
void reporte04(ListaPaciente &LP)
{
 	int cont[MAXsexo];
 	float porcentaje[MAXsexo];
 	iniciaVE(cont,MAXsexo);
 	iniciaVR(porcentaje,MAXsexo);

   NodoPaciente *Aux=LP.cab;

 	if(LP.N>0)
 	{
  		while(Aux!=NULL)
  		{
   		cont[Aux->P.sexo-1]++;
         Aux=Aux->sgte;
  		}
  		for(int i=0;i<MAXsexo;i++)
      {
      	if(cont[i]>0)
      		porcentaje[i]=(float)cont[i]*100/LP.N;
      }
  		for(int i=0;i<MAXsexo;i++)
      {
      	printf("\nPorcentaje(%s): %.2f",Tsexo[i],porcentaje[i]);
  		}
 	}
 	else
 		printf("\nNo Hay Datos...");
 	getch();
}

/*f)Dado el tipo de enfermedad,mostrar el promedio de costo y de edad
   de los pacientes.*/
void reporte05(ListaPaciente &LP)
{
 	int tipo,flag=0,cont=0,sumaedad=0;
 	float sumacosto=0.00;

   NodoPaciente *Aux=LP.cab;

 	if(LP.N>0)
 	{
  		tipo=validaTabla("\nIngrese Tipo de Enfermedad: ",TtipoEnf,MAXtipoEnf);

  		while(Aux!=NULL)
  		{
   		if(Aux->P.tipoEnf==tipo)
   		{
    			sumacosto+=Aux->P.costo;
    			sumaedad+=Aux->P.edad;
            cont++;
            flag=1;
      	}
         Aux=Aux->sgte;
  		}
  		if(flag==0)
  			printf("\nNo Hay Paciente con ese tipo de enfermedad.");
      else
  		{
  			printf("\nPromedio de costo: %.2f",sumacosto/cont);
   		printf("\nPromedio de edad: %.2f",(float)sumaedad/cont);
  		}
 }
 else
 	printf("\nNo Hay Datos...");
 getch();
}

//g) mostrar las atenciones cuyo costo es mayor a un valo ingresado
void reporte06(ListaPaciente &LP)
{
   int flag=0;
   float valor;

	NodoPaciente *Aux=LP.cab;

   if(LP.N>0)
   {
      valor=leeReal("\nIngrese costo: ",20.0,20000.0);

   	while(Aux!=NULL)
      {
      	if(Aux->P.costo>valor)
         {
   		   printf("\nNombre del paciente: %s",Aux->P.nombre);
            printf("\nEdad: %d",Aux->P.edad);
            printf("\nCosto: %.2f",Aux->P.costo);
         	flag=1;
         }
         Aux=Aux->sgte;
      }
      if(flag==0)
      	printf("\nNo hay atencion cuyo costo es mayor al valor ingresado.");
   }
   else
   	printf("\nNo hay datos");
   getch();
}
//h) mostrar ordenado descentendemente por anio de atencion
void reporte07(ListaPaciente &LP)
{
	Paciente P;

	NodoPaciente *Aux=LP.cab;
   NodoPaciente *Aux1;

   while(Aux->sgte!=NULL)
   {
      Aux1=Aux->sgte;
      while(Aux1!=NULL)
      {
      	if(Aux->P.anio < Aux1->P.anio)
         {
         	P=Aux->P;
            Aux->P=Aux1->P;
            Aux1->P=P;		
         }
         Aux1=Aux1->sgte;
      }
   	Aux=Aux->sgte;
   }
   printf("\nLista ordenada por anio(mayor a menor):");
   mostrarListaPacientes(LP);
   getch();
}

//Menu
void menu(ListaPaciente &LP)
{
 int op;
 do
 {
  //clrscr();
  printf("\n\n\n*** Clinica San Juan de Dios ****");
  printf("\n----------------------------------");
  printf("\n1.Registrar un Paciente ");
  printf("\n2.Mostrar ");
  printf("\n3.Dado el Paciente,mostrar sus atenciones en la clinica ");
  printf("\n4.Paciente con mayor costo de atencion en el 2018 ");
  printf("\n5.Mostrar el numero de atenciones por tipo de Enfermedad ");
  printf("\n6.Mostrar el porcentaje de hombres y mujeres atendidas ");
  printf("\n7.Dado el tipo de enfermedad,mostrar promedio de costo y edad de los pacientes");
  printf("\n8.Salir ");
  printf("\n");
  op=leeEntero("\nIngrese opcion: ",1,8);
  switch(op)
  {
   case 1: leeListaPacientes(LP);
   		  break;
   case 2: mostrarListaPacientes(LP);
   		  break;
   case 3: reporte01(LP);
   		  break;
   case 4: reporte02(LP);
   		  break;
   case 5: reporte03(LP);
   		  break;
   case 6: reporte04(LP);
   		  break;
   case 7: reporte05(LP);
   		  break;
   case 8: liberar(LP);
   		  break;
  }
 }while(op!=8);
}

int main()
{
 ListaPaciente LP;

 iniciaListaPacientes(LP);
 menu(LP);
 return 1;
}

