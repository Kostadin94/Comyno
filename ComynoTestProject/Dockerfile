# Use a base image with a C++ development environment
FROM gcc:latest

# Set the working directory in the container
WORKDIR /app

# Copy the C++ source code to the container
COPY . .

# Build the C++ application
RUN g++ -o app main.cpp -lcpprest -lboost_system -lpthread

# Expose the port your C++ application is listening on
EXPOSE 8080

# Command to run your C++ application
CMD ["./app"]
