#include<iostream>
#include"Chat.h"
using namespace std;

void Chat::run()
{
	ChatOne_ = true;
}
shared_ptr<User> Chat::getUserByLogin(const string& login) const
{
	for (auto &user: users_)
	{
		if (login == user.getUserLogin())
			return make_shared<User>(user);
	}
	return nullptr;
}

shared_ptr<User> Chat::getUserByName(const string& name) const
{
	for (auto& user: users_)
	{
		if (name == user.getUserName())
			return make_shared<User>(user);
	}
	return nullptr;
}
void Chat::login()
{
	string login, password;
	char operation;

	do
	{
		cout << "Логин:";
		cin >> login;
		cout << "Пароль:";
		cin >> password;

		currentUser_ = getUserByLogin(login);
		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;
			cout << "Пользователь не зарегестрирован" << endl;
			cout << "Нажми 'q' для выхода" << endl;
			cout <<"Любой символ для повтора: " << endl;
			cin >> operation;

			if (operation == 'q')
				break;
		}
	} while (!currentUser_);
}
void Chat::signUp()
{
	string login, password, name;

	cout << "Логин:  ";
	cin >> login;
	cout << "Пароль:  ";
	cin >> password;
	cout << "Имя:   ";
	cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLogin();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserName();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = std::make_shared<User>(user);
}
void Chat::showChat()const
{
	string from;
	string to;

	cout << "Чатик" << endl;

	for (auto& mess : messeges_)
	{
		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getUserLogin() == mess.getFrom() ? "Меня" : getUserByLogin(mess.getFrom())->getUserName());
			if (mess.getTo() == "all")
			{
				to = " Всем ";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "Мне" : getUserByLogin(mess.getTo())->getUserName();
			}
			cout << " Сообщение от " << from << "  Кому  " << to << endl;
			cout << "Текст  " << mess.getText() << endl;
		}
	}
	
}
void Chat::showLoginMenu()
{
	currentUser_ = nullptr;
	char operation;
	do
	{
		cout << "\tЧатик" << endl;
		cout << "1. Регистрация" << endl;
		cout << "2. Логин" << endl;
		cout << "3. Выход из программы" << endl;
		
		cin >> operation;

		switch (operation)
		{
		case '1':
			try
			{
				signUp();
			}
			catch (const exception & e)
			{
				cout << e.what() << endl;
			}
			break;
		case '2':
			login();
			break;
		case'3':
			ChatOne_ = false;
			break;
		default:
			cout << "Нажми 1, 2 или 3"<<endl;
			break;
		}
	} while (!currentUser_ && ChatOne_);
}
void Chat::showUserMenu()
{
	char operation;

	cout << "Привет,\t" << currentUser_->getUserName() << endl;
	cout << endl;
	while (currentUser_) 
	{
		cout << "Меню:" << endl;
		cout << "1. Показать чат" << endl;
		cout << "2. Написать сообщение" << endl;
		cout << "3. Пользователи" << endl;
		cout << "0. Выход" << endl;
		
		cout << endl;
		
		cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case'2':
			addMessege();
			break;
		case'3':
			showAllUserName();
			break;
		case'0':
			currentUser_ = nullptr;
			break;
		default:
			cout << "Неправильный выбор" << endl;
			break;
		}
	}
}

void Chat::showAllUserName() const
{
	cout << "Пользователь: " << endl;
	for (auto& user : users_)
	{
		cout << user.getUserName();
		if (currentUser_->getUserLogin() == user.getUserLogin())
			cout << " you " << endl;
			cout << endl;
	}
}

void Chat::addMessege()
{
	string to, text;

	cout << "Для личного сообщения 'Укажите имя пользователя!'" << endl;
	cout << "Написать Всем, введите 'all' " << endl;
	cin >> to;
	cout << "Текст:  ";
	cin.ignore();
	getline(cin,text);

	if (!(to == "all" || getUserByName(to)))
	{
		cout << "Такого пользователя нет: " << to << endl;
		cout << " Сообщение не отправлено." << endl;
		return;
	}

	if (to == "all")
		messeges_.push_back(Messege(currentUser_->getUserLogin(),"all" , text ));
	else
		messeges_.push_back(Messege(currentUser_ ->getUserLogin(), getUserByName(to)->getUserLogin(), text ));
}