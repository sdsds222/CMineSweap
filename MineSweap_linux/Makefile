# 编译器和编译选项  
CC=gcc  
CFLAGS=-Wall  

# 编译目标文件生成可执行文件test  
minesweap: main.o Utils.o
	$(CC) $(CFLAGS) -o $@ $^
	rm -f main.o Utils.o
  
 
# 编译源文件生成目标文件  
main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@  
	
Utils.o: Utils.c
	$(CC) $(CFLAGS) -c $^ -o $@  
	
# 清除生成的目标文件和可执行文件  
clean:  
	rm -f main.o Utils.o
