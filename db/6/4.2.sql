select StudentId
from Students
where StudentId not in (
  select S.StudentId
  from Lecturers L, Plan P, Students S, Marks M
  where LecturerName = :LecturerName
    and L.LecturerId = P.LecturerId
    and P.GroupId    = S.GroupId
    and M.StudentId  = S.StudentId
    and M.CourseId   = P.CourseId
)
