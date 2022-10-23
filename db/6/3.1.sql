select StudentId, CourseId from Marks
union
select StudentId, CourseId from Plan P, Students S where S.GroupId = P.GroupId
