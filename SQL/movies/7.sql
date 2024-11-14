SELECT title, rating FROM movies JOIN ratings ON movie_id = id where year = 2010 ORDER BY rating DESC, title ASC;
