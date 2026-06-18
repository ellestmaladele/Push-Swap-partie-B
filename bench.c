#include "pushswap.h"

static void put_long_fd(long n, int fd)
{
    if (n < 0)
    {
        ft_putchar_fd('-', fd);
        n = -n;
    }
    if (n >= 10)
        put_long_fd(n / 10, fd);
    ft_putchar_fd((n % 10) + '0', fd);
}

static void put_disorder(double disorder)
{
    long    value;

    value = (long)(disorder * 1000.0);
    put_long_fd(value / 1000, 2);
    ft_putchar_fd('.', 2);
    ft_putchar_fd(((value / 100) % 10) + '0', 2);
    ft_putchar_fd(((value / 10) % 10) + '0', 2);
    ft_putchar_fd((value % 10) + '0', 2);
}
const char	*strategy_complexity(t_strategy strategy)
{
	if (strategy == SIMPLE)
		return ("Optimized for <= 5 elements");
	if (strategy == MEDIUM)
		return ("Chunk-based strategy");
	if (strategy == COMPLEX)
		return ("Radix-based strategy");
	if (strategy == ADAPTIVE)
		return ("Disorder-driven selection");
	return ("Unknown");
}
static const char	*adaptive_regime(double disorder)
{
	if (disorder < LOW_DISORDER)
		return ("LOW (nearly sorted)");
	if (disorder < MEDIUM_DISORDER)
		return ("MEDIUM (partially disordered)");
	return ("HIGH (highly disordered)");
}
static void	print_bench_header(t_config *cfg, int size)
{
	ft_putstr_fd("\n========== BENCH ==========\n", 2);
	ft_putstr_fd("Input size       : ", 2);
	ft_putnbr_fd(size, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Strategy         : ", 2);
	ft_putstr_fd((char *)strategy_name(cfg->used_strategy), 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Strategy profile : ", 2);
	ft_putstr_fd((char *)strategy_complexity(cfg->used_strategy), 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Disorder         : ", 2);
	put_disorder(cfg->disorder);
	ft_putstr_fd("\n", 2);
}

static void print_adaptive_info(t_config *cfg)
{
    if (cfg->used_strategy != ADAPTIVE)
        return ;
    ft_putstr_fd("Adaptive regime  : ", 2);
    ft_putstr_fd((char *)adaptive_regime(cfg->disorder), 2);
    ft_putstr_fd("\n", 2);
}

static void print_moves_part1(t_bench *bench)
{
    ft_putstr_fd("sa  : ", 2);
    put_long_fd(bench->sa, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("sb  : ", 2);
    put_long_fd(bench->sb, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("ss  : ", 2);
    put_long_fd(bench->ss, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("pa  : ", 2);
    put_long_fd(bench->pa, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("pb  : ", 2);
    put_long_fd(bench->pb, 2);
    ft_putstr_fd("\n", 2);
}

static void print_moves_part2(t_bench *bench)
{
    ft_putstr_fd("ra  : ", 2);
    put_long_fd(bench->ra, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("rb  : ", 2);
    put_long_fd(bench->rb, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("rr  : ", 2);
    put_long_fd(bench->rr, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("rra : ", 2);
    put_long_fd(bench->rra, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("rrb : ", 2);
    put_long_fd(bench->rrb, 2);
    ft_putstr_fd("\n", 2);
}
static void	print_moves_part3(t_bench *bench)
{
	ft_putstr_fd("rrr : ", 2);
	put_long_fd(bench->rrr, 2);
	ft_putstr_fd("\n", 2);
}
void	print_bench(t_config *cfg, t_bench *bench, int size)
{
	print_bench_header(cfg, size);
	print_adaptive_info(cfg);
	ft_putstr_fd("\n--- Operations detail ---\n", 2);
	print_moves_part1(bench);
	print_moves_part2(bench);
	print_moves_part3(bench);
	ft_putstr_fd("Total operations : ", 2);
	put_long_fd(bench->total, 2);
	ft_putstr_fd("\n===========================\n", 2);
}

const char	*strategy_name(t_strategy strategy)
{
	if (strategy == SIMPLE)
		return ("SIMPLE");
	if (strategy == MEDIUM)
		return ("MEDIUM");
	if (strategy == COMPLEX)
		return ("COMPLEX");
	if (strategy == ADAPTIVE)
		return ("ADAPTIVE");
	return ("UNKNOWN");
}
