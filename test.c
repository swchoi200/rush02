#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int		ft_strncmp(char *s1, char *s2, int n)
{
	int i;
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n)
		i++;
	if (i == n)
		return (s1[i - 1] - s2[i - 1]);
	return (s1[i] - s2[i]);
}

int main(int argc, char **argv)
{
	int fd;
	int i;
	int len_input;
	char buf[10000];

	if (argc != 2)
	{
		write(1,"Dict Error\n", 11);
		return (0);
	}
	fd = open("numbers.dict", O_RDONLY);
	if (fd == -1)
	{
		write(1,"Dict Error\n", 11);
		return (0);
	}
	if (read(fd, buf, sizeof(buf)) == -1)
	{
		write(1,"Dict Error\n", 11);
		return (0);
	}
	//printf("%s",buf);
	close(fd);
	len_input = 0;
	while (argv[1][len_input])
		len_input++;
	i = 0;
	while (buf[i])
	{
		if (ft_strncmp(&buf[i], argv[1], len_input) == 0)
			break ;
		i++;
	}
	if (buf[i] == '\0')
	{
		write(1,"Dict Error\n", 11);
		return (0);
	}
	while (!(buf[i] >= 'a' && buf[i] <= 'z'))
		i++;
	while (buf[i] >= 'a' && buf[i] <= 'z')
	{
		write(1, &buf[i], 1);
		i++;
	}
}
