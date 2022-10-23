CREATE TYPE PROBLEM_T AS ENUM ('interactive', 'usual');
CREATE TYPE VERDICT_T AS ENUM ('accepted', 'wrong answer', 'runtime error', 'out of memory', 'time limit', 'unknown', 'pending', 'compilation error');

CREATE TABLE Contestants
(
  id               INT             NOT NULL PRIMARY KEY,
  name             VARCHAR(50)     NOT NULL
);

CREATE TABLE Contests
(
  id               INT             NOT NULL PRIMARY KEY,
  pid              INT             REFERENCES Contests(id),
  name             VARCHAR(50)     NOT NULL,
  description      TEXT            NOT NULL,
  location         VARCHAR(100)    NOT NULL,
  date             TIMESTAMP       NOT NULL
);

CREATE TABLE Questions
(
  id                INT            NOT NULL PRIMARY KEY,
  contest_id        INT            NOT NULL REFERENCES Contests(id),
  contestant_id     INT            NOT NULL REFERENCES Contestants(id),
  description       TEXT           NOT NULL,
  answer            TEXT
);

CREATE TABLE Problems
(
  id               INT             NOT NULL PRIMARY KEY,
  name             VARCHAR(50)     NOT NULL,
  description      TEXT            NOT NULL,
  problem_type     PROBLEM_T       NOT NULL
);

CREATE TABLE ProblemOfContest
(
  problem_id       INT             NOT NULL REFERENCES Problems(id),
  contest_id       INT             NOT NULL REFERENCES Contests(id),
  letter           CHAR            NOT NULL CHECK (letter between 'A' and 'Z'),
  PRIMARY KEY      (contest_id, letter)
);

CREATE TABLE Tests
(
  id               INT             NOT NULL PRIMARY KEY,
  input            VARCHAR(200)    NOT NULL,
  output           VARCHAR(200)    NOT NULL,
  problem_id       INT             NOT NULL REFERENCES Problems(id)
);

CREATE TABLE ProgrammingLanguages
(
  name             VARCHAR(50)     NOT NULL PRIMARY KEY,
  scaling_factor   REAL            NOT NULL
);

CREATE TABLE Submissions
(
  id               INT             NOT NULL PRIMARY KEY,
  time             TIMESTAMP       NOT NULL,
  src              VARCHAR(200)    NOT NULL,
  verdict          VERDICT_T       NOT NULL,
  contestant_id    INT             NOT NULL REFERENCES Contestants(id),
  problem_id       INT             NOT NULL REFERENCES Problems(id),
  language_name    VARCHAR(50)     NOT NULL REFERENCES ProgrammingLanguages(name)
);

CREATE TABLE TestResults
(
  submission_id    INT             NOT NULL REFERENCES Submissions(id),
  test_id          INT             NOT NULL REFERENCES Tests(id),
  verdict          VERDICT_T       NOT NULL,
  PRIMARY KEY      (submission_id, test_id)
);

-- | For contest_problems
-- || Done by psql
-- CREATE INDEX ON ProblemOfContest USING btree (contest_id, letter);

-- ||
 CREATE INDEX ON Problems USING hash (id);

-- | For show_submission
-- || Done by psql
-- CREATE INDEX ON TestResults USING btree (submission_id, test_id);

-- ||
CREATE INDEX ON Tests USING hash (id);

-- | For contest_places
-- || Mentioned before
-- CREATE INDEX ON ProblemOfContest USING btree (contest_id, letter);

-- ||
CREATE INDEX ON Contestants USING hash (id);

-- ||
CREATE INDEX ON Submissions USING btree (verdict, problem_id);
