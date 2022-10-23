select GroupName, CourseName
from Groups G1, Courses C1
where not exists (
  select GroupId, CourseId
  from Students S, Courses C2
  where G1.GroupId = S.GroupId and C2.CourseId = C1.CourseId and not exists (
    select StudentId, CourseId
    from Marks M
    where S.StudentId = M.StudentId and C2.CourseId = M.CourseId and Mark >= 3
  )
)
