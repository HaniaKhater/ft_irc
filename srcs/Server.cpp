#include "../incs/Server.hpp"

Server::Server(std::string port, std::string password)
	: _port(port), _password(password), _socketfd(0)
{
	std::cout << "Server is running" << std::endl;
	memset(&_hints, 0, sizeof(_hints));
}

Server::~Server()
{
	std::cout << "Server is shutting down" << std::endl;
}

// SOCKET PREPARATION

void 			Server::setHints()
{
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_flags = AI_PASSIVE;
}

int 			Server::setServinfo(char *port)
{
	if (getaddrinfo(NULL, port, &_hints, &_servinfo) < 0)
	{
		std::cerr << "SERVER - addrinfo Failure" << std::endl;
		return (FAILURE);
	}
	return (SUCCESS);
}

int 			Server::startServer()
{
	_socketfd = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);
	if (_socketfd == FAILURE)
	{
		std::cerr << "SERVER - Socket Failure" << std::endl;
		return (FAILURE);
	}
	int opt = 1;
	if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == FAILURE)
	{
		std::cerr << "SERVER - SetSockOpt Failure" << std::endl;
		return (freeaddrinfo(_servinfo), FAILURE);
	}
	std::cout << "bind arguments: " << _socketfd << " " << _servinfo->ai_addrlen << std::endl;
	if (bind(_socketfd, _servinfo->ai_addr, _servinfo->ai_addrlen) == FAILURE)
	{
		std::cerr << "SERVER - Bind Failure" << std::endl;
		return (freeaddrinfo(_servinfo), FAILURE);
	}
	if (listen(_socketfd, BACKLOG) == FAILURE)
	{
		std::cerr << "SERVER - Listen Failure" << std::endl;
		return (freeaddrinfo(_servinfo), FAILURE);
	}
	freeaddrinfo(_servinfo);
	return (SUCCESS);
}

// ACCESSORS (GETTERS AND SETTERS)

std::string		Server::getPort() const { return (_port); }

std::string		Server::getPassword() const { return (_password); }

std::string		Server::getMotD() const { return (_MotD); }

void			Server::setPassword(std::string new_pw) { _password = new_pw; }

void			Server::setMotD(std::string buffer) { _MotD = buffer; }
