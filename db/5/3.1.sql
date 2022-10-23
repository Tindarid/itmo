select * from Students natural join (select StudentId from Marks where CourseId = :CourseId and Mark = :Mark) R1
