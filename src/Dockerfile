# Author: Jake Mathai
# Purpose: Container Dockerfile. Load files, compile C++ code and install deps
FROM python:3.10.0
WORKDIR /src
COPY . /src/
RUN ls -l
RUN apt-get update
RUN apt-get install python3-dev -y
RUN g++ -I /usr/local/include/python3.10/ -std=c++20 -c -fPIC /src/cpp/lru.cpp
RUN g++ -I /usr/local/include/python3.10/ -std=c++20 lru.o -shared -o /src/liblru.so -W
