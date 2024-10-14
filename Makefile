check:
	@clear
	@echo "Compilation ..."
	@g++ -std=c++20 *.cpp
	@echo "Running ..."
	@./a.out
	@rm a.out
	@echo "Done, Image saved !\n"