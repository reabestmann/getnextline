/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:44:42 by rbestman          #+#    #+#             */
/*   Updated: 2025/01/03 17:22:49 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	char	*line;
	int	counter;
	int	fd;
	int	file_num;

	if (argc < 2)
	{
		printf("Usage: %s file1 file2 file3 etc\n", argv[0]);
		return 1;
	}
	file_num = 1;
	while(argv[file_num])
	{
		fd = open(argv[file_num], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening file");
			return (1);
		}
		printf("\nProcessing file: %s\n", argv[file_num]);
		counter = 1;
		while((line = get_next_line(fd)) != NULL)
		{
			printf("line %d: %s\n", counter, line);
			free(line);
			counter++;
		}
		close(fd); 
		file_num++;
	}
	return (0);
}
