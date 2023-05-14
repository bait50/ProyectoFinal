#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

struct corredor
{
	char nombre[30];
	int num,num_vueltas = 0;
	float promedio;
	float tiempo = 0;
	corredor *siguiente;
};
corredor *primero, *aux, *lifo, *fifo; //= NULL;
int num_corredores;

struct promedio
{
	corredor corredor;
	promedio *irq;
	promedio *der;
};

promedio *arbol = NULL;

void insertarNodo(promedio *&arbol, corredor aux_)
{
	
	if(arbol == NULL)
	{
		promedio *yoquese = new promedio();
		
		yoquese->corredor = aux_;
		yoquese->irq = NULL;
		yoquese->der = NULL; 
		arbol = yoquese;
		
	}
	else
	{
		
		if(aux_.promedio < arbol->corredor.promedio)
		{
			insertarNodo(arbol->irq, aux_);
					
		}
		else if(aux_.promedio > arbol->corredor.promedio)
		{
			insertarNodo(arbol->der, aux_);
		}	
		
	}
	
}


void mostrar_promedio(promedio *arbol_) 
{

	if(arbol_->irq != NULL)
	{
		mostrar_promedio(arbol_->irq);
	}
	cout<<"nombre: "<<arbol_->corredor.nombre<<endl<<"promedio: "<<arbol_->corredor.promedio<<endl;
	if(arbol_->der != NULL)
	{
		mostrar_promedio(arbol_->der);
	}
	
}


void ingresar_corredor()
{
	system("cls");
	corredor *aux = new corredor();
	cout<<"ingrese el nombre del corredor: "; cin>>aux->nombre;
	cout<<endl<<"ingrese el documento del corredor: "; cin>>aux->num;
	aux->siguiente = NULL;
	
	if(primero==NULL)
	{
		primero=aux;
	}
	else
	{
		corredor *aux2 = primero;
		while(aux2->siguiente!=NULL) aux2 = aux2->siguiente;
		
		aux2->siguiente=aux;
		aux2=NULL;
		aux=NULL;
	}
	
	num_corredores++;
}

void hacer_prueba()
{
	system("cls");
	int n;
	
	
	for(corredor *aux = primero; aux!=NULL; aux=aux->siguiente)
	{
		cout<<"nombre: "<<aux->nombre;
		cout<<endl<<"documento: "<<aux->num;
		cout<<'\n';
	}
	
	cout<<endl<<endl<<"ingrese el numero del corredor: ";
	cin>>n;
	
	aux = primero;
	bool encontrado = false;
	for(primero; primero!=NULL; primero=primero->siguiente)
	{
		if(n==primero->num)
		{
			int v;
			float aux_prom = 0;
			float tiempo, menorTiempo = 0;
			cout<<endl<<"cuantas vueltas hara el corredor: ";
			cin>>v;
			primero->num_vueltas+=v;
			for(int i =0;i<v;i++){
				
				tiempo = 1+rand() % 100;
				aux_prom += tiempo;	
				cout<<endl<<"tiempo de la vuelta "<<i+1<<": "<<tiempo;
				if(i == 0) menorTiempo = tiempo;	
				if(tiempo < menorTiempo) menorTiempo = tiempo;
			}
			primero->tiempo = menorTiempo;
			aux_prom=aux_prom/v;
			primero->promedio = aux_prom;
			
			insertarNodo(arbol, *primero);
			
			encontrado = true;
			cout<<endl;
			system("pause");
		}
	}
	primero=aux;
	aux=NULL;
	free(aux);
	if(!encontrado) 
	{
		cout<<endl<<"no se encontro el corredor"<<endl;
		system("pause");
	}
}

void mostrar_corredores()
{
	system("cls");
	cout<<"NUMERO DE CORREDORES: "<<num_corredores<<'\n';
	for(corredor *aux = primero; aux!=NULL; aux=aux->siguiente)
	{
		cout<<"nombre: "<<aux->nombre;
		cout<<endl<<"corredor: "<<aux->num;
		cout<<endl<<"numero de vueltas: "<<aux->num_vueltas;
		cout<<endl<<"promedio: "<<aux->promedio;
		cout<<endl<<"menor tiempo: "<<aux->tiempo;
		cout<<endl<<endl;
	}
	system("pause");
}



int main()
{
	
	int op;
	do
	{
		system("cls");
		cout<<"1. ingresar corredor"<<endl<<"2. mostrar corredores"<<endl<<"3. hacer vuelta"<<endl;
		cout<<"4. mostrar promedios"<<endl<<"5. mostrar tiempos"<<endl<<"6. salir"<<endl<<"--> ";
		cin>>op;
		
		switch(op)
		{
			case 1:
				ingresar_corredor();
				break;
			
			case 2:
				mostrar_corredores();
				break;
			
			case 3:
				hacer_prueba();
				break;
			case 4:
				system("cls");
				mostrar_promedio(arbol);
				system("pause");
				break;
			case 5:
				//mostrar_tiempos();
				break;
			default:
				system("cls");
				cout<<endl<<endl<<"la opcion no existe"<<endl<<endl;	
				system("pause");
			break;
		}
		
	}while(op!=6);
} 