clear

#./bin/shortest-path -f datasets/tiny/tinyGraph.txt -q datasets/tiny/tinyWorkload_FINAL.txt
./bin/shortest-path -f datasets/small/smallGraph.txt -q datasets/small/smallWorkload_FINAL.txt
#./bin/shortest-path -f datasets/medium/mediumGraph.txt -q datasets/medium/mediumWorkload_FINAL.txt
#./bin/shortest-path -f datasets/large/large.txt -q datasets/large/dynamic_workload/largeWorkload_6000_20.txt
#./bin/shortest-path -f datasets/test/duplicatesGraph.txt
#./bin/shortest-path -f datasets/test/serialGraph.txt


# Valgrind
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/tiny/tinyGraph.txt -q datasets/tiny/tinyWorkload_FINAL.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/small/smallGraph.txt -q datasets/small/smallWorkload_FINAL.txt
