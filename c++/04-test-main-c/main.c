#include <stdbool.h>
#include <stdlib.h>

extern bool server();

// int main(int argc, char **argv)
int main(void)
{
	if (!server())
		return EXIT_FAILURE;
	return 0;
}