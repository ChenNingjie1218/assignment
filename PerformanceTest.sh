cmake -S . -B ./build
cmake --build ./build
./build/test/performancetest
python3 python/data2plot.py