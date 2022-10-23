select distinct S.StudentId, StudentName, GroupId
from Students S, Marks M, Courses C
where S.StudentId = M.StudentId
  and M.CourseId  = C.CourseId 
  and CourseName  = :CourseName
  and Mark        = :Mark
