#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct drawing
{
	int	width;
	int	length;
	char	*matrice;
}				drawing;

typedef struct shape
{
	char	type;
	float x, y;
	float radius;
	char	color;
}				shape;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

int		is_in_circle(float x, float y, shape *circle)
{
	float	distance;

	distance = sqrtf(powf(x - circle->x, 2) + powf(y - circle->y, 2));
	distance -= circle->radius;
	if (distance <= 0.00000000)
	{
		if (distance <= -1.00000000)
			return (1);
		return (2);
	}
	return (0);
}

void	apply_one(shape *circle, drawing *drawing)
{
	int	in;
	int	x;
	int	y;

	y = 0;
	while (y < drawing->length)
	{
		x = 0;
		while (x < drawing->width)
		{
			in = is_in_circle((float)x, (float)y, circle);
			if ((in == 2 && circle->type == 'c') || (in && circle->type == 'C'))
				drawing->matrice[y * drawing->width + x] = circle->color;
			x++;
		}
		y++;
	}
}

int	get_info(FILE *file, drawing *drawing)
{
	int	ret;
	char	back;
	char	*tmp;

	if ((ret = fscanf(file, "%d %d %c\n", &drawing->width, &drawing->length, &back)) == 3)
	{
		if (drawing->width <= 0 || drawing->width > 300 || drawing->length <= 0 || drawing->length > 300)
			return (1);
		tmp = malloc(sizeof(char) * drawing->width * drawing->length);
		drawing->matrice = tmp;
		if (!drawing->matrice)
			return (1);
		ret = 0;
		while (ret < drawing->width * drawing->length)
			drawing->matrice[ret++] = back;
		return (0);
	}
	return (1);
}

void	print_drawing(drawing * drawing)
{
	int		i;

	i = 0;
	while (i < drawing->length)
	{
		write (1, drawing->matrice + i * drawing->width, drawing->width);
		write (1, "\n", 1);
		i++;
	}
}

int	execute(FILE *file)
{
	shape	circle;
	drawing drawing;
	int		ret;

	if (!get_info(file, &drawing))
	{
		while ((ret = fscanf(file, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.color)) == 5)
		{
			if (circle.radius <= 0.00000000 || (circle.type != 'c' && circle.type != 'C'))
				return (1);
			apply_one(&circle, &drawing);
		}
		if (ret == -1)
		{
			print_drawing(&drawing);
			return (0);
		}
		return (1);
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	FILE	*file;

	if (ac == 2)
	{
		file = fopen(av[1], "r");
		if (file && !execute(file))
			return 0;
		i = ft_strlen("Error: Operation file corrupted\n");
		write(1, "Error: Operation file corrupted\n", i);
	}
	else
	{
		i = ft_strlen("Error: argument\n");
		write(1, "Error: argument\n", i);
	}
	return (1);
}
