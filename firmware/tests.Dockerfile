# Use an official GCC image
FROM gcc:latest

# Install GoogleTest and dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Create an app directory
WORKDIR /app

# Copy your source and test files
COPY ./Makefile ./Makefile
COPY ./main ./main
COPY ./tests ./tests

# Run the tests
CMD ["make", "tests"]
