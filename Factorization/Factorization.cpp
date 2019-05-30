//ƒелители числа
//Created by ©2017, bedvit (bedvit@mail.ru)
#include <mpirxx.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <thread>
#include <Windows.h>

CRITICAL_SECTION cs;//критическа€ секци€
unsigned long long Ostatok;
unsigned long long Ostatok2;
unsigned long long oldMn;
unsigned long long ArrRez[3000] = {0,1};
int option;
int Solutions(1);
int y(1);
int y2(1);
mpz_class mpz_Ostatok;
mpz_class mpz_Ostatok2;
mpz_class mpz_oldMn;
mpz_class mpz_ArrRez[100000] = { 0,1 };

void Func(int start)
{
	unsigned long long Ch=(1);
	unsigned long long Mn = 30 * Ch + start;
	while (Mn <= Ostatok2) {
		if (Ostatok%Mn == 0) {
		EnterCriticalSection(&cs);//критическа€ секци€
		Ostatok = Ostatok / Mn;
		Ostatok2 = (unsigned long long)sqrt(Ostatok);
			if (option == 3) {
				if (oldMn != Mn) {
					for (y = 1; y <= Solutions; y++) {
					ArrRez[Solutions + y] = ArrRez[y] * Mn;
					std::cout << ArrRez[Solutions + y] << std::endl;
					}
				Solutions = Solutions + y - 1;
					}
				else {
					for (y2 = 1; y2 < y; y2++) {
					ArrRez[Solutions + y2] = ArrRez[Solutions - y + 1 + y2] * Mn;
					std::cout << ArrRez[Solutions + y2] << std::endl;
					}
				Solutions = Solutions + y2 - 1;
				}
			}
			else if (oldMn != Mn || option != 2) { Solutions++; std::cout << Mn << std::endl; } //или
		oldMn = Mn;
		LeaveCriticalSection(&cs);//критическа€ секци€
		}
		else{Ch++;Mn = 30 * Ch + start;}
	}
}
void Func2(int start)
{
	mpz_class mpz_Ch = (1);
	mpz_class mpz_Mn = 30 * mpz_Ch + start;
	while (mpz_Mn <= mpz_Ostatok2) {
		if (mpz_divisible_p(mpz_Ostatok.get_mpz_t(), mpz_Mn.get_mpz_t())==0){mpz_Ch++;mpz_Mn = 30 * mpz_Ch + start;}//проверка на делимость
		else {
		EnterCriticalSection(&cs);//критическа€ секци€
		mpz_Ostatok = mpz_Ostatok / mpz_Mn;
		mpz_Ostatok2 = sqrt(mpz_Ostatok);
			if (option == 3) {//проверка на выбранную опцию
				if (mpz_oldMn != mpz_Mn) {
					for (y = 1; y <= Solutions; y++) {
					mpz_ArrRez[Solutions + y] = mpz_ArrRez[y] * mpz_Mn;
					std::cout << mpz_ArrRez[Solutions + y] << std::endl;
					}
				Solutions = Solutions + y - 1;
				}
				else {
					for (y2 = 1; y2 < y; y2++) {
					mpz_ArrRez[Solutions + y2] = mpz_ArrRez[Solutions - y + 1 + y2] * mpz_Mn;
					std::cout << mpz_ArrRez[Solutions + y2] << std::endl;
					}
				Solutions = Solutions + y2 - 1;
				}
			}
			else if (mpz_oldMn != mpz_Mn || option != 2) { Solutions++; std::cout << mpz_Mn << std::endl; } //или
		mpz_oldMn = mpz_Mn;
		LeaveCriticalSection(&cs);//критическа€ секци€
		}
	}
}
int main()
{	InitializeCriticalSection(&cs);
	////////////////////вывод большого количества строк в консоль
	HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  size;
	size.X = 100;   // кол-во символов на строку
	size.Y = 10010;  // увеличиваем до нужного размера - количества переменных
	SetConsoleScreenBufferSize(hout, size);
	////////////////////
	std::string s;
	std::cout << "Created by 2017, bedvit (bedvit@mail.ru)\n\nFactorization of a number(factorization)=1\nSearch for prime divisors=2\nSearch for all divisors=3\n\nSelect a calculation option:= ";
	std::cin >> option;
	std::cout << "Enter the numeric: ";
	std::cin >> s;
	std::cout << "\nResult:\n1" << std::endl;
	unsigned int start_time = clock(); // начальное врем€
	mpz_Ostatok = s;
	if (mpz_probab_prime_p(mpz_Ostatok.get_mpz_t(), 100) == 0) {

		std::vector<std::thread> thr(8);
		int arr[] = { 0,1,7,11,	13,	17,	19,	23,	29 };

		if (mpz_Ostatok > 18446744073709551615)	{
			mpz_Ostatok2 = sqrt(mpz_Ostatok);
			mpz_class mpz_Mn = (2);
			//mpz_class mpz_oldMn;?????????????
			while (mpz_Mn <= 30) {
				if (mpz_divisible_p(mpz_Ostatok.get_mpz_t(), mpz_Mn.get_mpz_t()) == 0) { mpz_Mn++;}  //проверка на делимость
				else {
					mpz_Ostatok = mpz_Ostatok / mpz_Mn;
					mpz_Ostatok2 = sqrt(mpz_Ostatok);

					if (option == 3) {//проверка на выбранную опцию
						if (mpz_oldMn != mpz_Mn) {
							for (y = 1; y <= Solutions; y++) {
								mpz_ArrRez[Solutions + y] = mpz_ArrRez[y] * mpz_Mn;
								std::cout << mpz_ArrRez[Solutions + y] << std::endl;
							}
							Solutions = Solutions + y - 1;
						}
						else {
							for (y2 = 1; y2 < y; y2++) {
								mpz_ArrRez[Solutions + y2] = mpz_ArrRez[Solutions - y + 1 + y2] * mpz_Mn;
								std::cout << mpz_ArrRez[Solutions + y2] << std::endl;
							}
							Solutions = Solutions + y2 - 1;
						}
					}
					else if (mpz_oldMn != mpz_Mn || option != 2) { Solutions++; std::cout << mpz_Mn << std::endl; } //или
					mpz_oldMn = mpz_Mn;
				}
			}
			for (int i = 1; i <= 8; i++) thr[i - 1] = std::thread(Func2, arr[i]);
			for (int i = 1; i <= 8; i++) thr[i - 1].join();
			if (mpz_Ostatok > 1){//провер€ем остаток
				if (option == 3) {
					if (mpz_oldMn != mpz_Ostatok) {
						for (y = 1; y <= Solutions; y++) {
							mpz_ArrRez[Solutions + y] = mpz_ArrRez[y] * mpz_Ostatok;
							std::cout << mpz_ArrRez[Solutions + y] << std::endl;
						}
						Solutions = Solutions + y - 1;
					}
					else {
						for (y2 = 1; y2 < y; y2++) {
							mpz_ArrRez[Solutions + y2] = mpz_ArrRez[Solutions - y + 1 + y2] * mpz_Ostatok;
							std::cout << mpz_ArrRez[Solutions + y2] << std::endl;
						}
						Solutions = Solutions + y2 - 1;
					}
				}
				else { std::cout << mpz_Ostatok << std::endl; Solutions++; }
			}
		}
		else {
			Ostatok = mpz_Ostatok.get_ui();
			Ostatok2 = (unsigned long long)sqrt(Ostatok);
			unsigned long long Mn = (2);
			//unsigned long long oldMn;??????????
			while (Mn <= 30) {
				if (Ostatok%Mn == 0) {//проверка на делимость
					Ostatok = Ostatok / Mn;
					Ostatok2 = (unsigned long long)sqrt(Ostatok);
					
					if (option == 3) {//проверка на выбранную опцию
						if (oldMn != Mn) {
							for (y = 1; y <= Solutions; y++) {
								ArrRez[Solutions + y] = ArrRez[y] * Mn; 
								std::cout << ArrRez[Solutions + y] << std::endl; 
							}
						Solutions = Solutions + y-1;
						}
						else {
							for (y2 = 1; y2 < y; y2++) { 
								ArrRez[Solutions + y2] = ArrRez[Solutions - y + 1 + y2] * Mn; 
								std::cout << ArrRez[Solutions + y2] << std::endl;
							}
							Solutions = Solutions + y2 - 1;
						}
					}
					else if (oldMn != Mn || option != 2){Solutions++;std::cout << Mn << std::endl;} //или
					oldMn = Mn;
				}
				else { Mn++; }
			}
			for (int i = 1; i <= 8; i++) thr[i - 1] = std::thread(Func, arr[i]);
			for (int i = 1; i <= 8; i++) thr[i - 1].join();
			if (Ostatok > 1) {//провер€ем остаток
				if (option == 3) {
					if (oldMn != Ostatok) {
						for (y = 1; y <= Solutions; y++) {
							ArrRez[Solutions + y] = ArrRez[y] * Ostatok;
							std::cout << ArrRez[Solutions + y] << std::endl;
						}
						Solutions = Solutions + y - 1;
					}
					else {
						for (y2 = 1; y2 < y; y2++) {
							ArrRez[Solutions + y2] = ArrRez[Solutions - y + 1 + y2] * Ostatok;
							std::cout << ArrRez[Solutions + y2] << std::endl;
						}
						Solutions = Solutions + y2 - 1;
					}
				}
				else { std::cout << Ostatok << std::endl; Solutions++; }
			}
		}
	}
	else { std::cout << s << std::endl; Solutions++;}//если число простое
	unsigned int end_time = clock(); // конечное врем€
	unsigned int search_time = end_time - start_time; // искомое врем€
	printf("\nTime, sec (min): %f (%f) Solutions: %u\n", search_time / 1000.0, search_time / 60000.0, Solutions);
	system("pause");
	return 0;
}
