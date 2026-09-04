# 📚 libft — C standard library functions, reimplemented from scratch

![language](https://img.shields.io/badge/language-C-blue.svg)
![norm](https://img.shields.io/badge/42-norminette-success.svg)
![flags](https://img.shields.io/badge/build-Wall%20Wextra%20Werror-brightgreen.svg)
![platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey.svg)

> **TL;DR (EN):** A static C library written from scratch as the first [42](https://42tokyo.jp/)
> project. It reimplements **43 functions** — 34 mandatory (libc string/memory/conversion
> helpers plus `ft_split`, `ft_itoa`, `ft_strtrim`, …) and 9 bonus singly-linked-list
> operations (`ft_lst*`) — in **1,362 lines across 44 files**, grouped into six
> functional directories under `src/`. The only external calls the archive makes are
> `malloc`, `free` and `write(2)`; every other dependency is another function in this
> library. Builds with `-Wall -Wextra -Werror` with zero warnings and passes norminette
> on all 44 files.

本リポジトリは **C 標準ライブラリの主要関数を一から再実装した静的ライブラリ** `libft.a` です（42 の rank00 課題）。
mandatory 34 関数と bonus の連結リスト操作 9 関数、あわせて 43 関数を実装しています。
libc の文字列・メモリ関数には一切依存せず、自作関数どうしを組み合わせて構成しているのが方針上の中心です。

---

## 実装範囲

課題テンプレートは 43 ファイルの平坦配置が普通ですが、探しにくいため役割ごとに 6 ディレクトリへ分けました。
`Makefile` も `FT_IS_DIR` 〜 `FT_TO_DIR` の変数で同じ分類を持ち、`SRCS` の並びがそのまま目次になります。

| ディレクトリ | 本数 | 関数 |
| --- | --- | --- |
| `src/ft_is/` | 5 | `ft_isalpha` `ft_isdigit` `ft_isalnum` `ft_isascii` `ft_isprint` |
| `src/ft_to/` | 4 | `ft_atoi` `ft_itoa` `ft_toupper` `ft_tolower` |
| `src/ft_mem/` | 7 | `ft_memset` `ft_bzero` `ft_memcpy` `ft_memmove` `ft_memchr` `ft_memcmp` `ft_calloc` |
| `src/ft_put/` | 4 | `ft_putchar_fd` `ft_putstr_fd` `ft_putendl_fd` `ft_putnbr_fd` |
| `src/ft_str/` | 14 | `ft_strlen` `ft_strlcpy` `ft_strlcat` `ft_strchr` `ft_strrchr` `ft_strncmp` `ft_strnstr` `ft_strdup` `ft_substr` `ft_strjoin` `ft_strtrim` `ft_split` `ft_strmapi` `ft_striteri` |
| `src/ft_lst/` (bonus) | 9 | `ft_lstnew` `ft_lstadd_front` `ft_lstadd_back` `ft_lstsize` `ft_lstlast` `ft_lstdelone` `ft_lstclear` `ft_lstiter` `ft_lstmap` |

公開ヘッダは `libft.h` 1 本のみです。bonus は `_bonus.c` サフィックスで命名し、`Makefile` 側で
`SRCS`（34 本）と `BONUS`（9 本）を別変数に分けています。`all` は mandatory だけを、
`bonus` は両方を 1 つの `libft.a` にまとめます（42 の bonus 分離要件への対応）。

連結リストは単方向で、ノードは `content` と `next` だけを持ちます。

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```

---

## ビルド・使い方

```bash
make            # mandatory 34 関数のみで libft.a を生成
make bonus      # mandatory + bonus の計 43 関数で libft.a を生成
make clean      # .o のみ削除
make fclean     # .o と libft.a を削除
make re         # fclean してから all を再ビルド
```

`CFLAGS = -Wall -Wextra -Werror -I.`、暗黙ルールで `.c` → `.o`、`ar rcs` でアーカイブ化します。

生成されたアーカイブに含まれる公開シンボル数は、mandatory が 34、bonus 込みが 43 で、
余分な外部シンボルはありません（内部ヘルパはすべて `static`）。

```console
$ make && nm libft.a | grep ' T ' | wc -l
34
$ make fclean && make bonus && nm libft.a | grep ' T ' | wc -l
43
```

呼び出し側からは `libft.h` を include して `libft.a` をリンクします。
以下の `demo.c` は本リポジトリには含まれません（動作確認用にその場で書いたもの）。

```c
#include "libft.h"
#include <stdio.h>

static void	del_content(void *p)
{
	free(p);
}

int	main(void)
{
	char	**words;
	t_list	*lst;
	int		i;

	ft_putendl_fd("putendl_fd -> write(2) on fd 1", 1);
	words = ft_split("  42   Tokyo  libft ", ' ');
	i = -1;
	while (words[++i])
		printf("split[%d]      = \"%s\"\n", i, words[i]);
	printf("strtrim       = \"%s\"\n", ft_strtrim("<<<norminette>>>", "<>"));
	printf("atoi          = %d\n", ft_atoi("  -9885abc"));
	printf("itoa(INT_MIN) = \"%s\"\n", ft_itoa(-2147483648));
	lst = ft_lstnew(ft_strdup("head"));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("tail")));
	printf("lstsize       = %d\n", ft_lstsize(lst));
	printf("lstlast       = \"%s\"\n", (char *)ft_lstlast(lst)->content);
	ft_lstclear(&lst, del_content);
	printf("lstclear      = %p\n", (void *)lst);
	return (0);
}
```

```console
$ make bonus
$ cc -Wall -Wextra -Werror -I. demo.c libft.a -o demo && ./demo
putendl_fd -> write(2) on fd 1
split[0]      = "42"
split[1]      = "Tokyo"
split[2]      = "libft"
strtrim       = "norminette"
atoi          = -9885
itoa(INT_MIN) = "-2147483648"
lstsize       = 2
lstlast       = "tail"
lstclear      = 0x0
```

---

## 実装のポイント

### 外部依存を malloc / free / write の 3 つに閉じる

libc の文字列・メモリ関数は一切呼ばず、必要な処理は自作関数どうしで組み立てています。
`ft_bzero` は `ft_memset` に完全委譲し、`ft_strdup` / `ft_strjoin` / `ft_strtrim` / `ft_substr` は
コピーに `ft_memcpy` を、`ft_split` は語の切り出しに `ft_substr` を、`ft_strtrim` は集合判定に
`ft_strchr` を使います。`write(2)` を直接叩くのは `ft_putchar_fd` と `ft_putstr_fd` の 2 ファイルだけで、
`ft_putendl_fd` / `ft_putnbr_fd` はその 2 つの上に載っています。

結果として、アーカイブの未解決シンボルは 15 個、うち libc 側は 3 つだけになります
（残り 12 個はすべて libft 内の関数）。

```console
$ nm -u libft.a | grep '^_' | sort -u | grep -v '^_ft_'
_free
_malloc
_write
```

### エッジケースに明示的に対処した 3 箇所

- **`ft_memmove` の重なり領域** — `dst` と `src` のアドレス大小で走査方向を切り替えます。`dst < src` なら前方、そうでなければ `while (len--)` の逆順コピーで、コピー元を読む前に潰す事故を避けます。`ft_memcpy` は前方コピーのみで、標準の契約どおり役割を分けています。
- **`ft_calloc` の乗算オーバーフロー** — `count * size` を計算する前に `if (count && size > SIZE_MAX / count) return (NULL);` で弾きます。乗算を除算に置き換えて桁あふれ前に判定する定石で、このためだけに `<stdint.h>` を include しています。
- **`ft_putnbr_fd` の `INT_MIN`** — `-2147483648` は符号反転すると `int` に収まらないため、再帰に入る前に文字列リテラルで特別処理します。それ以外は `n / 10` の再帰による桁分解です。

### 確保の回数を減らす設計

- **`ft_split`** — 「語数を数える前走査 → `malloc` 1 回 → 切り出し走査」の 2 パス構成で、`realloc` による再確保が起きません。全体 O(n)、追加確保は語数 + 1 個のポインタ配列と各語の文字列です。78 行で最大の関数のため、`ft_countword` / `get_word_len` / `free_lst` の 3 つの `static` ヘルパに分割しています。
- **`ft_itoa`** — `static ft_number_size` で 10 で割りながら桁数を先に求め（O(log₁₀ n)）、確保したバッファの末尾から `n % 10` で 1 桁ずつ埋めます。

### 部分構築リークを避ける `ft_lstmap`

途中の `ft_lstnew` が失敗した場合、`ft_lstclear(&new, del)` で構築済みノードを `del` 付きで全解放してから
`NULL` を返します。`f` が確保した中身ごと巻き戻さないと、呼び出し側から到達不能なメモリが残るためです。
`ft_lstclear` 自身も `next` を退避してから `ft_lstdelone` で解放し、解放済みノードを辿らないようにしています。

### ロケール非依存の `ft_is*`

`<ctype.h>` を使わず ASCII コードを直接比較しています（例: `ft_isprint` は `32 <= c && c <= 126`、
`ft_isascii` は `0 <= c && c <= 127`）。`ft_toupper` / `ft_tolower` も `'a' - 'A'` の差分を加減算するだけです。

### 計算量

素直な線形走査が中心で、意図的に定数倍を削る最適化はしていません。走査系（`ft_strlen`
`ft_strchr` `ft_memchr` `ft_memcmp` `ft_memmove` など）と連結リスト操作は O(n)、
`ft_itoa` / `ft_putnbr_fd` は O(log₁₀ n)、`ft_lstadd_front` のみ O(1) です。
例外は 2 つあります。`ft_strnstr` は開始位置ごとに照合する二重ループで最悪 O(n·m)（KMP 等は未使用）、
`ft_lstadd_back` は末尾ポインタを持たないため毎回終端まで辿る O(n) です。

---

## 検証したこと

**本リポジトリに単体テストも CI も含まれていません。** 実際に確認したのは以下の 3 点だけです
（Apple clang 21.0.0 / arm64 macOS）。

| 項目 | 結果 |
| --- | --- |
| `-Wall -Wextra -Werror` でのビルド | `make` / `make bonus` とも警告ゼロ、exit 0 |
| norminette 3.3.59 | `libft.h` + `src/` 配下の全 44 ファイルが `OK!`、Error 0 件 |
| リンクと実行 | 上記 `demo.c` を `libft.a` にリンクして期待どおりの出力 |

norminette は 42 のコーディング規約チェッカで、関数 25 行以内・変数宣言と処理の分離・引数 4 つまで・
`for` / `while` 以外の制御構文の制限などを検査します。

---

## 既知の制限

学習成果物として提出時点のまま公開しているため、以下は未修整です。

- **`ft_split` の確保失敗パスが不完全** — `if (!lst[i]) free_lst(lst, i - 1);` に `return` がなく、解放後もループが続きます。添字も `i - 1` とずれています。`malloc` 成功時の挙動には影響しませんが、失敗時は正しく巻き戻りません。
- **`ft_atoi` はオーバーフローを検査しない** — 桁あふれ時の戻り値は未定義相当です（`ft_calloc` の検査とは対照的に、ここは未対応）。
- **`libft.h` が `ft_striteri` / `ft_putendl_fd` / `ft_putnbr_fd` を二重に宣言している** — C としては無害ですが冗長です。
- **`ft_atoi.c` と `ft_strrchr.c` の末尾に、コメントアウトされた動作確認用 `main()` が残っている。**
- `.gitignore` がないため、`make` 後の `.o` と `libft.a` が untracked として現れます。

---

## 学んだこと

- **重なり領域のセマンティクスが `memcpy` と `memmove` を分けている理由。** 「速いほう / 安全なほう」ではなく、`memcpy` は領域が重ならないことを呼び出し側の契約として要求する、という API 設計の話だと理解しました。方向分岐を自分で書いて初めて、2 つの関数が別々に存在する意味が腑に落ちます。
- **サイズ計算そのものが攻撃面になる。** `count * size` は `malloc` に渡る前に静かに折り返し、実際より小さい領域が確保されてヒープオーバーフローにつながります。乗算を除算に置き換えて事前に弾く定石を `ft_calloc` で覚えました。
- **2 の補数の非対称性。** `INT_MIN` だけ `-n` が `int` に収まらないため、符号反転を前提にしたコードは必ずここで壊れます。`ft_putnbr_fd` と `ft_itoa` の両方で、符号処理を再帰・ループに入る前に済ませる形に落ち着きました。
- **所有権をコールバックで表現する。** `ft_lstclear` / `ft_lstdelone` / `ft_lstmap` が `del` を引数で取るのは、リストがノードは所有するが `content` は所有しないためです。C では所有権を型に書けないぶん、規約が関数シグネチャに現れるのだと理解しました。
- **静的ライブラリのリンク単位とシンボルの可視性。** `ar rcs` のアーカイブが `.o` 単位でリンクされること、`static` ヘルパが外部シンボルに出ないことを `nm` で確かめました。公開シンボルがちょうど 43 個で止まるのはその結果です。以降の 42 課題はすべてこのライブラリの上に載るため、`write(2)` と `malloc` を呼ぶ場所を数えられるほど少なく保てたことが、そのまま後工程の読みやすさに効きました。

---

*This project was created as part of the 42 curriculum.*
