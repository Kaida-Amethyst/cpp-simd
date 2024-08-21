
main:
	mkdir -p target
	g++ main.cc vv-interface.cc -std=c++20 -o target/main

run: main
	./target/main

clean:
	rm -rf target
