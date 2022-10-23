select * from Students except select * from (select * from (select StudentId from Marks natural join Courses where CourseName = :CourseName) R1 natural join Students) R2
