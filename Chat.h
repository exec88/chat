#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Messege.h"
using namespace std;

struct UserLogin : public exception

{
	const char* what() const noexcept override { return "Логин занят"; }
};

struct UserName : public exception
{
	const char* what() const noexcept override { return "Имя занято"; }
};

class Chat
{
private:
	bool ChatOne_ = false;
	vector<User> users_;
	vector<Messege> messeges_;
	shared_ptr<User> currentUser_ = nullptr;

	void login();
	void signUp();
	void showChat() const;
	void showAllUserName() const;
	void addMessege();
	vector<User>& getAllUser() { return users_; }
	vector<Messege>& getAllMessege() { return messeges_; }
	shared_ptr<User> getUserByLogin(const string& login) const;
	shared_ptr<User> getUserByName(const string& name) const;
public:
	void run();
	bool ChatOne() const { return ChatOne_; }
	shared_ptr<User> getCurrentUser()const { return currentUser_; }
	void showLoginMenu();
	void showUserMenu();
};