SELECT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE stars.movie_id IN (
    SELECT movie_id
    FROM stars
    WHERE stars.person_id = (
        SELECT id
        FROM people
        WHERE name = 'Kevin Bacon' AND birth = 1958
    )
) AND people.name != 'Kevin Bacon';
