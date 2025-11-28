#include "shell.h"

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to previous memory
 * @old_size: size of previous memory
 * @new_size: new size
 *
 * Return: pointer to new memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;
	char *old_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(new_size));

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_ptr = ptr;
	for (i = 0; i < old_size && i < new_size; i++)
		new_ptr[i] = old_ptr[i];

	free(ptr);
	return (new_ptr);
}

/**
 * check_buffer - checks if buffer needs refilling
 * @buf_pos: pointer to buffer position
 * @buf_size: pointer to buffer size
 * @buffer: buffer to fill
 * @fd: file descriptor
 *
 * Return: 0 on success, -1 on failure/EOF
 */
int check_buffer(size_t *buf_pos, size_t *buf_size, char *buffer, int fd)
{
	ssize_t r;

	if (*buf_pos >= *buf_size)
	{
		*buf_pos = 0;
		r = read(fd, buffer, READ_BUF_SIZE);
		if (r <= 0)
			return (-1);
		*buf_size = r;
	}
	return (0);
}

/**
 * _getline - reads a line from a file descriptor
 * @lineptr: pointer to the buffer
 * @n: size of the buffer
 * @fd: file descriptor to read from
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[READ_BUF_SIZE];
	static size_t buf_pos, buf_size;
	size_t line_pos = 0;
	char *line;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	line = *lineptr;
	while (1)
	{
		if (check_buffer(&buf_pos, &buf_size, buffer, fd) == -1)
		{
			if (line_pos == 0)
				return (-1);
			line[line_pos] = '\0';
			return (line_pos);
		}
		if (line_pos >= *n - 1)
		{
			line = _realloc(line, *n, *n * 2);
			if (!line)
				return (-1);
			*n *= 2;
			*lineptr = line;
		}
		line[line_pos] = buffer[buf_pos++];
		if (line[line_pos] == '\n')
		{
			line[line_pos + 1] = '\0';
			return (line_pos + 1);
		}
		line_pos++;
	}
}
