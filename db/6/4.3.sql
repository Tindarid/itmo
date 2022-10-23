select StudentId
from Students
where StudentId not in (
  select StudentId
  from Students S, Lecturers L, Plan P
  where not exists (
    select StudentId, CourseId
    from Marks M
    where S.StudentId = M.StudentId and P.CourseId = M.CourseId
  ) and L.LecturerId = P.LecturerId and LecturerName = :LecturerName
)
