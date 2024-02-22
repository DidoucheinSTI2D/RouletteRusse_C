CREATE TABLE `games` (
 `id` INT PRIMARY KEY AUTO_INCREMENT,
 `numbers` INT,
 `winner` INT
);

CREATE TABLE `users` (
 `id` INT PRIMARY KEY AUTO_INCREMENT,
 `username` VARCHAR(15),
 `wins` INT,
 `loses` INT
);

CREATE TABLE `users_games` (
 `game_id` INT REFERENCES games(id),
 `user_id` INT REFERENCES users(id)
);
