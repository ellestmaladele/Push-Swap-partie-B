/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addufour <addufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:58:01 by addufour          #+#    #+#             */
/*   Updated: 2026/06/16 17:22:32 by addufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void    assign_indexes(t_stack *a)
{
    t_stack *tmp;
    int     *sorted;
    int     size;

    size = stack_size(a);
    sorted = copy_values(a);
    if (!sorted)
        return ;
    sort_array(sorted, size);
    tmp = a;
    while (tmp)
    {
        tmp->index = find_index(sorted, size, tmp->value);
        tmp = tmp->next;
    }
    free(sorted);
}

int stack_max_index(t_stack *a)
{
    int max;

    max = 0;
    while (a)
    {
        if (a->index > max)
            max = a->index;
        a = a->next;
    }
    return (max);
}

int get_max_bits(t_stack *a)
{
    int max;
    int bits;

    max = stack_max_index(a);
    bits = 0;

    while ((max >> bits) != 0)
        bits++;

    return (bits);
}

void    radix_sort(t_stack **a, t_stack **b, t_bench *bench)
{
    int max_bits;
    int size;
    int bit;

    size = stack_size(*a);
    max_bits = get_max_bits(*a);
    bit = 0;
    while (bit < max_bits)
    {
        process_bit(a, b, bit, size, bench);
        restore_stack(a, b, bench);
        bit++;
    }
}

static int  *copy_values(t_stack *a)
{
    int     *arr;
    int     size;
    int     i;

    size = stack_size(a);
    arr = malloc(sizeof(int) * size);
    if (!arr)
        return (NULL);
    i = 0;
    while (a)
    {
        arr[i] = a->value;
        i++;
        a = a->next;
    }
    return (arr);
}

static void sort_array(int *arr, int size)
{
    int i;
    int j;
    int tmp;

    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

static int  find_index(int *sorted, int size, int value)
{
    int i;

    i = 0;
    while (i < size)
    {
        if (sorted[i] == value)
            return (i);
        i++;
    }
    return (-1);
}

static int  get_bit(int index, int bit)
{
    return ((index >> bit) & 1);
}

static void process_bit(t_stack **a, t_stack **b, int bit, int size, t_bench *bench)
{
    int i;

    if (!a || !*a)
        return ;
    i = 0;
    while (i < size)
    {
        if (get_bit((*a)->index, bit))
        {
            ra(a);
            bench_count(bench, OP_RA);
        }
        else
        {
            pb(a, b);
            bench_count(bench, OP_PB);
        }
        i++;
    }
}

static void restore_stack(t_stack **a, t_stack **b, t_bench *bench)
{
    while (*b)
    {
        pa(a, b);
        bench_count(bench, OP_PA);
    }
}
