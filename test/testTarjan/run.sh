rm -f results
clear


#./bin/shortest-path -f datasets/dfsExample.txt 
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/wikiExample.txt 
#./bin/shortest-path -f datasets/wikiExample.txt 
#./bin/shortest-path -f datasets/theirExample.txt 
./bin/shortest-path -f datasets/grailSimple.txt 

#./bin/shortest-path -f ../../datasets/tiny/tinyGraph.txt 
#./bin/shortest-path -f ../../datasets/small/smallGraph.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f ../../datasets/small/smallGraph.txt 
#./bin/shortest-path -f ../../datasets/medium/mediumGraph.txt

#./bin/shortest-path -f ../../datasets/tiny/tinyGraph.txt -q ../../datasets/tiny/tinyWorkload_FINAL.txt && diff "./results.txt" "../.././datasets/tiny/tinyWorkload_RESULTS.txt"
#./bin/shortest-path -f ../../datasets/small/smallGraph.txt -q ../../datasets/small/smallWorkload_FINAL.txt && diff "./results.txt" "../.././datasets/small/smallWorkload_RESULTS.txt"
#./bin/shortest-path -f ../../datasets/medium/mediumGraph.txt -q ../../datasets/medium/mediumWorkload_FINAL.txt && diff "./results.txt" "../.././datasets/medium/mediumWorkload_RESULTS.txt"
#./bin/shortest-path -f ../../datasets/medium/mediumGraph.txt -q ../../datasets/medium_static_workload/mediumWorkload_static_FINAL.txt && diff "../.././results.txt" "../.././datasets/medium_static_workload/mediumWorkload_static_RESULTS.txt"
#./bin/shortest-path -f ../../datasets/large/large.txt/large.txt -q ../../datasets/large/dynamic_workload/largeWorkload_6000_20.txt && diff "./results.txt" "../.././datasets/large/dynamic_workload/largeWorkload_6000_20_RESULTS.txt"

#./bin/shortest-path -f datasets/wikiExample.txt -q datasets/wikiExampleWorkload_FINAL.txt
#./bin/shortest-path -f ../../datasets/tiny/tinyGraph.txt -q ../../datasets/tiny/tinyWorkload_FINAL.txt
#./bin/shortest-path -f ../../datasets/small/smallGraph.txt -q ../../datasets/small/smallWorkload_FINAL.txt
#./bin/shortest-path -f ../../datasets/medium/mediumGraph.txt -q ../../datasets/medium/mediumWorkload_FINAL.txt
#./bin/shortest-path -f ../../datasets/medium/mediumGraph.txt -q ../../datasets/medium/static_workload/mediumWorkload_static_FINAL.txt
#./bin/shortest-path -f ../../datasets/large/large.txt -q ../../datasets/large/dynamic_workload/largeWorkload_6000_20.txt
#./bin/shortest-path -f ../../datasets/test/duplicatesGraph.txt
#./bin/shortest-path -f ../../datasets/test/serialGraph.txt


# Valgrind
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/tiny/tinyGraph.txt -q datasets/tiny/tinyWorkload_FINAL.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/small/smallGraph.txt -q datasets/small/smallWorkload_FINAL.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/shortest-path -f datasets/large/large.txt/large.txt -q datasets/large/dynamic_workload/largeWorkload_6000_20.txt
