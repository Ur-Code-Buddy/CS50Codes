# Student Management System

#### Video Demo: https://youtu.be/6qbKEkkLj3U

## Student Management System Documentation



## Overview

The Student Management System is a Flask-based web application designed to simplify user registration, authentication, and real-time communication through a group chat feature. Leveraging Flask-SocketIO for WebSocket-based communication, this system enables seamless interaction within the chat interface.

## Project Structure

### Directories:

- **templates:** Contains HTML templates for rendering pages.
- **static:** Houses static files such as CSS and JavaScript.
- **helpers.py:** Includes helper functions for error handling and user authentication.
- **final_project.sql:** SQL file with the database schema.
- **users.db:** SQLite database file storing user and conversation data.

### Files:

- **app.py:** Main application file containing Flask routes, SocketIO configuration, and database interactions.

## Configuration

### Dependencies:

- Flask
- Flask-SocketIO
- cs50
- Werkzeug

### Environment Configuration:

Flask app and SocketIO are configured to run with the host set to "0.0.0.0" and port 5000.

## Application Routes

1. **Index Route ("/"):**
   - Requires user authentication.
   - Renders the main page ("index.html") upon successful login.

2. **Chat Route ("/live_chat"):**
   - Requires user authentication.
   - Renders the chat interface ("chat.html") with the current user's username.

3. **Login Route ("/login"):**
   - Allows users to log in.
   - Handles both GET and POST requests.
   - Validates submitted credentials and redirects to the main page on successful login.

4. **Logout Route ("/logout"):**
   - Logs the user out by clearing the session.
   - Redirects to the login page.

5. **Register Route ("/register"):**
   - Allows new users to register.
   - Handles both GET and POST requests.
   - Validates and hashes the password before saving user data to the database.

## SocketIO Integration

1. **SocketIO Initialization:**
   - Configures Flask-SocketIO with CORS enabled for all origins.

2. **Message Handling:**
   - Defines a SocketIO event "message" for handling chat messages.
   - Broadcasts messages to all users in real-time.
   - Stores messages in the database along with the user ID and timestamp.

## Database Interaction

1. **Database Schema:**
   - Two tables in "users.db": "users" and "conversations."
   - "users" table stores user IDs, usernames, and hashed passwords.
   - "conversations" table stores chat messages with user IDs and timestamps.

## User Authentication

1. **Session Management:**
   - Utilizes Flask sessions for user authentication and persistence.

2. **Password Security:**
   - Utilizes Werkzeug for password hashing and verification.

## Running the Application

1. **Execution:**
   - The application is set to run with `socketio.run(app, host="0.0.0.0", port=5000)`.

2. **Access:**
   - Access the application through a web browser at http://localhost:5000.

## Conclusion

This detailed documentation provides a comprehensive overview of the Student Management System's structure, configuration, routes, SocketIO integration, database interaction, user authentication, and execution. The application offers a user-friendly interface, real-time communication, and secure user authentication, creating a holistic solution for student management.
