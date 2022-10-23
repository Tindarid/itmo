-- Create new submission
CREATE OR REPLACE FUNCTION new_submission(new_id int, src_path varchar(200), user_id int, problem int, language varchar(50))
  RETURNS boolean
AS
$$
BEGIN
  insert into Submissions (id, time, src, verdict, contestant_id, problem_id, language_name)
  values (new_id, now(), src_path, 'pending', user_id, problem, language)
  on conflict (id) do nothing returning false;
  
  insert into TestResults (submission_id, test_id, verdict)
  select new_id, T.id, 'pending' from Tests T where T.problem_id = problem;
  return true;
END;
$$ LANGUAGE plpgsql;
