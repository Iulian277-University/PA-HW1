build:
	g++ walsh.cpp -o walsh
	g++ statistics.cpp -o statistics
	g++ prinel.cpp -o prinel
	g++ crypto.cpp -o crypto
	g++ regele.cpp -o regele

run-p1:
	./walsh

run-p2:
	./statistics

run-p3:
	./prinel

run-p4:
	./crypto

run-p5:
	./regele

clean:
	rm walsh statistics prinel crypto regele verif
