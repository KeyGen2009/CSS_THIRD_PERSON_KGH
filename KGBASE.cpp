/*
			KeyGen2009 thirdperson tutorial
			Dios los bendiga es un regalo mio para ustedes!
																	*/
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <conio.h>

using namespace std;

//Variables del programa
DWORD pid;
HANDLE hp;

//Headers 
#include "KGModulos.h"

//Modulos del juego
ModuloInfo client;

//3D Person hack
uintptr_t ACTIVADOR = 0x691D50;
int activador = 256;
int activador_off = 0;

uintptr_t DISTANCIA = 0x60773C;
float distancia = 100;

//Parches para poder usar en multijugador el thirdperson
uintptr_t ACTIVADOR_PARCHE = 0x14FCE6;
unsigned char activador_parche[] = { 0xC6, 0x81, 0xA1,0x00,0x00,0x00, 0x01 };

uintptr_t DISTANCIA_PARCHE = 0x14FCC6;
unsigned char distancia_parche[] = { 0x90,0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, };


int main()
{
	//Abrir el proceso
	hp = kg_abrir_proceso("cstrike_win64.exe", PROCESS_ALL_ACCESS);

	//Cargar modulos
	client = kg_obtener_modulo_info(pid, L"client.dll");

	//Parcheo automatico
	WriteProcessMemory(hp, (LPBYTE)(client.base + ACTIVADOR_PARCHE), &activador_parche, sizeof(activador_parche), 0);
	WriteProcessMemory(hp, (LPBYTE)(client.base + DISTANCIA_PARCHE), &distancia_parche, sizeof(distancia_parche), 0);

	while (1)
	{
		if (GetKeyState(VK_F2))
		{
			//Activar el thirdperson
			WriteProcessMemory(hp, (LPBYTE)(client.base + ACTIVADOR), &activador, sizeof(activador), 0);
			//Cambiar la distancia de la camara
			WriteProcessMemory(hp, (LPBYTE)(client.base + DISTANCIA), &distancia, sizeof(distancia), 0);
		}
		else {
			WriteProcessMemory(hp, (LPBYTE)(client.base + ACTIVADOR), &activador_off, sizeof(activador_off), 0);

		}
		Sleep(10);
	}
	
}