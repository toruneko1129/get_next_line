#include <unistd.h>
#include <fcntl.h>

int	main()
{
	int fd = open("./nl", O_RDWR);
	write(fd, "01234567890123456789012345678901234567890\n1", 43);
	close(fd);
	fd = open("./munl", O_RDWR);
	write(fd, "01234567890123456789012345678901234567890\n1\n2\n3\n4\n5", 51);
	close(fd);
}
