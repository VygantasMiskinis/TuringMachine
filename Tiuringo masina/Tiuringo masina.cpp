// Tiuringo masina.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <windows.h>
using namespace std;
class TiuringoKompiuteris
{
	
	
private:
	int galvosPozicija;
	string busena = "0";
	vector <string> juosta;
	vector <vector<string>> kodas;
	string name;

	
public:
	TiuringoKompiuteris(string vardas) {

		name = vardas;
	}
	void nuskaitymas()
	{
		
		if (name != "Klaida")

		{
			ifstream read(name);
			vector <char> tempC;
			vector <string> tempS;
			read >> galvosPozicija;
			char elementas;
			string elementasS;
			read.get();
			do
			{
				read.get(elementas);
				if (elementas != '\n')
					tempC.push_back(elementas);
			} while (elementas != '\n');


			for (int i = 0; i < tempC.size(); i++)
			{
				string laikinas;
				laikinas = tempC[i];
				juosta.push_back(laikinas);
			}

			tempC.clear();

			while (!read.eof())
			{

				for (int i = 0; i < 5; i++)
				{
					read >> elementasS;

					tempS.push_back(elementasS);
				}
				if (read.eof())
					break;
				kodas.push_back(tempS);
				tempS.clear();
			}
			tempS.clear();
			read.close();
			if (juosta.empty())
			{
				busena = "Halt";
				juosta.push_back(" Failas nerastas ");
			}
		}
		else 
		{
			busena = "Halt";
			juosta.push_back(" Failas nerastas ");
		}
		
	}
	void israsymas()
	{
		if (busena != "Halt")
		{
			for (int i = 0; i < galvosPozicija; i++)
			{
				cout << " ";
			}
			cout << "V" << endl;
		}
		else cout << "Halt" << endl;
		for (auto it : juosta)
			cout << it;
		cout << "\n\n\n";
		
	}
	void step()
	{
		
			if (galvosPozicija < 0 || galvosPozicija >= juosta.size())
				busena = "Halt";

			for (int i = 0; i < kodas.size(); i++)
			{
				if (kodas[i][0] == busena&&juosta[galvosPozicija] == kodas[i][1])
				{
					juosta[galvosPozicija] = kodas[i][2];
					if (kodas[i][3] == "R") galvosPozicija++;
					else galvosPozicija--;
					busena = kodas[i][4];
					break;
				}
				else if (i + 1 >= kodas.size()) busena = "Halt";	
			}
              
			
		}
	
	
};
void threaduFunkcija(TiuringoKompiuteris * Komp)
{
	Komp->step();

}
string FailoVardas()
{
	string temp;
	getline(cin,temp);
	switch (temp[0])
	{
		case ('1'):
			return "1.txt";
		break;
	case ('2'):
		return "2.txt";
		break;
	case ('3'):
		return "3.txt";
		break;
	case ('4'):
		return "4.txt";
		break;
	default:
		return "Klaida";
		break;
	}
	
	
}
void keyIsPressed(bool  & boolean)
{
	while(!boolean)
	if (GetKeyState('X') & 0x8000)
	{
		boolean = true;
	}
}
int main()
{
	bool testi = true;

	while (testi)
	{
		testi = false;

		vector <TiuringoKompiuteris> uzduotys;
		for (int i = 0; i < 4; i++)
		{
			cout << "Iveskite kuri tiuringo koda norite paleisti [1,2,3,4]" << endl;
			TiuringoKompiuteris temp(FailoVardas());
			uzduotys.push_back(temp);
			uzduotys[i].nuskaitymas();
		}
		bool reset = false;


		thread stop(keyIsPressed, std::ref(reset));
		while (!reset)
		{

			thread t1(threaduFunkcija, &uzduotys[0]);
			thread t2(threaduFunkcija, &uzduotys[1]);
			thread t3(threaduFunkcija, &uzduotys[2]);
			thread t4(threaduFunkcija, &uzduotys[3]);

			t1.join();
			t2.join();
			t3.join();
			t4.join();
			system("CLS");

			for (auto it : uzduotys)
				it.israsymas();
			cout << "X - baigti skaiciavima" << endl;
			this_thread::sleep_for(100ms);

		}
		stop.join();
		cout << "Pradëti ið naujo? [T/N]" << endl;
		char tmp;
		cout << endl;
		cin.get(tmp);
		cin.ignore();
		if (tmp == 'T')
			testi = true;
	}
}


/*
pgr kintamieji: juosta, galvutes pozicija, komandinis kodas , dabartine busena;
pgr veiksmai: 
1. nuskaitymas
2. komandu vykdymas
   2.1 surandama reikalinga kodo eilute
   2.2 patikrinama salyga (dabartinis simbolis)
   2.3 atitikus ( pakeiciama nauju simboliu, pakeiciama busena i nauja)
       2.3.1 keliaujama i naujos busenos pradzia
	   2.3.2 keliaujama i desine/kaire galvute
   2.4 neatitikus toliau einama zemyn kodu kol pasiekiama busenos pabaiga (tokiu atveju kodas stabdomas (HALT) nes neaprasytas tam tikras simbolis toje busenoje

3. isvedami ekrane pakeitimai

   */