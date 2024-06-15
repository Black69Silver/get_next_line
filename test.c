#include "get_next_line.h"

int	main(void) 
{
	FILE *file;
	char *line;
	int fd;
	size_t	i;

	// Open the file in read mode ("r")
	file = fopen("/Users/ggeorgie/Documents/04_get_next_line/for_submission/input.txt", "r");

	// Check if the file was successfully opened
	if (file == NULL) 
	{
		printf("Unable to open the file.\n");
		return 1; // Return an error code
	}

	// Obtain the file descriptor
	fd = fileno(file);

	// Perform operations on the file using fd if needed
	i = 0;
	while (i < 9)
	{
		line = get_next_line(fd);
		printf("return [%zu]: '%s'\n", i, line);
		free(line);
		i++;
	}
	return (0);

	// Close the file when done
	fclose(file);

	return 0; // Return success code
}

/*
Abracadabra
Hocus-pocus, tontus-talontus
Vade celeriter jubeo!


*/