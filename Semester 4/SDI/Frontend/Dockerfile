# Use a base image that supports Node.js and npm
FROM node:latest

# Set the working directory
WORKDIR /app

# Copy the frontend application code to the Docker image
COPY . .

# Install the required dependencies
RUN npm install

# Build the frontend application
RUN npm run build

# Expose the necessary port(s)
EXPOSE 3000

# Specify the command to start your frontend application
CMD ["npm", "start"]
