build:
	g++ walsh.cpp -o walsh
	g++ statistics.cpp -o statistics
	g++ prinel.cpp -o prinel

run-p1:
	./walsh

run-p2:
	./statistics

run-p3:
	./prinel

run-p4:

clean:
	rm walsh statistics verif
