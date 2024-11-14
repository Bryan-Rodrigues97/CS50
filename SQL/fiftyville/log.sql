-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find the crime scene report description
SELECT * FROM crime_scene_reports
    WHERE day = 28
    AND month = 7;
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Find the interviews mentioning the bakery.
SELECT * FROM interviews
    WHERE transcript LIKE '%bakery%'
    AND day = 28
    AND month = 7;

-- Ruth
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
SELECT t2.name, t1.license_plate FROM bakery_security_logs t1
JOIN people t2 on t2.license_plate = t1.license_plate
    WHERE t1.day = 28
    AND t1.month = 7
    AND t1.hour = 10
    AND t1.minute < 25
    AND t1.activity = 'exit';

-- Suspects by securities log:
    -- Vanessa
    -- Bruce
    -- Barry
    -- Luca
    -- Sofia
    -- Iman
    -- Diana
    -- Kelsey


-- Eugene
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Query the persons who withdrew some money according to Eugene.
SELECT t1.account_number, t3.name, t3.phone_number, t3.passport_number, t3.license_plate FROM atm_transactions t1
JOIN bank_accounts t2 on t2.account_number = t1.account_number
JOIN people t3 ON t3.id = t2.person_id
    WHERE t1.day = 28
    AND t1.month = 7
    AND t1.atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';

-- Suspects by atm withdrew:
    -- Bruce
    -- Diana
    -- Brooke
    -- Kenny
    -- Iman
    -- Luca
    -- Taylor
    -- Benista


-- Raimond
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

--  Query the phone calls. Search for suspects.
SELECT t2.name, t2.phone_number, t2.passport_number, t2.license_plate, t3.name, t3.phone_number, t3.passport_number, t3.license_plate  FROM phone_calls t1
JOIN people t2 ON t2.phone_number = t1.caller
JOIN people t3 ON t3.phone_number = t1.receiver
    WHERE t1.day = 28
    AND t1.month = 7
    AND t1.duration < 60;

-- Suspects and Accomplice Suspects based on the query calls:
    -- Sofia    - Accompplice Jack
    -- Kelsey   - Accompplice Larry
    -- Bruce    - Accompplice Robin
    -- Kelsey   - Accompplice Melissa
    -- Taylor   - Accompplice James
    -- Diana    - Accompplice Philip
    -- Carina   - Accompplice Jacqueline
    -- Kenny    - Accompplice Doris
    -- Benista  - Accompplice Anna

-- After comparing the suspects based on the three interviews.
    -- Bruce
-- Diana


-- Query phone calls. Search for details.
-- Suspects (Bruce and Diana)
SELECT t2.name, t2.phone_number, t2.passport_number, t2.license_plate, t3.name, t3.phone_number, t3.passport_number, t3.license_plate  FROM phone_calls t1
JOIN people t2 ON t2.phone_number = t1.caller
JOIN people t3 ON t3.phone_number = t1.receiver
    WHERE t1.day = 28
    AND t1.month = 7
    AND t1.duration < 60
    AND (t2.name = 'Bruce' OR t2.name = 'Diana');

-- Bank movements from the suspects.
SELECT t1.year, t1.month, t1.day, t1.transaction_type, t1.amount, t3.name FROM atm_transactions t1
JOIN bank_accounts t2 ON t2.account_number = t1.account_number
JOIN people t3 ON t3.id = t2.person_id
    AND month = 7
    AND (t3.name = 'Philip' OR t3.name = 'Robin' OR name = 'Diana' OR name = 'Bruce');

-- Robin makes a deposit (2023-07-29). Money for the flight?

-- Check for flies where Bruce or Diana where passengers
SELECT t1.id, t1.month, t1.day, t5.name, t2.city, t3.city FROM flights t1
JOIN airports t2 ON t2.id = t1.origin_airport_id
JOIN airports t3 ON t3.id = t1.destination_airport_id
JOIN passengers t4 ON t4.flight_id = t1.id
JOIN people t5 ON t5.passport_number = t4.passport_number
    WHERE t5.name = 'Bruce'
    OR t5.name = 'Diana';

-- Diana traveled twice, including returning to Fiftyville. Meanwhile, Bruce left for New York City on the 29th, one day after the robbery, and did not return
-- Bruce is the THIEF who scaped to NYC. Robin is the ACCOMPLICE.
