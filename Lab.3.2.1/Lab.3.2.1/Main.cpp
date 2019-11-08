#include "coder.h"
#include <map>

enum commands { Perestanovki, DiffieHellman, Shamir, Dal_Ghamal, RSA };

int main()
{
	std::string variant;
	while (variant != "Exit") {
		std::map<std::string, commands> getEnum{ {"Perestanovki", Perestanovki}, {"DiffieHellman", DiffieHellman}, {"Shamir", Shamir}, {"Dal_Ghamal", Dal_Ghamal}, {"RSA", RSA} };

		std::cout << "Choose encription: Perestanovki, DiffieHellman, Shamir, RSA, Dal_Ghamal. Or type Exit." << std::endl;
		std::cin >> variant;
		if (variant == "Exit" || getEnum.find(variant) == getEnum.end())
			continue;

		std::string text, e_text;
typeMassage:
		std::cout << "Type massage: ";
		std::cin >> text;
		try {
			for (char a : text) {
				if (a < '0' || a > 'z')
					throw std::string("Type correct massage!\n");
			}
		}
		catch (std::string m)
		{
			std::cout << m << std::endl;
			goto typeMassage;
		}

		switch (getEnum[variant])
		{
		case Perestanovki:
		{
			try {
				classes::Coder_Perestanovok a(2143);
				e_text = a.encode(text);
				std::cout << e_text << std::endl;
				std::cout << a.decode(e_text) << std::endl;
			}
			catch (std::string a) {
				std::cout << a << std::endl;
			}
			break;
		}
		case DiffieHellman:
		{
			classes::Diffie_Hellman a(7);
			classes::Diffie_Hellman b(13);
			a.make_secret_key(b.get_public_key());
			b.make_secret_key(a.get_public_key());
			e_text = a.encode(text);
			std::cout << e_text << std::endl;
			std::cout << b.decode(e_text) << std::endl;
			break;
		}
		case Shamir:
		{
			classes::Shamir a(5, 85);//5*85 % 107-1 = 1
			classes::Shamir b(17, 25);
			e_text = a.encode(text, b);
			std::cout << e_text << std::endl;
			std::cout << b.decode(e_text, a) << std::endl;
			break;
		}
		case Dal_Ghamal:
		{
			classes::Dal_Ghamal a(30);
			classes::Dal_Ghamal b(50);
			e_text = a.encode(text, b.public_key);
			std::cout << e_text << std::endl;
			std::cout << b.decode(e_text, a.r) << std::endl;
			break;
		}
		case RSA:
		{
			classes::RSA a(17);
			classes::RSA b(17);
			std::vector<int32_t> e_text = a.encode(text, b.e, b.n);
			for (int32_t a : e_text) {
				std::cout << a << ' ';
			}
			std::cout << std::endl;
			std::cout << b.decode(e_text) << std::endl;
			break;
		}
		default:
			break;
		}

		//p должно быть < 127, так как иначе багает ASCII, но больше 90
		
	}
	return 0;
}