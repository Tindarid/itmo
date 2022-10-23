select StudentId, StudentName, GroupName
from Students S, Groups G
where S.GroupId = G.GroupId and StudentId not in (
  select StudentId
  from Marks M, Courses C
  where C.CourseName = :CourseName and C.CourseId = M.CourseId
)
