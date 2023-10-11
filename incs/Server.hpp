#ifndef SERVER_HPP
#define SERVER_HPP

#include "Irc.hpp"

class Server
{
	private:
		struct addrinfo		_hints;
		struct addrinfo		*_servinfo;
		int					_socketfd;
		std::string			_port;
		std::string			_password;
		std::string			_MotD;

	public:
		Server(std::string port, std::string Password);
		~Server();
		// Socket Preparartion
		void			setHints();
		int				setServinfo(char *port);
		int				startServer(void);
		// Accessors
		std::string		getPort() const;
		std::string		getPassword() const;
		void			setPassword(std::string new_pw);
		std::string		getMotD() const;
		void			setMotD(std::string buffer);
};

#endif
