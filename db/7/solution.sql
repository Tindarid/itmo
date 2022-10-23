-- 1.1
delete from Students where StudentId not in (
  select R.StudentId from (
    select S.StudentId, Mark
    from Plan P natural join Students S left outer join Marks M
    on M.CourseId = P.CourseId and M.StudentId = S.StudentId
  ) R where Mark is null or Mark < 60
);


-- 1.2
delete from Students where StudentId in (
  select R2.StudentId from (
    select R.StudentId, count(*) as C from (
      select S.StudentId, Mark
      from Plan P natural join Students S left outer join Marks M
      on M.CourseId = P.CourseId and M.StudentId = S.StudentId
    ) R where Mark is null or Mark < 60 group by R.StudentId
  ) R2 where R2.C >= 3
);

-- 1.3
delete from Groups where GroupId not in (
  select distinct GroupId from Students
);

-- 2.1
create view Losers as (
  select R.StudentId, R.StudentName, count(*) as amount from (
    select S.StudentId, StudentName, Mark
    from Plan P natural join Students S left outer join Marks M
    on M.CourseId = P.CourseId and M.StudentId = S.StudentId
  ) R where Mark is null or Mark < 60 group by R.StudentId, R.StudentName
);

-- 2.2
create materialized view LoserT AS (
  select StudentId, StudentName, Amount from Losers
);

create function update_losers() returns trigger as $$
begin
  refresh materialized view LoserT;
  return null;
end;
$$ LANGUAGE plpgsql;

create trigger UpdateLosers
after insert or update or delete on Marks
for each statement execute procedure update_losers();

-- 2.3
drop trigger if exists UpdateLosers on Marks;

-- 3.1
Такая проверка выполняется автоматически, потому что изучение курса == запись в таблице Plan, а в ней не фигурируют StudentId (но фигурируют GroupId). Значит все студенты каждой группы будут изучать один и тот же набор курсов.

-- 3.2
create function update_mark() returns trigger as $$
begin
  if new.Mark < old.Mark then
    return old;
  else
    return new;
  end if;
end;
$$ LANGUAGE plpgsql;

create trigger Guard
before update on Marks
for each row execute procedure update_mark();
