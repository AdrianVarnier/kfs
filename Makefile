# ===== TARGET =====
NAME    = kfs

# ===== SOURCES =====
SRC_C   =	kernel.c \
			terminal.c \
			utils.c \
			keyboard.c \
			printk.c \
			cursor.c \
			gdt.c \

SRC_S   =	boot.s \
			gdt_flush.s \

# ===== DIRECTORIES =====
SRC_DIR = src
INC_DIR = inc
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
all: $(OBJ_DIR) $(DEP_DIR) iso

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

iso: $(NAME)
	rm -rf isodir
	mkdir -p isodir/boot/grub
	cp $(NAME) isodir/boot/$(NAME)
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(NAME).iso isodir

qemu:
	qemu-system-i386 -cdrom $(NAME).iso

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)$(dir $<)
	@mkdir -p $(DEP_DIR)$(dir $<)
	$(CC) $(CFLAGS) -I $(INC_DIR) -MMD -MP -MF $(DEP_DIR)$*.d -c $< -o $@

$(OBJ_DIR)%.o: %.s
	@mkdir -p $(OBJ_DIR)$(dir $<)
	$(AS) $(ASFLAGS) $< -o $@

# ===== CLEAN =====
clean: clean_dep clean_obj clean_obj_iso

cclean: clean clean_bin

fclean: clean clean_bin clean_iso

re: fclean clean_iso all

clean_dep:
	rm -rf $(DEP_DIR)

clean_obj:
	rm -rf $(OBJ_DIR)

clean_obj_iso:
	rm -rf isodir

clean_bin:
	rm -f $(NAME)

clean_iso:
	rm -rf $(NAME).iso

# ===== DEPS =====

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DEP_DIR):
	mkdir -p $(DEP_DIR)

-include $(DEP)

.PHONY: all clean fclean re
