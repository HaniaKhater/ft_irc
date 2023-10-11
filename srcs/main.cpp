#include "../incs/Server.hpp"

bool	servShutdown = false;

static void signalHandler(int signal) {
	(void)signal;
	servShutdown = true;
}

int	main(int ac, char **av) {
	if (ac != 3) {
		std::cout << "Invalid input. Please try ./ircserv [port] [password]" << std::endl;
		return (FAILURE);
	}
	signal(SIGINT, signalHandler);
	Server	server(av[1], av[2]);
	server.setHints();
	if (server.setServinfo(av[1]) == FAILURE) {
		std::cerr << "MAIN - setServinfo Failure" << std::endl;
		return(FAILURE);
	}
	if (server.startServer() == FAILURE) {
		std::cerr << "MAIN - startServer Failure" << std::endl;
		return(FAILURE);
	}
	return (SUCCESS);
}
