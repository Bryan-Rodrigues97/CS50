SELECT title FROM movies
JOIN ratings ON ratings.movie_id = movies.id
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id AND name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;
