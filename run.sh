rm -f results.txt
clear

#./bin/shortest-path -f datasets/tiny/tinyGraph.txt -q datasets/tiny/tinyWorkload_FINAL.txt && diff "./results.txt" "./datasets/tiny/tinyWorkload_RESULTS.txt"
#./bin/shortest-path -f datasets/small/smallGraph.txt -q datasets/small/smallWorkload_FINAL.txt && diff "./results.txt" "./datasets/small/smallWorkload_RESULTS.txt"
#./bin/shortest-path -f datasets/medium/mediumGraph.txt -q datasets/medium/mediumWorkload_FINAL.txt && diff "./results.txt" "./datasets/medium/mediumWorkload_RESULTS.txt"
./bin/shortest-path -f datasets/medium/mediumGraph.txt -q datasets/medium/static_workload/mediumWorkload_static_FINAL.txt && diff "./results.txt" "./datasets/medium/static_workload/mediumWorkload_static_RESULTS.txt"
#./bin/shortest-path -f datasets/large/large.txt -q datasets/large/dynamic_workload/largeWorkload_6000_20.txt && diff "./results.txt" "./datasets/large/dynamic_workload/largeWorkload_6000_20_RESULTS.txt"

#./bin/shortest-path -f datasets/test/loop.txt -q datasets/test/loopq.txt
#./bin/shortest-path -f datasets/test/oneLevel.txt -q datasets/test/oneLevelQ.txt
#./bin/shortest-path -f datasets/test/same.txt -q datasets/test/sameQ.txt


#./bin/shortest-path -f datasets/tiny/tinyGraph.txt -q datasets/tiny/tinyWorkload_FINAL.txt
#./bin/shortest-path -f datasets/small/smallGraph.txt -q datasets/small/smallWorkload_FINAL.txt
#./bin/shortest-path -f datasets/medium/mediumGraph.txt -q datasets/medium/mediumWorkload_FINAL.txt
#./bin/shortest-path -f datasets/medium/mediumGraph.txt -q datasets/medium/static_workload/mediumWorkload_static_FINAL.txt
#./bin/shortest-path -f datasets/large/large.txt -q datasets/large/dynamic_workload/largeWorkload_6000_20.txt
#./bin/shortest-path -f datasets/test/duplicatesGraph.txt
#./bin/shortest-path -f datasets/test/serialGraph.txt


# Valgrind
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/tiny/tinyGraph.txt -q datasets/tiny/tinyWorkload_FINAL.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/small/smallGraph.txt -q datasets/small/smallWorkload_FINAL.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/large/large.txt/large.txt -q datasets/large/dynamic_workload/largeWorkload_6000_20.txt


#diff <(head -n 2000 file1.log) <(head -n 2000 file2.log)
#4109857 -> ok  ~1hour

#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/test/anotherone.txt -q datasets/test/anotheroneQ.txt
#./bin/shortest-path -f datasets/medium/mediumGraph.txt
