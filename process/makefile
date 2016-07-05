POJ1=fork
POJ2=signal
POJ3=pipe
POJ4=popen
POJ5=fifo
CC=gcc

$(POJ1): 
	@$(CC) $(LDFLAGS) -o $@ fork.c	
	@./fork
	@rm fork
$(POJ2):
	@$(CC) $(LDFLAGS) -o $@ signal.c	
	@./signal
	@rm signal
$(POJ3):
	@$(CC) $(LDFLAGS) -o $@ pipe.c	
	@./pipe
	@rm pipe	
$(POJ4):
	@$(CC) $(LDFLAGS) -o $@ popen.c	
	@./popen
	@rm popen
$(POJ5):
	@$(CC) $(LDFLAGS) -o fifo1 fifo1.c	
	@$(CC) $(LDFLAGS) -o fifo2 fifo2.c	
	@./fifo2 & # 这里只能放到后台,类似于 服务器
	@./fifo1
	@rm fifo1 fifo2
	
clean:
	@rm fork signal pipe popen fifo1 fifo2
