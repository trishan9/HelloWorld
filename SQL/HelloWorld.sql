CREATE DATABASE IF NOT EXISTS hello_worlddb;

-- Switch to the hello_worlddb database
USE hello_worlddb;

-- Create the hello_world table
CREATE TABLE IF NOT EXISTS hello_world (
    id INT AUTO_INCREMENT PRIMARY KEY,
    message VARCHAR(255),
    language VARCHAR(255)
);

-- Insert values into the table
INSERT INTO hello_world (message, language) VALUES ('Hello world', 'English');

-- Select all rows from the hello_world table
SELECT message FROM hello_world where language='English';