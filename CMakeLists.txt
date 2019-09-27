cmake_minimum_required(VERSION 3.10)
project(lem-in C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

include_directories(inc)

include_directories(libft/inc)

include_directories(libft/ft_printf/inc)

add_executable(lem-in src/main.c
        ./src/helper_f_find_vl_path.c
        ./src/run_ants.c
        ./src/read_data.c
        ./src/ft_free_mem.c
        ./src/main.c
        ./src/hlpr_f_try_read.c
        ./src/hlp_f_run_ants.c
        ./src/try_read.c
        ./src/find_valid_path.c
        ./libft/src/ft_lstcnt.c
        ./libft/src/ft_strdel.c
        ./libft/src/get_next_line.c
        ./libft/src/ft_lstrvrs.c
        ./libft/src/ft_strlen.c
        ./libft/src/ft_strcmp.c
        ./libft/src/ft_isdigit.c
        ./libft/src/ft_lstmap.c
        ./libft/src/ft_memset.c
        ./libft/src/ft_striter.c
        ./libft/src/ft_strjoin.c
        ./libft/src/ft_memdel.c
        ./libft/src/ft_putchar_fd.c
        ./libft/src/ft_strtrim.c
        ./libft/src/ft_lstnew.c
        ./libft/src/ft_strstr.c
        ./libft/src/ft_lstadd.c
        ./libft/src/ft_toupper.c
        ./libft/src/ft_memcmp.c
        ./libft/src/ft_strncpy.c
        ./libft/src/ft_putendl.c
        ./libft/src/ft_putendl_fd.c
        ./libft/src/ft_isalpha.c
        ./libft/src/ft_strcpy.c
        ./libft/src/ft_lstdelone.c
        ./libft/src/ft_striteri.c
        ./libft/src/ft_lstiter.c
        ./libft/src/ft_lstdel.c
        ./libft/src/ft_strdup.c
        ./libft/src/ft_putnbr_fd.c
        ./libft/src/ft_strmapi.c
        ./libft/src/ft_memcpy.c
        ./libft/src/ft_putstr_fd.c
        ./libft/src/ft_strsub.c
        ./libft/src/ft_isspace.c
        ./libft/src/ft_strnstr.c
        ./libft/src/ft_strequ.c
        ./libft/src/ft_strncat.c
        ./libft/src/ft_putchar.c
        ./libft/src/ft_isprint.c
        ./libft/src/ft_strrchr.c
        ./libft/src/ft_strcat.c
        ./libft/src/ft_strlcat.c
        ./libft/src/ft_strchr.c
        ./libft/src/ft_strclr.c
        ./libft/src/ft_bzero.c
        ./libft/src/ft_putnbr.c
        ./libft/src/ft_atoi.c
        ./libft/src/ft_putstr.c
        ./libft/src/ft_memalloc.c
        ./libft/src/ft_strsplit.c
        ./libft/src/ft_isascii.c
        ./libft/src/ft_itoa.c
        ./libft/src/ft_memmove.c
        ./libft/src/ft_lstaddend.c
        ./libft/src/ft_tolower.c
        ./libft/src/ft_isalnum.c
        ./libft/src/ft_sqrt.c
        ./libft/src/ft_strmap.c
        ./libft/src/ft_strnequ.c
        ./libft/src/ft_strnew.c
        ./libft/src/ft_memchr.c
        ./libft/src/ft_memccpy.c
        ./libft/src/ft_strncmp.c
        ./libft/inc/libft.h
        ./libft/ft_printf/src/ft_outp_float.c
        ./libft/ft_printf/src/fns_for_fl.c
        ./libft/ft_printf/src/fns_for_ddgt.c
        ./libft/ft_printf/src/if_flgs_o_x_b.c
        ./libft/ft_printf/src/itoa_printf_o_x_b.c
        ./libft/ft_printf/src/ft_for_pr_cca_ssa.c
        ./libft/ft_printf/src/ft_determ_argc.c
        ./libft/ft_printf/src/ft_printf.c
        ./libft/ft_printf/src/ft_print_pct.c
        ./libft/ft_printf/src/ft_cnt_i_d_u_ua_c.c
        ./libft/ft_printf/src/itoa_a_e_f_g.c
        ./libft/ft_printf/src/print_cca_ssa.c
        ./libft/ft_printf/src/fts_f_output_dgt.c
        ./libft/ft_printf/src/ft_with_flags.c
        ./libft/ft_printf/src/init_arr.c
        ./libft/ft_printf/src/cnt_o_x_b.c
        ./libft/ft_printf/src/ft_determine_flgs.c
        ./libft/ft_printf/src/ft_for_print_args.c
        ./libft/ft_printf/src/itoa_printf.c
        ./libft/ft_printf/src/ft_f_prn_unicd.c
        ./libft/ft_printf/src/lib_printf.c
        ./libft/ft_printf/src/fill_struct.c
        ./libft/ft_printf/src/determ_types.c
        ./libft/ft_printf/src/print_unicode.c
        ./libft/ft_printf/inc/libftprintf.h
        ./inc/libftlemin.h helper_f_find_vl_path2.c)
