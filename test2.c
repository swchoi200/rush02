#include <stdlib.h>
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

void	print_value(char *buf, char **split, int row)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (i < row)
	{
		k = 0;
		while (buf[k])
		{
			j = 0;
			while (split[i][j])
				j++;
			if (ft_strncmp(buf, split[i], j) == 0)
				break ;
			k++;
		}
		if (buf[k] == '\0')
		{
			write(1,"Dict Error\n", 11);
			return ;
		}
		while (!(buf[k] >= 'a' && buf[k] <= 'z'))
			k++;
		while (buf[k] >= 'a' && buf[k] <= 'z')
		{
			write(1, &buf[k], 1);
			k++;
		}
		if (split[i])
		write(1, " ", 1);
		i++;
	}
}

int		main(int argc, char **argv)
{
	char **split;
	int i;
	int j;
	int row;
	int tmp;
	int fd;
	char buf[10000];

	if (argc < 2)
	{
		write(1, "error\n",6);
		return (0);
	}
	j = 0;
	while (argv[1][j])
	{
		if (!(argv[1][j] >= '0' && argv[1][j] <= '9'))
			write(1,"Error\n", 6);
		j++;
	}
	row = 0;
	while (argv[1][row])
		row++;
	//printf("%d",row);
	split = malloc(sizeof(char *) * row);
	i = 0;
	while (i < row)
	{
		split[i] = malloc(sizeof(char) * (row - i));
		i++;
	}
	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < row - i)
		{
			split[i][j] = '0';
			printf("%c ",split[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	tmp = 0;
	while (*argv[1])
	{
		tmp += *argv[1] - '0';
		if (*(argv[1] + 1) != '\0')
			tmp *= 10;
		argv[1]++;
	}
	//printf("%d\n",tmp);
	i = row - 1;
	while (tmp != 0)
	{
		split[i][0] = (tmp % 10) + '0';
		tmp /= 10;
		i--;
	}
	printf("%s\n",split[0]);
	printf("%s\n",split[1]);
	printf("%s\n",split[2]);
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
	close(fd);
	//printf("%s",buf);
	print_value(buf, split, row);
	/*i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);*/
}
