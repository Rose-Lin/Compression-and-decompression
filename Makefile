puff :: forest.o forest_node.o huff_tree_node.o llist.o llist_node.o puff.o
	gcc -o puff puff.o forest.o forest_node.o huff_tree_node.o llist.o llist_node.o

puff.o: forest.h forest_node.h huff_tree_node.h puff.c llist_node.h
	gcc -c puff.c

huff: forest.o forest_node.o huff_tree_node.o llist.o llist_node.o huff.o
	gcc -o huff huff.o forest.o forest_node.o huff_tree_node.o llist.o llist_node.o

huff.o: forest.h forest_node.h huff_tree_node.h huff.c llist_node.h
	gcc -c huff.c

forest.o: forest.h forest.c forest_node.h
	gcc -c forest.c

forest_node.o: forest_node.h forest_node.c
	gcc -c forest_node.c

huff_tree_node.o: huff_tree_node.h huff_tree_node.c
	gcc -c huff_tree_node.c

llist.o: llist_node.h llist.h llist.c
	gcc -c llist.c

llist_node.o: llist_node.h llist_node.c
	gcc -c llist_node.c
