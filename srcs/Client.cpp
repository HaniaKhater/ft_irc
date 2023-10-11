#include "Client.hpp"

Client::Client(int fd) : _clientfd(fd) {
	std::cout << "Client " << fd << " Created" << std::endl;
}

Client::~Client() {
	std::cout << "client " << _clientfd<< " destroyed" << std::endl;
}

int				Client::getClientfd() const	{ return _clientfd; }

std::string		Client::getNickname() const	{ return _nickname; }

void			Client::setNickname(std::string const&nickname) {
	_nickname = (_nickname.size() > 9) ? nickname.substr(0, 9) : nickname;
}

std::string		Client::getUsername() const { return _username; }

void			Client::setUsername( std::string const &username) { _username = username; }
