# Author: Jake Mathai
# Purpose: Container Dockerfile. Load files, compile C++ code and install deps
FROM python:3.10.0
WORKDIR /src
COPY . /src/
RUN ls -l
RUN g++ -std=c++20 -c -fPIC /src/cpp/lru.cpp
RUN g++ -std=c++20 lru.o -shared -o /src/liblru.so -W
RUN python -m pip install -r /src/requirements.txt || true