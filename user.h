#pragma once 
#include <string>

class User
{
    std::string _login;
    std::string _password;
    std::string _name;
public:
    User(const std::string& login, const std::string& password, const std::string& name)
        : _login(login), _password(password), _name(name) {
    }

    const std::string& get_login() const
    {
        return _login;
    }

    bool check_password(const std::string& pass) const
    {
        return _password == pass;
    }

    const std::string& get_name() const
    {
        return _name;
    }
};

