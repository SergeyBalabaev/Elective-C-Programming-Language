CXX=gcc
DFLAGS=-Wall -g -lm -Werror
RFLAGS= -lm -O3
OBJDIR = obj
SRCDIR = src
OBJS = $(OBJDIR)/zip_f.o
OBJS += $(OBJDIR)/arch_logic.o
OBJS += $(OBJDIR)/file_In_out.o
OBJS += $(OBJDIR)/information.o
OBJS += $(OBJDIR)/math_func.o

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CXX) -c $< -o $@

all: clean $(OBJS)
	$(CXX) $(OBJS) $(RFLAGS) -o zip_f

debug: clean $(OBJS)
	$(CXX) $(OBJS) $(DFLAGS) -o zip_f
    	
clean:
	rm -f $(OBJDIR)/*.o
