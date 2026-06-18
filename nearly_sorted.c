#include "pushswap.h"

static int	has_local_inversion(t_stack *a)
{
	while (a && a->next)
	{
		if (a->value > a->next->value)
			return (1);
		a = a->next;
	}
	return (0);
}
static void	correct_top(t_stack **a)
{
	if ((*a)->next
		&& (*a)->value > (*a)->next->value)
		sa(a);
	else
		ra(a);
}
static void	rewind_stack(t_stack **a)
{
	int	size;

	size = stack_size(*a);
	while (size--)
		rra(a);
}
void	nearly_sorted_sort(t_stack **a)
{
	int	limit;

	limit = stack_size(*a) * stack_size(*a);
	while (has_local_inversion(*a) && limit--)
		correct_top(a);
	rewind_stack(a);
}
