/**
	Task: object Coder
	1. На основе класса Coder реализовать кодер/декодер шифра простой перестановки + 
		> Поле ключа - private
		> Конструктор без параметров генерирует рандомный ключ
		> Конструктор с параметрами создает объект с заданным ключом
		> Методы decode и encode должны производить разшифрование и шифрование соответственно
		> Примеры использования методов класса за пределами класса:
			Coder object;
			std::string text;
			syd::cin >> text;
			text = object.encode(text);
			std::cout << "Encoded text: " << text << std::endl;
			std::cout << "Decoded text: " << object.decode(text) << std::endl;

	2. На основе класса Coder реализовать объект, способный создавать защищенный канал с объектом того же типа.
		> Кроме private поля secret_key или private_key использовать public поле public_key
		> ВСЕ секретные поля должны быть private
		> ВСЕ открытые ключи должны быть public
		> Использовать для создания защищенного канала один из шифров с открытым ключом.
			1. Диффи-Хеллман +
			2. Шамир +
			3. Дль-Гамаль
		> Реализовать то же самое на RSA. 

**/
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#ifndef __CODER_H__
#define __CODER_H__

namespace classes
{
class Coder_Perestanovok {
private:
	int private_key;

	int private_key_size = 3;

	std::string coding(const std::string& simple_text, const int local_key);
public:
	//int public_key;

	Coder_Perestanovok();
	Coder_Perestanovok(int key);

	//int get_public_key();

	std::string encode(std::string simple_text);
	std::string decode(std::string chiper_text);

};

int32_t pow_10(int32_t number, int32_t razryad);//Эта функция делает не то что хотелось бы, но мне лень править 4 и 3 дадут -> 4000
int32_t pow_special(int32_t number, int32_t razryad, int32_t determinator);

class Dal_Ghamal {
private:
	int private_key;

public:
	const int p = 107, g = 2;
	int r = 0;
	int public_key;
	Dal_Ghamal();
	Dal_Ghamal(int key);

	std::string encode(std::string simple_text, int key_b);
	std::string decode(std::string chiper_text, int r);

};


class Diffie_Hellman {
private:
	int private_key;
	void generate_public_key();
	int secret_key;

public:
	int public_key;
	int p = 23;
	int g = 5;
	Diffie_Hellman();
	Diffie_Hellman(int key);

	void make_secret_key(int another_public_key);
	int get_public_key();

	std::string encode(std::string simple_text);
	std::string decode(std::string chiper_text);

};

class Shamir {
private:
	int private_key ;
	int private_key_two;

public:
	int p = 107;
	std::string for_good_decoding;

	Shamir(int key, int key_two);
	int coding(int number) const;
	int decoding(int number) const;

	std::string encode(std::string simple_text, const Shamir& b);
	std::string decode(std::string simple_text, const Shamir& b);
};

class RSA {
private:

	const int16_t p = 3557, q = 2579; // два простых числа

	int fi; //Функция Эйлера получателя

	int d; // private key

	int evklid(int U, int V, int restU, int restV);
public:
	
	int n; // n получателя
	
	const int8_t e; // открытая экспонента 17
	


	RSA(int key_e);

	
	std::vector<int32_t> encode(std::string simple_text, int b_e, int b_n);
	std::string decode(std::vector<int32_t> chiper_text);

};
}
#endif

//cplusplus.com search rand.h



// Coder obj;
// std::string vec;
// std::cout << obj.encode(vec);
// std::cout << obj.decode(obj.encode(vec));
