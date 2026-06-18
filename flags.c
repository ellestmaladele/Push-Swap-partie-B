/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addufour <addufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:17:02 by addufour          #+#    #+#             */
/*   Updated: 2026/06/16 17:22:01 by addufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void    init_config(t_config *cfg)
{
    cfg->strategy = ADAPTIVE;
    cfg->used_strategy = ADAPTIVE;
    cfg->disorder = 0.0;
    cfg->bench = 0;
}

int parse_flag(char *arg, t_config *cfg)
{
    if (!ft_strcmp(arg, "--simple"))
        cfg->strategy = SIMPLE;
    else if (!ft_strcmp(arg, "--medium"))
        cfg->strategy = MEDIUM;
    else if (!ft_strcmp(arg, "--complex"))
        cfg->strategy = COMPLEX;
    else if (!ft_strcmp(arg, "--adaptive"))
        cfg->strategy = ADAPTIVE;
    else if (!ft_strcmp(arg, "--bench"))
        cfg->bench = 1;
    else
        return (0);
    return (1);
}

void    run_strategy(t_stack **a, t_stack **b, t_config *cfg)
{
    cfg->used_strategy = cfg->strategy;
    if (cfg->strategy == SIMPLE)
        mini_sort(a, b, NULL);
    else if (cfg->strategy == MEDIUM)
    {
        assign_indexes(*a);
        radix_sort(a, b, NULL);
    }
    else if (cfg->strategy == COMPLEX)
    {
        assign_indexes(*a);
        radix_sort(a, b, NULL);
    }
    else
        adaptive_sort(a, b, cfg);
}

// differencier medium et complex//
