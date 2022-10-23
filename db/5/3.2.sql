select * from Students natural join (select StudentId from Marks natural join Courses where CourseName = :CourseName and Mark = :Mark) R1
