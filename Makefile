imgproc: imgtools.o imgproc.o
	g++ -o imgproc imgtools.o imgproc.o
	
imgtools.o: imgtools.cc imgtools.h
	g++ -c imgtools.cc

imgproc.o: imgproc.cc imgtools.h
	g++ -c imgproc.cc
	

