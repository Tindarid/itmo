INSERT INTO Contests (id, name, description, location, date)
VALUES (1, 'Codeforces Round 100', 'New rating round', 'codeforces.com', TIMESTAMP '2012-11-11 10:40:40'),
       (2, 'Northwestern Russia Regional Contest 2030', 'Some obvious description', 'St. Petersburg', TIMESTAMP '2030-06-06 12:12:12'),
       (3, 'Google Hashcode 2008', 'Welcome, programmers!', 'New-York', TIMESTAMP '2008-05-20 6:00:00'),
       (4, 'Google Hashcode 2009', 'Welcome, programmers!', 'New-Amsterdam', TIMESTAMP '2009-05-20 6:00:00'),
       (5, 'Google KickStart 2010', 'Welcome, programmers! Let''s start!', 'WWW', TIMESTAMP '2010-05-20 6:00:00'),
       (6, 'PCMS Training', 'Problems with trees and others', 'https://neerc.ifmo.ru/pcms2client', TIMESTAMP '2020-06-07 11:00:00');

INSERT INTO Contestants (id, name)
VALUES (1, 'Gennady Korotkevich'),
       (2, 'Benjamin Qi'),
       (3, 'Andrew He'),
       (4, 'Petr Mitrichev'),
       (5, 'Alex Danilyuk');

INSERT INTO Questions (id, contest_id, contestant_id, description, answer)
VALUES (1, 1, 1, 'Why problems are so easy?', null),
       (2, 3, 1, 'Why problems are so easy?', null),
       (3, 2, 1, 'Why problems are so easy?', 'enough'),
       (4, 6, 3, 'How to solve task A?', 'No comments.'),
       (5, 6, 4, 'I think B task is NP', 'But it is not NP-complete!');

INSERT INTO Problems (id, name, description, problem_type)
VALUES (1, 'A + B', '2 + 2 = 4', PROBLEM_T('usual')),
       (2, 'A + B Bigintegers', '20000000000000000000000 + 200000000000000000000 = ?', PROBLEM_T('usual')),
       (3, 'Topological sort of tree', 'Try it yourself', PROBLEM_T('usual')),
       (4, 'Planar graphs strike back', 'No way to solve it', PROBLEM_T('interactive')),
       (5, 'Disk Tree',
       'Hacker Bill has accidentally lost all the information from his workstation''s hard drive and he has no backup copies of its contents.
        He does not regret for the loss of the files themselves, but for the very nice and convenient directory structure that he had created and cherished during years of work.
        Fortunately, Bill has several copies of directory listings from his hard drive.
        Using those listings he was able to recover full paths (like "WINNT\SYSTEM32\CERTSRV\CERTCO~1\X86") for some directories.
        He put all of them in a file by writing each path he has found on a separate line.
        Your task is to write a program that will help Bill to restore his state of the art directory structure by providing nicely formatted directory tree.',
       PROBLEM_T('usual')),
       (6, 'Factorials!!!',
       'Definition 1. n!!…! = n(n−k)(n−2k)…(n mod k), if k doesn’t divide n; n!!…! = n(n−k)(n−2k)…k, if k divides n (There are k marks ! in the both cases).
        Definition 2. X mod Y — a remainder after division of X by Y.
        For example, 10 mod 3 = 1; 3! = 3·2·1; 10!!! = 10·7·4·1.
        Given numbers n and k we have calculated a value of the expression in the first definition. Can you do it as well?',
       PROBLEM_T('interactive'));


INSERT INTO ProblemOfContest (contest_id, problem_id, letter)
VALUES (1, 1, 'A'),
       (1, 2, 'B'),
       (2, 1, 'B'),
       (2, 2, 'A'),
       (3, 1, 'A'),
       (4, 3, 'Y'),
       (5, 1, 'A'),
       (5, 4, 'B'),
       (6, 5, 'A'),
       (6, 6, 'B');


INSERT INTO Tests (id, input, output, problem_id)
VALUES (1, '2+2.in', '2+2.out', 1),
       (2, '4+4.in', '4+4.out', 1),
       (3, '0+0.in', '0+0.out', 1),
       (4, '1+1.in', '1+1.out', 1),
       (5, 'MAXINTdiv2+MAXINTdiv2.in', 'MAXINTdiv2+MAXINTdiv2.out', 1),
       (6, '2222222222222222222222222222 + 1111111.in', '2222222222222222222222222222 + 1111111.out', 2),
       (7, '512bit + 512bit.in', '512bit + 512bit.out', 2),
       (8, '9 !!.in', '9 !!.out', 6),
       (9, 'sample.in', 'sample.out', 3),
       (10, 'sample.in', 'sample.out', 4),
       (11, 'sample.in', 'sample.out', 5);

INSERT INTO ProgrammingLanguages (name, scaling_factor)
VALUES ('C++ gcc 9.2.0', 1.0),
       ('Python 2.7', 0.3),
       ('Python 3.2', 0.5),
       ('GHC 8.8.3', 0.5),
       ('javac 8.0', 0.9),
       ('javac 11.0.10', 1.0),
       ('rustc 1.49.0 (e1884a8e3 2020-12-29)', 1.5);

INSERT INTO Submissions (id, time, src, verdict, contestant_id, problem_id, language_name)
VALUES (1, TIMESTAMP '2024-12-12 11:43:44', 'try.cpp', 'accepted', 1, 1, 'C++ gcc 9.2.0'),
       (2, TIMESTAMP '2014-12-12 11:43:44', 'wow.py', 'pending', 2, 1, 'Python 3.2'),
       (3, TIMESTAMP '2015-12-12 11:43:44', 'sol.hs', 'pending', 4, 2, 'GHC 8.8.3'),
       (4, TIMESTAMP '2011-12-12 11:43:44', 'sol.hs', 'compilation error', 4, 3, 'Python 2.7'),
       (5, TIMESTAMP '2011-12-12 11:43:44', 'sol.java', 'accepted', 4, 1, 'javac 8.0'),
       (6, TIMESTAMP '2011-12-12 11:43:45', 'sol.java', 'accepted', 4, 2, 'javac 8.0'),
       (7, TIMESTAMP '2011-12-12 11:43:46', 'sol.java', 'accepted', 4, 3, 'javac 8.0'),
       (8, TIMESTAMP '2011-12-12 11:43:47', 'sol.java', 'accepted', 4, 4, 'javac 8.0'),
       (9, TIMESTAMP '2011-12-12 11:43:48', 'sol.java', 'accepted', 4, 5, 'javac 8.0'),
       (10, TIMESTAMP '2011-12-12 11:43:49', 'sol.java', 'accepted', 4, 6, 'javac 8.0');


INSERT INTO TestResults (submission_id, test_id, verdict)
VALUES (1, 1, 'accepted'),
       (1, 2, 'accepted'),
       (1, 3, 'accepted'),
       (1, 4, 'accepted'),
       (1, 5, 'accepted'),
       (4, 9, 'compilation error'),
       (5, 1, 'accepted'),
       (5, 2, 'accepted'),
       (5, 3, 'accepted'),
       (5, 4, 'accepted'),
       (5, 5, 'accepted'),
       (6, 6, 'accepted'),
       (6, 7, 'accepted'),
       (10, 8, 'accepted'),
       (7, 9, 'accepted'),
       (8, 10, 'accepted'),
       (9, 11, 'accepted');
