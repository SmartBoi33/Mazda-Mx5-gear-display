FROM ubuntu:latest

# Install dependencies
RUN apt update && apt install -y \
    arduino-cli \
    simavr \
    make \
    gcc \
    g++

# Create a working directory
WORKDIR /app

ENV PWD=/app

# Copy your Arduino project files
COPY ./Makefile ./Makefile
COPY ./main ./main
COPY ./tests ./tests

# Set Arduino CLI config
RUN make install

# Compile the test sketch
RUN make compile

# Run tests on simulated board
CMD simavr -m atmega328p -f 16000000 ./build/test.ino.hex
