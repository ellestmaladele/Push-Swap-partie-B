#include "pushswap.h"

static int	get_chunk_size(int size)
{
	if (size <= 100)
		return (15);
	return (30);
}

static void	push_chunk(t_stack **a, t_stack **b,
			int *limit, int chunk_size)
{
	pb(a, b);
	if (*b && (*b)->index < (*limit - chunk_size / 2))
		rb(b);
	(*limit)++;
}

static void	push_chunks_to_b(t_stack **a,
			t_stack **b, int chunk_size)
{
	int	limit;

	limit = chunk_size;
	while (*a)
	{
		if ((*a)->index <= limit)
			push_chunk(a, b, &limit, chunk_size);
		else
			ra(a);
	}
}
static int	find_max_pos(t_stack *b)
{
	int		pos;
	int		max_pos;
	int		max_index;

	pos = 0;
	max_pos = 0;
	max_index = b->index;
	while (b)
	{
		if (b->index > max_index)
		{
			max_index = b->index;
			max_pos = pos;
		}
		pos++;
		b = b->next;
	}
	return (max_pos);
}
static void	move_max_to_top(t_stack **b)
{
	int	pos;
	int	size;

	pos = find_max_pos(*b);
	size = stack_size(*b);
	if (pos <= size / 2)
	{
		while (pos--)
			rb(b);
	}
	else
	{
		pos = size - pos;
		while (pos--)
			rrb(b);
	}
}
static void	restore_to_a(t_stack **a, t_stack **b)
{
	while (*b)
	{
		move_max_to_top(b);
		pa(a, b);
	}
}
void	chunk_sort(t_stack **a, t_stack **b)
{
	int	chunk_size;

	chunk_size = get_chunk_size(stack_size(*a));
	push_chunks_to_b(a, b, chunk_size);
	restore_to_a(a, b);
}
