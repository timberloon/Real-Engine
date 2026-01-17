dll:
	g++ -shared -DNOVALIB_BUILD nova/src/*.cpp -Inova -Wl,--out-implib,build/libnovalib.dll.a -o build/nova.dll
applic:
	g++ space/space.cpp -Inova -Lbuild -lnova -o build/space.exe
run:
	./build/space.exe