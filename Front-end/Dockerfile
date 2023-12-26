# Use a base image with Node.js
FROM node:latest

# Set the working directory in the container
WORKDIR /app

# Copy package.json and package-lock.json to the container
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the frontend source code to the container
COPY . .

# Expose the port your Node.js application is listening on
EXPOSE 8081

# Command to run your Node.js application
CMD ["npm", "start"]
