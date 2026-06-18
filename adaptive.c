/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addufour <addufour@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:19:48 by addufour          #+#    #+#             */
/*   Updated: 2026/06/17 15:21:53 by addufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_strategy choose_strategy(int size, double disorder)
{
    if (size <= 5)
        return (SIMPLE);

    if (disorder < 0.2)
        return (ADAPTIVE);

    if (disorder < 0.5)
        return (MEDIUM);

    return (COMPLEX);
}

static void execute_simple(t_stack **a, t_stack **b, t_config *cfg)
{
    (void)cfg;
    mini_sort(a, b, NULL);
}

static void execute_adaptive(t_stack **a, t_stack **b, t_config *cfg)
{
    (void)b;
    (void)cfg;

    nearly_sorted_sort(a);
}

static void execute_medium(t_stack **a, t_stack **b, t_config *cfg)
{
    (void)cfg;

    assign_indexes(*a);
    chunk_sort(a, b);
}

static void execute_complex(t_stack **a, t_stack **b, t_config *cfg)
{
    (void)cfg;

    assign_indexes(*a);
    radix_sort(a, b, NULL);
}

void    adaptive_sort(t_stack **a, t_stack **b, t_config *cfg)
{
    int size;

    if (!a || !*a || !cfg)
        return ;
    size = stack_size(*a);
    cfg->used_strategy = choose_strategy(size, cfg->disorder);
    if (cfg->used_strategy == SIMPLE)
        execute_simple(a, b, cfg);
    else if (cfg->used_strategy == ADAPTIVE)
        execute_adaptive(a, b, cfg);
    else if (cfg->used_strategy == MEDIUM)
        execute_medium(a, b, cfg);
    else
        execute_complex(a, b, cfg);
}
