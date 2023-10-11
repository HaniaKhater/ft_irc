#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Irc.hpp"

class Client {
	private:
		int				_clientfd;
		std::string		_nickname;
		std::string		_username;

	public:
		Client(int fd);
		~Client();

		// Accessors
		int			getClientfd() const;
		std::string	getNickname() const;
		void		setNickname(std::string const &nickname);
		std::string	getUsername() const;
		void		setUsername(std::string const &username);
};

#endif
