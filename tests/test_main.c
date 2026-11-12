#include "libft.h"
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int	g_fail = 0;

#define CHECK(cond) do { if (!(cond)) { g_fail++; \
	fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); } } while (0)

static int	sign(int x)
{
	return ((x > 0) - (x < 0));
}

static void	test_is_to(void)
{
	for (int c = -1; c < 256; c++)
	{
		CHECK(!!ft_isalpha(c) == !!isalpha(c));
		CHECK(!!ft_isdigit(c) == !!isdigit(c));
		CHECK(!!ft_isalnum(c) == !!isalnum(c));
		CHECK(!!ft_isascii(c) == !!isascii(c));
		CHECK(!!ft_isprint(c) == !!isprint(c));
		CHECK(ft_toupper(c) == toupper(c));
		CHECK(ft_tolower(c) == tolower(c));
	}
}

static void	test_atoi_itoa(void)
{
	const char	*in[] = {"0", "42", "  \t\n-123abc", "+7", "--1", "2147483647",
		"-2147483648", "", " + 1", NULL};
	int			nums[] = {0, 1, -1, 42, -42, INT_MAX, INT_MIN, 1000000};
	char		buf[32];
	char		*s;

	for (int i = 0; in[i]; i++)
		CHECK(ft_atoi(in[i]) == atoi(in[i]));
	for (size_t i = 0; i < sizeof(nums) / sizeof(*nums); i++)
	{
		snprintf(buf, sizeof(buf), "%d", nums[i]);
		s = ft_itoa(nums[i]);
		CHECK(s && strcmp(s, buf) == 0);
		free(s);
	}
}

static void	test_mem(void)
{
	char	a[32];
	char	b[32];
	char	*p;

	memset(a, 'x', sizeof(a));
	ft_memset(b, 'x', sizeof(b));
	CHECK(memcmp(a, b, sizeof(a)) == 0);
	ft_bzero(b, 10);
	CHECK(b[0] == 0 && b[9] == 0 && b[10] == 'x');
	strcpy(a, "0123456789");
	strcpy(b, "0123456789");
	ft_memmove(a + 2, a, 5);
	memmove(b + 2, b, 5);
	CHECK(strcmp(a, b) == 0);
	ft_memmove(a, a + 3, 5);
	memmove(b, b + 3, 5);
	CHECK(strcmp(a, b) == 0);
	CHECK(ft_memcpy(a, "hello", 6) == a && strcmp(a, "hello") == 0);
	p = "abc\0def";
	CHECK(ft_memchr(p, 'd', 7) == p + 4);
	CHECK(ft_memchr(p, 'z', 7) == NULL);
	CHECK(sign(ft_memcmp("ab\x80", "ab\x01", 3)) == sign(memcmp("ab\x80", "ab\x01", 3)));
	CHECK(ft_memcmp("abc", "abd", 2) == 0);
	p = ft_calloc(4, 4);
	CHECK(p && memcmp(p, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16) == 0);
	free(p);
	p = ft_calloc(0, 0);
	CHECK(p != NULL);
	free(p);
	CHECK(ft_calloc(SIZE_MAX, 2) == NULL);
}

static void	test_str_basic(void)
{
	char		dst[16];
	const char	*s = "hello world";

	CHECK(ft_strlen("") == 0 && ft_strlen(s) == 11);
	CHECK(ft_strchr(s, 'o') == strchr(s, 'o'));
	CHECK(ft_strchr(s, '\0') == strchr(s, '\0'));
	CHECK(ft_strchr(s, 'z') == NULL);
	CHECK(ft_strrchr(s, 'o') == strrchr(s, 'o'));
	CHECK(ft_strrchr(s, '\0') == strrchr(s, '\0'));
	CHECK(ft_strrchr(s, 'z') == NULL);
	CHECK(ft_strncmp("abc", "abd", 2) == 0);
	CHECK(sign(ft_strncmp("abc", "abd", 3)) == sign(strncmp("abc", "abd", 3)));
	CHECK(sign(ft_strncmp("a\x80", "a\x01", 5)) == sign(strncmp("a\x80", "a\x01", 5)));
	CHECK(ft_strncmp("abc", "abc", 100) == 0);
	CHECK(ft_strncmp("abc", "ab", 0) == 0);
	CHECK(ft_strlcpy(dst, s, sizeof(dst)) == 11 && strcmp(dst, s) == 0);
	CHECK(ft_strlcpy(dst, s, 4) == 11 && strcmp(dst, "hel") == 0);
	CHECK(ft_strlcpy(dst, s, 0) == 11);
	strcpy(dst, "abc");
	CHECK(ft_strlcat(dst, "defgh", 6) == 8 && strcmp(dst, "abcde") == 0);
	CHECK(ft_strlcat(dst, "xyz", 2) == 5);
	CHECK(ft_strlcat(dst, "xyz", 0) == 3);
	CHECK(ft_strnstr(s, "world", 11) == s + 6);
	CHECK(ft_strnstr(s, "world", 10) == NULL);
	CHECK(ft_strnstr(s, "", 0) == s);
	CHECK(ft_strnstr(s, "lo", 5) == s + 3);
	CHECK(ft_strnstr(s, "lo", 4) == NULL);
}

/* Bounded functions must not read past n/len bytes (non-NUL-terminated
** heap buffers let ASan catch any out-of-bounds read). */
static void	test_bounded_reads(void)
{
	char	*h;

	h = malloc(5);
	if (!h)
		return ;
	memcpy(h, "hello", 5);
	CHECK(ft_strnstr(h, "xyz", 5) == NULL);
	CHECK(ft_strnstr(h, "llo", 5) == h + 2);
	CHECK(ft_strnstr(h, "lloz", 5) == NULL);
	CHECK(ft_strncmp(h, "hello", 5) == 0);
	CHECK(ft_memchr(h, 'z', 5) == NULL);
	CHECK(ft_memcmp(h, "hello", 5) == 0);
	free(h);
}

static char	upper_idx(unsigned int i, char c)
{
	return (i % 2 ? ft_toupper(c) : c);
}

static void	upper_ptr(unsigned int i, char *c)
{
	(void)i;
	*c = ft_toupper(*c);
}

static void	test_str_alloc(void)
{
	char	*p;
	char	buf[8];

	p = ft_strdup("dup");
	CHECK(p && strcmp(p, "dup") == 0);
	free(p);
	p = ft_substr("hello", 1, 3);
	CHECK(p && strcmp(p, "ell") == 0);
	free(p);
	p = ft_substr("hello", 10, 3);
	CHECK(p && strcmp(p, "") == 0);
	free(p);
	p = ft_substr("hello", 2, 100);
	CHECK(p && strcmp(p, "llo") == 0);
	free(p);
	p = ft_strjoin("foo", "bar");
	CHECK(p && strcmp(p, "foobar") == 0);
	free(p);
	p = ft_strtrim("  xx hi xx  ", " x");
	CHECK(p && strcmp(p, "hi") == 0);
	free(p);
	p = ft_strtrim("xxxx", "x");
	CHECK(p && strcmp(p, "") == 0);
	free(p);
	p = ft_strmapi("abcd", upper_idx);
	CHECK(p && strcmp(p, "aBcD") == 0);
	free(p);
	strcpy(buf, "abc");
	ft_striteri(buf, upper_ptr);
	CHECK(strcmp(buf, "ABC") == 0);
}

static void	free_split(char **v)
{
	for (int i = 0; v && v[i]; i++)
		free(v[i]);
	free(v);
}

static void	test_split(void)
{
	char	**v;

	v = ft_split("  a bb   ccc ", ' ');
	CHECK(v && strcmp(v[0], "a") == 0 && strcmp(v[1], "bb") == 0
		&& strcmp(v[2], "ccc") == 0 && v[3] == NULL);
	free_split(v);
	v = ft_split("", ' ');
	CHECK(v && v[0] == NULL);
	free_split(v);
	v = ft_split("    ", ' ');
	CHECK(v && v[0] == NULL);
	free_split(v);
	v = ft_split("abc", '\0');
	CHECK(v && strcmp(v[0], "abc") == 0 && v[1] == NULL);
	free_split(v);
	CHECK(ft_split(NULL, ' ') == NULL);
}

static void	test_put(void)
{
	char	buf[64];
	int		fds[2];
	ssize_t	n;

	if (pipe(fds) != 0)
	{
		CHECK(0);
		return ;
	}
	ft_putchar_fd('a', fds[1]);
	ft_putstr_fd("bc", fds[1]);
	ft_putendl_fd("d", fds[1]);
	ft_putnbr_fd(INT_MIN, fds[1]);
	ft_putnbr_fd(0, fds[1]);
	ft_putnbr_fd(-42, fds[1]);
	ft_putnbr_fd(INT_MAX, fds[1]);
	close(fds[1]);
	n = read(fds[0], buf, sizeof(buf) - 1);
	close(fds[0]);
	buf[n < 0 ? 0 : n] = '\0';
	CHECK(strcmp(buf, "abcd\n-21474836480-422147483647") == 0);
}

#ifdef TEST_BONUS

static void	del_content(void *p)
{
	free(p);
}

static void	*dup_content(void *p)
{
	return (ft_strdup(p));
}

static void	count_iter(void *p)
{
	(void)p;
}

static void	test_lst(void)
{
	t_list	*lst;
	t_list	*mapped;

	lst = NULL;
	CHECK(ft_lstsize(lst) == 0 && ft_lstlast(lst) == NULL);
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("b")));
	ft_lstadd_front(&lst, ft_lstnew(ft_strdup("a")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("c")));
	CHECK(ft_lstsize(lst) == 3);
	CHECK(strcmp(lst->content, "a") == 0);
	CHECK(strcmp(ft_lstlast(lst)->content, "c") == 0);
	ft_lstiter(lst, count_iter);
	mapped = ft_lstmap(lst, dup_content, del_content);
	CHECK(mapped && ft_lstsize(mapped) == 3
		&& strcmp(mapped->next->content, "b") == 0);
	CHECK(mapped->content != lst->content);
	ft_lstclear(&mapped, del_content);
	CHECK(mapped == NULL);
	ft_lstclear(&lst, del_content);
	CHECK(lst == NULL);
}
#endif

int	main(void)
{
	test_is_to();
	test_atoi_itoa();
	test_mem();
	test_str_basic();
	test_bounded_reads();
	test_str_alloc();
	test_split();
	test_put();
#ifdef TEST_BONUS
	test_lst();
#endif
	if (g_fail)
	{
		fprintf(stderr, "%d check(s) failed\n", g_fail);
		return (1);
	}
	printf("All tests passed\n");
	return (0);
}
