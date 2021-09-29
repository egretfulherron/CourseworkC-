

build:  obj lib link

lib: obj next

obj:
	g++ -c BST.cpp BST.hpp

next:
	g++ BST.o -shared -o BST.lib   
link :
	g++ PartA.cpp BST.lib -o symbol_table

clean: cleanout cleantxt cleanlib

cleanout:
	rm symbol_table
	rm BST.o


cleantxt:
	rm tree.txt
	rm identifiers.txt
cleanlib:
	rm BST.lib





	