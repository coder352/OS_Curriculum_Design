.PHONY: build clean

lx:
	@g++ -g -masm=intel -o JD.out lx.cpp
	@./JD.out
	@rm JD.out

pt:
	@make -C ./TestMVC/src build

philosopher:
	@make -C ./Dinner/src build

