#include "coder.h"


std::string classes::Coder_Perestanovok::coding(const std::string& simple_text, const int local_key)
{
	std::string word;//исходное слово с размером ключа
	std::string encoded_text = ""; // Итоговый текст
	std::string encoded_word;// Закодированное слово

	int key = local_key;
	for (int i = 0; i < simple_text.size() / private_key_size; ++i) {//Разбиваем текст на слова
		word = "";
		encoded_word = "";
		key = local_key;
		for (int j = 0; j < private_key_size; ++j) {
			word += simple_text[j + i * private_key_size];
			encoded_word += '1';//размер для закодированного = кодированному, поэтому мы можем обращаться к encoded_word[key-1]
		}

		for (int j = 0; j < private_key_size; ++j) {
			encoded_word[key % 10 - 1] = word[private_key_size - j - 1];//перестановка в соответствии с ключём
			key /= 10;
		}
		encoded_text += encoded_word;
	}
	return encoded_text;
}


classes::Coder_Perestanovok::Coder_Perestanovok()
{

	std::vector<int> list_of_used_numbers;
	srand(time(0));
	rand();
	private_key = 0;
	for (int i = 0; i < private_key_size;) {
		int key = rand() % private_key_size + 1;

		bool everething_ok = true;
		for (int a : list_of_used_numbers) {//Проверка на различные индексы в ключе
			if (a == key) {
				everething_ok = false;
				break;
			}
		}
		if (!everething_ok)
			continue;
		private_key *= 10;
		private_key += key;
		list_of_used_numbers.push_back(key);
		++i;//Нужно что бы если сработал continue i не увеличился
	}
	std::cout << private_key << std::endl;
}

classes::Coder_Perestanovok::Coder_Perestanovok(int key)
{
	private_key_size = 0;
	private_key = key;
	for (int local_key = key; local_key != 0; ++private_key_size, local_key /= 10); // Считаем длину ключа

	std::vector<int> list_of_used_numbers;
	bool everething_ok = true;//Проверка на валидность ключа
	for (int i = 0; i < private_key_size; ++i, key /= 10) {
		int symbol = key % 10;
		for (int a : list_of_used_numbers) {//Проверка на различные индексы в ключе
			if (a == symbol) {
				everething_ok = false;
				throw static_cast<std::string>("Wrong Key");
			}
		}
		list_of_used_numbers.push_back(symbol);
	}
}

std::string classes::Coder_Perestanovok::encode(std::string simple_text)
{
	for (int i = 0; i < simple_text.size() % private_key_size; ++i) {//добавляем символы если число не делится на длину ключа
		simple_text += static_cast<char>(61);
	}

	return coding(simple_text, private_key);
}

std::string classes::Coder_Perestanovok::decode(std::string chiper_text)
{
	int key = private_key;
	int r_key = 0; // обратный ключ для расшифровки
	for (int i = 1; i < private_key_size + 1; ++i, key /= 10) {//получаем обратный код
		r_key += pow_10(private_key_size + 1 - i, private_key_size + 1 - key % 10); // Лучше забbть на это, но если не хочется, то смысл в том, что
																					//мы идём с "конца", первого разряда числа, но в теории это последнее число,
																					//поэтому мы кодируем его числом = private_key_size. Поэтому private_key_size + 1 - i
																					//Интересующая нас позиция в исходном key и по совместительству интересующее нас 
																					//значение в r_key. Аналогично и с private_key_size + 1 - key % 10
	}
	chiper_text = coding(chiper_text, r_key);
	while (chiper_text[chiper_text.size() - 1] == '=') {
		chiper_text[chiper_text.size() - 1] = NULL;
		chiper_text.resize(chiper_text.size() - 1);
	}
	return chiper_text;
}


int32_t classes::pow_10(int32_t number, int32_t razryad)//Функция возвращает число * на 10 в степени r
{
	int result = 1;
	for (int i = 1; i < razryad; ++i)
		result *= 10;
	return result * number;
}

int32_t classes::pow_special(int32_t number, int32_t razryad, int32_t determinator)
{
	int64_t result = 1;
	for(int i = 0; i < razryad; ++i) {
		result *= number;
		result = result % determinator;
	}
	return result;
}

void classes::Diffie_Hellman::generate_public_key()
{
	public_key = pow_special(g, private_key, p);
}

classes::Diffie_Hellman::Diffie_Hellman()
{
	srand(time(0));
	rand();
	private_key = rand() % 99 + 1;
	generate_public_key();
}

classes::Diffie_Hellman::Diffie_Hellman(int key)
{
	private_key = key;
	generate_public_key();
}

void classes::Diffie_Hellman::make_secret_key(int another_public_key)
{
	secret_key = pow_special(another_public_key, private_key, p);
}

int classes::Diffie_Hellman::get_public_key()
{
	return this->public_key;
}

std::string classes::Diffie_Hellman::encode(std::string simple_text)
{
	std::string text = simple_text;
	for (char& a : text) {
		a += secret_key;
	}
	return text;
}

std::string classes::Diffie_Hellman::decode(std::string chiper_text)
{
	std::string text = chiper_text;
	for (char& a : text) {
		a -= secret_key;
	}
	return text;
}

int classes::Shamir::coding(int number) const
{
	return pow_special(number, private_key, p);
}

int classes::Shamir::decoding(int number) const
{
	return pow_special(number, private_key_two, p);
}

classes::Shamir::Shamir(int key, int key_two): private_key(key), private_key_two(key_two){}

std::string classes::Shamir::encode(std::string simple_text, const Shamir& b)
{
	std::string text = simple_text;
	for (char& a : text) {
		a = coding(a-47);
	}
	for (char& a : text) {
		a = b.coding(a);
	}
	return text;
}

std::string classes::Shamir::decode(std::string simple_text, const Shamir& b)
{

	std::string text = simple_text;
	for (char& a : text) {
		a = static_cast<char>(b.decoding(a));
	}
	for (char& a : text) {
		a = static_cast<char>(decoding(a) + 47);
	}
	return text;
}

classes::Dal_Ghamal::Dal_Ghamal()
{
	srand(time(0));
	rand();
	private_key = rand() % (p-1);
	public_key = pow_special(g, private_key, p);
}

classes::Dal_Ghamal::Dal_Ghamal(int key): private_key(key)
{
	public_key = pow_special(g, key, p);
}

std::string classes::Dal_Ghamal::encode(std::string simple_text, int key_b)
{
	srand(time(0));
	rand();
	int k = rand() % (p - 2);
	r = pow_special(g, k, p);
	std::string text = simple_text;
	for (char& a : text) {
		a = ((a - 47) * pow_special(key_b, k, p))%p;
	}
	return text;
}

std::string classes::Dal_Ghamal::decode(std::string chiper_text, int r)
{
	std::string text = chiper_text;
	for (char& a : text) {
		a = (a * pow_special(r, p-1-private_key, p))%p + 47;
	}
	return text;
}

int classes::RSA::evklid(int U, int V, int restU, int restV)
{
	if (V == 0)
		return restU;
	int q = U / V;
	return evklid(V, U % V, restV, restU - q * restV);
}

classes::RSA::RSA(int key_e) : e(key_e)
{
	fi = (p - 1) * (q - 1);
	n = p * q;
	int V = e;
	int U = fi;
	if (U < V) {
		d = evklid(V, U, 1, 0);
		if (d < 0)
			d += V;
	}
	else {
		d = evklid(U, V, 0, 1);
		if (d < 0)
			d += U;
	}
}

std::vector<int32_t> classes::RSA::encode(std::string simple_text, int b_e, int b_n)
{
	std::vector<int32_t> res;
	std::string text = simple_text;
	for (char& a : text) {
		res.push_back(pow_special(a-47, b_e, b_n));
	}
	return res;
}

std::string classes::RSA::decode(std::vector<int32_t> chiper_text)
{
	std::string text;
	for (int32_t a : chiper_text) {
		text += pow_special(a, d, n) +47;
	}
	return text;
}
