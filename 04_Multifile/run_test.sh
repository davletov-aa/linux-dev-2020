TEST_DIR=$1

for x in prog prog-a prog-so;
do
	cp -f "$x" "run";
	./run 2> "$TEST_DIR/$x.txt";
	./run "la" >> "$TEST_DIR/$x.txt";
	./run "la" "la" "la" >> "$TEST_DIR/$x.txt";
	rm "run"
done