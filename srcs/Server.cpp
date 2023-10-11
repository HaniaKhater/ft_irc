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
	if (getaddrinfo(NULL, port, &_hints, &_servinfo) != SUCCESS)
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
	try {
		setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
		bind(_socketfd, _servinfo->ai_addr, _servinfo->ai_addrlen);
		listen(_socketfd, BACKLOG);
	}
	catch (std::exception &e) {
		std::cerr << "SERVER ERROR - " << e.what()  << std::endl;
		return (freeaddrinfo(_servinfo), FAILURE);
	}
	freeaddrinfo(_servinfo);
	std::cout << "Server launch was a success!" << std::endl;
	return (SUCCESS);
}

// SERVER MANAGEMENT

int				Server::loopServer() {
	std::vector<pollfd>	fds;
	pollfd				serv_fd;

	serv_fd.fd = _socketfd;
	serv_fd.events = POLLIN;

	fds.push_back(serv_fd);
	while (servShutdown == false) {
		if (poll((pollfd *)&fds[0], (unsigned int)fds.size(), -1) <= SUCCESS) {
			if (errno == EINTR) //Signal MG
				break ;
			std::cerr << "SERVER - Poll Failure" << std::endl;
			throw;
		}
	}
	return (SUCCESS);
}

// ACCESSORS (GETTERS AND SETTERS)

std::string		Server::getPort() const { return (_port); }

std::string		Server::getPassword() const { return (_password); }

void			Server::setPassword(std::string new_pw) { _password = new_pw; }

std::string		Server::getMotD() const { return (_MotD); }

void			Server::setMotD(std::string buffer) { _MotD = buffer; }
