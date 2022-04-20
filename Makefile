build:
	g++ walsh.cpp -o walsh
	g++ statistics.cpp -o statistics
	g++ prinel.cpp -o prinel
	# g++ crypto.cpp -o crypto

run-p1:
	./walsh

run-p2:
	./statistics

run-p3:
	./prinel

run-p4:
	# ./crypto

clean:
	rm walsh statistics crypto verif
