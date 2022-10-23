select StudentName, CourseName
from (
  select StudentId, CourseId from Marks
  union
  select StudentId, CourseId from Plan P, Students S where S.GroupId = P.GroupId
) Ids, Students S, Courses C
where Ids.StudentId = S.StudentId and C.CourseId = Ids.CourseId
