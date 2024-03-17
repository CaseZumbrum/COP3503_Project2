build:
	g++ -std=c++11 -o project2.out image.cpp image_reader.cpp main.cpp
task:
	./project2.out output/part11.tga input/circles.tga multiply input/layer1.tga
	./project2.out output/part12.tga input/layer1.tga flip
	./project2.out output/part13.tga input/layer1.tga subtract input/layer2.tga 
