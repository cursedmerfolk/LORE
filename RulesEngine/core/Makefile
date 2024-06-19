
jsoncpp_build:
	cd jsoncpp && \
	mkdir -p build && \
	cd build && \
	cmake -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_SYSTEM_VERSION=11 -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DJSONCPP_WITH_TESTS=OFF .. && \
	make install && \
	cd ../..


windows:
	mkdir -p build && \
	cd build && \
	cmake -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_SYSTEM_VERSION=11 -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ .. && \
	make && \
	cd ..

# Clean up build files
clean:
	rm -rf build
