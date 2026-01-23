# ===== TARGET =====
NAME    = kfs

# ===== SOURCES =====
SRC_C   = kernel.c
SRC_S   = boot.s

# ===== DIRECTORIES =====
SRC_DIR =
INC_DIR =
OBJ_DIR = obj/
DEP_DIR = dep/

# ===== FILES =====
OBJ_C   = $(addprefix $(OBJ_DIR), $(SRC_C:.c=.o))
OBJ_S   = $(addprefix $(OBJ_DIR), $(SRC_S:.s=.o))
OBJ     = $(OBJ_C) $(OBJ_S)

DEP     = $(addprefix $(DEP_DIR), $(SRC_C:.c=.d))


# ===== VPATH =====
vpath %.c $(SRC_DIR)
vpath %.s $(SRC_DIR)
vpath %.h $(INC_DIR)

# ===== TOOLCHAIN =====
CC      = i686-elf-gcc
AS      = i686-elf-as

# ===== FLAGS =====
CFLAGS  = -std=gnu99 -O2 -Wall -Wextra -Werror -fno-builtin -fno-stack-protector -ffreestanding -nostdlib -nodefaultlibs
ASFLAGS =
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -nodefaultlibs
LIBS    = -lgcc

# ===== RULES =====
all: $(OBJ_DIR) $(DEP_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)$(dir $<)
	@mkdir -p $(DEP_DIR)$(dir $<)
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)$*.d -c $< -o $@

$(OBJ_DIR)%.o: %.s
	@mkdir -p $(OBJ_DIR)$(dir $<)
	$(AS) $(ASFLAGS) $< -o $@

# ===== CLEAN =====
clean: clean_dep clean_obj

fclean: clean clean_bin

re: fclean all

clean_dep:
	rm -rf $(DEP_DIR)

clean_obj:
	rm -rf $(OBJ_DIR)

clean_bin:
	rm -f $(NAME)

# ===== DEPS =====

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DEP_DIR):
	mkdir -p $(DEP_DIR)

-include $(DEP)

.PHONY: all clean fclean re
