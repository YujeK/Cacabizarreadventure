NAME		:=	doom_editor
SRC			:=  main.c \
				check_key_presses.c \
				check_map_convexity.c \
				check_map_geometry.c \
				check_map_intersections.c \
				check_player_position.c \
				check_sprite_position.c \
				draw_line.c \
				draw_rectangle.c \
				draw_window.c \
				edge_ops.c \
				fd_operations.c \
				fd_operations2.c \
				fd_operations3.c \
				free_map.c \
				geometry.c \
				geometry2.c \
				get_next_line.c \
				init_wind.c \
				initialize_new_map.c \
				inside_sector.c \
				mouse_button_events.c \
				no_boxed_sector.c \
				read_fd.c \
				read_fd2.c \
				remove_duped_vertex.c \
				sdl_pixels.c \
				sector_ops.c \
				sector_ops2.c \
				sector_ops3.c \
				vertex_move.c \
				vertex_ops.c
# directories :
OBJDIR 		:=	objs
INCDIR  	:=	includes
# LIBFT
VPATH		:= ./srcs:
LFT_NAME	:=	libft.a
LFT_PATH	:=	./libft
LFT_LIB		:=	-L $(LFT_PATH) -lft
LFT_INC		:=	-I $(LFT_PATH)
LFT_RULE	:=	$(LFT_PATH)/$(LFT_NAME)
# SDL
LSDL_LIB	:=	$(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LSDL_INC	:=	$(shell sdl2-config --cflags)
# **************************************************************************** #
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.d))
LIB			:=	$(LFT_LIB) $(LSDL_LIB)
INC			:=	-I $(INCDIR) $(LFT_INC) $(LSDL_INC)
# **************************************************************************** #
CC			:=	clang
CFLAGS		:=  -Wall -Wextra -Werror
# **************************************************************************** #
all : $(NAME)
.PHONY: all
$(NAME): $(OBJ) $(LFT_RULE)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC) $(LIB)
	@echo "\033[1;34;2m <(^o^)> - MAMA HE LIMPIADO MI DORMITORIO PERFECTAMENTE ~\033[0m"
	@echo "\033[0;31;3m                        (ALL RULE DONE)                               ~ (__)=3 ~\033[0m"
-include $(DEP)
$(LFT_RULE):
	@$(MAKE) -C $(LFT_PATH)/
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir $(OBJDIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) -MMD -c -o $@ $< $(INC)

clean :
	@$(MAKE) -C $(LFT_PATH) clean
	@rm -f $(OBJ)
	@rm -f $(DEP)
	@echo "\033[1;33;2m <(^o^)> - MAMA HE COMIDO TODAS LAS PATATAS, PUEDO JUGAR A SMASHBROS ? \033[0m"
	@echo "\033[0;31;3m                        (CLEAN RULE DONE)                             ~ (__)=3 ~ \033[0m"
.PHONY: clean
fclean : clean
	@$(MAKE) -C $(LFT_PATH) fclean
	@rm -f $(NAME)
	@echo "\033[1;31;2m J^_^L - SEGURO MI PEQUEÑITO SEBASTIAN, PERO LIMPIES TU CUARTO ANTES ~\033[0m"
	@echo "\033[0;31;3m                        (FCLEAN RULE DONE)                            ~ (__)=3  ~\033[0m"
.PHONY: fclean
re : fclean all
	@echo "\033[0;35;2m J^_^L - MUY BIEN, LAVAS LOS PLATOS AHORA ~"
	@echo "\033[0;31;3m                        (RE RULE DONE)                                ~ (__)=3  ~\033[0m"
.PHONY: re
