-- Problems of contest
CREATE OR REPLACE FUNCTION contest_problems(contest int)
  RETURNS TABLE
          (
            letter         char,
            name           varchar(50)
          )
  IMMUTABLE
AS
$$
BEGIN
  RETURN QUERY
    with Related as (
      select * from ProblemOfContest PC where PC.contest_id = contest
    )
    select R.letter as letter, P.name as name
    from Related R
    inner join Problems P on R.problem_id = P.id
    order by R.letter;
END;
$$ LANGUAGE plpgsql;

-- Test results of submission
CREATE OR REPLACE FUNCTION show_submission(submission int)
  RETURNS TABLE
          (
            test_number     int,
            verdict         verdict_t
          )
  IMMUTABLE
AS
$$
BEGIN
  RETURN QUERY
    with Results as (
      select * from TestResults where submission_id = submission
    )
    select (row_number() OVER (ORDER BY R.test_id))::int test_number, R.verdict as verdict
    from Results R
    inner join Tests T on T.id = R.test_id;
END;
$$ LANGUAGE plpgsql;

-- Contest's table of places
CREATE OR REPLACE FUNCTION contest_places(contest int)
  RETURNS TABLE
          (
            place          int,
            name           varchar(50),
            solved         int
          )
  IMMUTABLE
AS
$$
BEGIN
  RETURN QUERY
    with
    Related as (
      select * from ProblemOfContest PC where PC.contest_id = contest
    ),
    ContestantSolved as (
      select S.contestant_id as id, count(distinct S.problem_id)::int as solved
      from Related R
      inner join Submissions S
      on R.problem_id = S.problem_id and S.verdict = verdict_t 'accepted'
      group by S.contestant_id
    )
    select (row_number() OVER (ORDER BY CS.solved desc))::int place, C.name as name, CS.solved
    from ContestantSolved CS
    inner join Contestants C
    on C.id = CS.id;
END;
$$ LANGUAGE plpgsql;
