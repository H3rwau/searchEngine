CC :=g++
ELF :=offline
DIR_OBJS = ../../obj
DIR_BIN = ../../bin
DIR_LOG = ../../log
#需要调用的链接库
#每行用\来结尾
LIBS    :=  -llog4cpp -pthread
# 头文件路径
INCLUDE :=  -I
# 链接库路径
LDFLAGS :=  -L
dirs := $(DIR_OBJS) $(DIR_BIN) $(DIR_LOG)
srcs =$(wildcard *.cc)
objs =$(patsubst %.cc,%.o,$(srcs))

objs :=$(addprefix $(DIR_OBJS)/,$(objs))
ELF :=$(addprefix $(DIR_BIN)/,$(ELF))


all: $(dirs) $(ELF)
$(dirs):
	mkdir $@
$(ELF):$(objs)
	$(CC) $^  -g -o $@ $(LIBS)
$(DIR_OBJS)/%.o:%.cc
	$(CC) $^  -g -o $@ -c $(LIBS)
.PHONY: clean rebuild
rebuild:clean 
clean:
	rm -f $(objs)
	rm  $(ELF)
