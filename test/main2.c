#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *path_array;

	path_array = getenv("PATH");
	if (path_array == NULL)
		printf("ERROR\n");
	printf("path_array : %s", path_array);
}
