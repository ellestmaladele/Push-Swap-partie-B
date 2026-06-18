/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addufour <addufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:13:31 by addufour          #+#    #+#             */
/*   Updated: 2026/06/16 17:22:06 by addufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int find_min_pos(t_stack *a)
{
    int min;
    int pos;
    int min_pos;

    min = a->value;
    pos = 0;
    min_pos = 0;

    while (a)
    {
        if (a->value < min)
        {
            min = a->value;
            min_pos = pos;
        }
        pos++;
        a = a->next;
    }
    return (min_pos);
}

void    sort_two(t_stack **a)
{
    if ((*a)->value > (*a)->next->value)
        sa(a);
}

void    sort_three(t_stack **a)
{
    int first;
    int second;
    int third;

    first = (*a)->value;
    second = (*a)->next->value;
    third = (*a)->next->next->value;

    if (first > second && second < third && first < third)
        sa(a);
    else if (first > second && second > third)
    {
        sa(a);
        rra(a);
    }
    else if (first > second && second < third && first > third)
        ra(a);
    else if (first < second && second > third && first < third)
    {
        sa(a);
        ra(a);
    }
    else if (first < second && second > third && first > third)
        rra(a);
}

void    sort_four(t_stack **a, t_stack **b)
{
    move_min_to_top(a);
    pb(a, b);

    sort_three(a);

    pa(a, b);
}

void    sort_five(t_stack **a, t_stack **b)
{
    move_min_to_top(a);
    pb(a, b);

    move_min_to_top(a);
    pb(a, b);

    sort_three(a);

    pa(a, b);
    pa(a, b);
}

void    mini_sort(t_stack **a, t_stack **b, t_bench *bench)
{
    int size;

    (void)bench;
    size = stack_size(*a);

    if (is_sorted(*a))
        return ;

    if (size == 2)
        sort_two(a);
    else if (size == 3)
        sort_three(a);
    else if (size == 4)
        sort_four(a, b);
    else if (size == 5)
        sort_five(a, b);
}

int is_sorted(t_stack *a)
{
    while (a && a->next)
    {
        if (a->value > a->next->value)
            return (0);
        a = a->next;
    }
    return (1);
}

void    move_min_to_top(t_stack **a)
{
    int min_pos;
    int size;
    int moves;

    min_pos = find_min_pos(*a);
    size = stack_size(*a);
    if (min_pos <= size / 2)
    {
        while (min_pos-- > 0)
            ra(a);
    }
    else
    {
        moves = size - min_pos;
        while (moves-- > 0)
            rra(a);
    }
}
