#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <unistd.h>

typedef struct s_node
{
	int value;
	int index;
	struct s_node *next;
} t_node;

typedef struct s_stacks
{
	t_node *a;
	t_node *b;
} t_stacks;

void	error_exit(const char *message);

t_node	*new_node(int value);
void	free_stack(t_node *stack);
int	stack_size(t_node *stack);
bool	stack_sorted(t_node *stack);
void	push_front(t_node **stack, t_node *node);
void	push_bottom(t_node **stack, t_node *node);
t_node	*pop_front(t_node **stack);
t_node	*stack_last(t_node *stack);
t_node	*stack_before_last(t_node *stack);

void	swap(t_node **stack);
void	rotate(t_node **stack);
void	reverse_rotate(t_node **stack);

void	sa(t_node **a);
void	sb(t_node **b);
void	ss(t_node **a, t_node **b);
void	pa(t_node **a, t_node **b);
void	pb(t_node **a, t_node **b);
void	ra(t_node **a);
void	rb(t_node **b);
void	rr(t_node **a, t_node **b);
void	rra(t_node **a);
void	rrb(t_node **b);
void	rrr(t_node **a, t_node **b);

t_node	*parse_arguments(int argc, char **argv);
void	assign_indices(t_node *stack);

void	sort_small(t_stacks *stacks);
void	sort_medium(t_stacks *stacks);

void	print_stack(const char *name, t_node *stack);

// disorder_metric //

int	stack_size(t_stack *stack);
int	*stack_to_array(t_stack *stack, int size);
long	count_total_pairs(int size);
long	count_inversions(int *arr, int size);
double	compute_disorder(t_stack *stack);

// bench //

static void	put_long_fd(long n, int fd);
static void	put_disorder(double disorder);
const char	*strategy_complexity(t_strategy strategy) static const char *adaptive_regime(double disorder);
static void	print_bench_header(t_config *cfg, int size);
static void	print_adaptive_info(t_config *cfg);
static void	print_moves_part1(t_bench *bench);
static void	print_moves_part2(t_bench *bench);
static void	print_moves_part3(t_benh *bench);
void	print_bench(t_config *cfg, t_bench *bench, int size);
const char	*strategy_name(t_strategy strategy);

// mini_sort //

int	find_min_pos(t_stack *a);
void	sort_two(t_stack **a);
void	sort_three(t_stack **a);
void	sort_four(t_stack **a, t_stack **b);
void	sort_five(t_stack **a, t_stack **b);
const char	*strategy_name(t_strategy strategy);
void	mini_sort(t_stack **a, t_stack **b, t_bench *bench);
int	is_sorted(t_stack *a);
void	move_min_to_top(t_stack **a);

// adaptive //

t_strategy	choose_strategy(int size, double disorder);
static void	execute_simple(t_stack **a, t_stack **b, t_config *cfg);
static void	execute_adaptive(t_stack **a, t_stack **b, t_config *cfg);
static void	execute_medium(t_stack **a, t_stack **b, t_config *cfg);
static void	execute_complex(t_stack **a, t_stack **b, t_config *cfg);
void	adaptive_sort(t_stack **a, t_stack **b, t_config *cfg);

// chunksort //

static int	get_chunk_size(int size);
static void	push_chunk(t_stack **a, t_stack **b, int *limit, int chunk_size);
static void	push_chunks_to_b(t_stack **a, t_stack **b, int chunk_size);
static int	find_max_pos(t_stack *b);
static void	move_max_to_top(t_stack **b);
static void	restore_to_a(t_stack **a, t_stack **b);
void	chunk_sort(t_stack **a, t_stack **b);

// nearly_sorted //

static int	has_local_inversion(t_stack *a);
static void	correct_top(t_stack **a);
static void	rewind_stack(t_stack **a);
void	nearly_sorted_sort(t_stack **a);

// radix //

void	assign_indexes(t_stack *a);
int	stack_max_index(t_stack *a);
int	get_max_bits(t_stack *a);
void	radix_sort(t_stack **a, t_stack **b, t_bench *bench);
static int	*copy_values(t_stack *a);
static void	sort_array(int *arr, int size);
static int	find_index(int *sorted, int size, int value);
static int	get_bit(int index, int bit);
static void	process_bit(t_stack **a, t_stack **b, int bit, int size,
		t_bench *bench);
static void	restore_stack(t_stack **a, t_stack **b, t_bench *bench);

// flags //

void	init_config(t_config *cfg);
int	parse_flag(char *arg, t_config *cfg);
void	run_strategy(t_stack **a, t_stack **b, t_config *cfg);


#endif
