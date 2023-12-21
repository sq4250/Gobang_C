ROOT := $(shell pwd)

SUBDIR := $(ROOT)/Core/Src $(ROOT)/Core/Src/func

OUTPUT := $(ROOT)/.build
TARGET := $(ROOT)/Gobang

INCS := -I $(ROOT)/Core/Inc
SRCS := $(foreach dir, $(SUBDIR), $(wildcard $(dir)/*.c))
OBJS := $(patsubst $(ROOT)/%.c, $(OUTPUT)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

$(TARGET) : $(OBJS)
		@echo linking...
		@gcc $(OBJS) -o $@
		@echo complete!

$(OUTPUT)/%.o : $(ROOT)/%.c 
		@echo compile...
		@mkdir -p $(dir $@)
		@gcc -MMD -MP -c $(INCS) $< -o $@

.PHONY : clean

clean :
		@echo try to clean...
		@rm -r $(OUTPUT)
		@rm $(TARGET)
		@echo complete!

-include $(DEPS)

.PHONY : run

run :
		@$(TARGET)
