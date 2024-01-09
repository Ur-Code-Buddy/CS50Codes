-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND street = 'Humphrey Street';
--all the witnesses mention bakery..lets check that out--

SELECT * FROM interviews
WHERE month = 7 AND day = 28;

/*We learnt a few crutial information here:
Considering that one of them might be the accomplance, we hear the one who talked about an accomplance.
mentioned that the suspect withdraw some amount from ATM of "Leggett Street"
then another mentioned that he left the bakery within 10 min of the act ~10:25
And that his accomplance booked the flight tickers and the earliest flight out
*/


SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON phone_calls.caller = people.phone_number
   AND atm_transactions.day = 28
   AND atm_transactions.atm_location = 'Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw'
   AND phone_calls.day = 28
   AND duration < 60;
--Bruce, Diana, Kenny, Taylor and Benista made transaction and phonecall that day --



SELECT name
  FROM people
  JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
   AND bakery_security_logs.day = 28
   AND bakery_security_logs.activity = 'exit'
   AND bakery_security_logs.hour = 10
   AND bakery_security_logs.minute >= 15
   AND bakery_security_logs.minute <= 25
--Names that repeat from atm transaction that who were at bakery are: Bruce, Diana

--Its either Bruce or Diana--



--Finding the earliest flight--
SELECT airports.full_name,airports.city, flights.id FROM airports
    JOIN flights on airports.id = flights.destination_airport_id
    WHERE flights.origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
    AND flights.day = 29
    ORDER by flights.hour,flights.minute;
--found that the earliest flight(id:36) is going to New York city lets see who all were travelling on that flight


SELECT people.name FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE people.name IN ('Bruce', 'Diana') AND passengers.flight_id = 36;


--The culprit is Bruce--
--Lets find the accomplince, the person he talked to--


SELECT name FROM people
WHERE phone_number = (
    SELECT phone_calls.receiver
    FROM phone_calls
    WHERE phone_calls.caller = '(367) 555-5533'
    AND phone_calls.day = 28
    AND phone_calls.duration < 60
);

--Accomplince is Robin--
