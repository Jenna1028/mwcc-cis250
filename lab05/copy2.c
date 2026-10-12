#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    int source_fd;
    int destination_fd;

    ssize_t bytes_read;
    ssize_t bytes_written;

    char buffer[BUFFER_SIZE];

//check commqnd line arguments
if (argc != 3)
{
    printf("Usage: %s source destination\n", argv[0]);
    return 1;
}

//open the source file
source_fd = open(argv[1], O_RDONLY);

if (source_fd == -1)
{
    perror("Error opeing source file");
    return 1;
}
    //open the destination file
    destination_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (destination_fd == -1)
    {
    	perror("Error opening destination file");
    	close(source_fd);
    	return 1;
    }

    //read in chunks
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {

	ssize_t total_written = 0;

	while (total_written < bytes_read)
	{
    	bytes_written = write(destination_fd,
                          buffer + total_written,
                          bytes_read - total_written);

    if (bytes_written <= 0)
    {
        if (bytes_written == -1)
        {
            perror("Error writing to destination file");
        }
        else
        {
            fprintf(stderr, "Error: No bytes written\n");
        }

        close(source_fd);
        close(destination_fd);
        return 1;
    }

    total_written += bytes_written;
    }

 }

    if (bytes_read == -1)
    {
        perror("Error reading source file");
        close(source_fd);
        close(destination_fd);
        return 1;
     }

     if (close(source_fd) == -1)
     {
    	perror("Error closing source file");
    	close(destination_fd);
    	return 1;
     }

     if (close(destination_fd) == -1)
     {
    	perror("Error closing destination file");
    	return 1;
      }

      printf("File copied successfully.\n");

	return 0;
}

